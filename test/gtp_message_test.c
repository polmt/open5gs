#include "core_pkbuf.h"
#include "core_lib.h"
#include "core_debug.h"

#include "testutil.h"
#include "asn_msg.h"

static void gtp_message_test1(abts_case *tc, void *data)
{
    asnv_msg_ms_preattachment_req reqv;
    asnv_msg_ms_preattachment_req reqv2;

    pkbuf_t *req = NULL;
#if 0
    c_uint8_t *buf;
    c_uint32_t buflen;
#endif

    {
        extern int _asn_msg;
        _asn_msg = 0;
    }
    /* Initialize message value structure */
    memset(&reqv, 0, sizeof(asnv_msg_ms_preattachment_req));

    /* Set nessary members of message */
    COMPD_SET(reqv.ms_info);
    COMPD_SET(reqv.ms_info.ms_security_history);
    VALUE_SET(reqv.ms_info.ms_security_history.authorization_policy_support, 0x3);

    COMPD_SET(reqv.bs_info);
    OCTET_SET(reqv.bs_info.bs_id, (c_uint8_t*)"\x11\x22\x33\x44\x55\x66", 6);

    /* Build message */
    asn_build_msg(&req, &asnt_msg_ms_preattachment_req, &reqv);

#if 0
    d_print_hex(req->payload, req->len);
#endif

    /* Initialize message value structure */
    memset(&reqv2, 0, sizeof(asnv_msg_ms_preattachment_req));

    /* Parse message */
    asn_parse_msg(&reqv2, &asnt_msg_ms_preattachment_req, req);

    if (COMPD_ISSET(reqv2.ms_info))
        if (COMPD_ISSET(reqv2.ms_info.ms_security_history))
            if (VALUE_ISSET(reqv2.ms_info.ms_security_history.authorization_policy_support))
#if 0
                d_print("%02x", VALUE_GET(reqv2.ms_info.ms_security_history.authorization_policy_support));
#else
    ;
#endif

#if 0
    if (COMPD_ISSET(reqv2.bs_info))
        if (OCTET_ISSET(reqv2.bs_info.bs_id))
        {
            OCTET_GET(buf, buflen, reqv2.bs_info.bs_id);
            d_print_hex(buf, buflen);
        }
#endif
    pkbuf_free(req);
}

abts_suite *test_gtp_message(abts_suite *suite)
{
    suite = ADD_SUITE(suite)

    abts_run_test(suite, gtp_message_test1, NULL);

    return suite;
}
