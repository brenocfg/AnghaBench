#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL3_RT_MAX_PLAIN_LENGTH ; 
 int /*<<< orphan*/  SSL_CTX_clear_options (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 void* SSL_CTX_set1_groups_list (int /*<<< orphan*/ *,char*) ; 
 void* SSL_CTX_set_max_early_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_OP_ENABLE_MIDDLEBOX_COMPAT ; 
 int /*<<< orphan*/  SSL_READ_EARLY_DATA_FINISH ; 
 int /*<<< orphan*/  SSL_READ_EARLY_DATA_SUCCESS ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_connect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get1_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_read_early_data (int /*<<< orphan*/ *,char*,int,size_t*) ; 
 void* SSL_set_session (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ *) ; 
 void* SSL_write_early_data (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  TEST_error (char*) ; 
 int /*<<< orphan*/  TEST_false (void*) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_size_t_eq (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_size_t_gt (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (void*) ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 void* badccs ; 
 void* badsessid ; 
 void* badvers ; 
 int /*<<< orphan*/  bio_f_watchccs_filter () ; 
 int /*<<< orphan*/ * c_to_s_fbio ; 
 void* cappdataseen ; 
 void* ccsaftersh ; 
 void* ccsbeforesh ; 
 int /*<<< orphan*/  cert ; 
 void* chseen ; 
 scalar_t__ chsessidlen ; 
 void* create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  privkey ; 
 int /*<<< orphan*/ * s_to_c_fbio ; 
 void* sappdataseen ; 
 void* sccsseen ; 
 void* shseen ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int test_tls13ccs(int tst)
{
    SSL_CTX *sctx = NULL, *cctx = NULL;
    SSL *sssl = NULL, *cssl = NULL;
    int ret = 0;
    const char msg[] = "Dummy data";
    char buf[80];
    size_t written, readbytes;
    SSL_SESSION *sess = NULL;

    chseen = shseen = sccsseen = ccsaftersh = ccsbeforesh = 0;
    sappdataseen = cappdataseen = badccs = badvers = badsessid = 0;
    chsessidlen = 0;

    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(), TLS_client_method(),
                                       TLS1_VERSION, 0,
                                       &sctx, &cctx, cert, privkey))
        || !TEST_true(SSL_CTX_set_max_early_data(sctx,
                                                 SSL3_RT_MAX_PLAIN_LENGTH)))
        goto err;

    /*
     * Test 0: Simple Handshake
     * Test 1: Simple Handshake, client middlebox compat mode disabled
     * Test 2: Simple Handshake, server middlebox compat mode disabled
     * Test 3: HRR Handshake
     * Test 4: HRR Handshake, client middlebox compat mode disabled
     * Test 5: HRR Handshake, server middlebox compat mode disabled
     * Test 6: Early data handshake
     * Test 7: Early data handshake, client middlebox compat mode disabled
     * Test 8: Early data handshake, server middlebox compat mode disabled
     * Test 9: Early data then HRR
     * Test 10: Early data then HRR, client middlebox compat mode disabled
     * Test 11: Early data then HRR, server middlebox compat mode disabled
     */
    switch (tst) {
    case 0:
    case 3:
    case 6:
    case 9:
        break;
    case 1:
    case 4:
    case 7:
    case 10:
        SSL_CTX_clear_options(cctx, SSL_OP_ENABLE_MIDDLEBOX_COMPAT);
        break;
    case 2:
    case 5:
    case 8:
    case 11:
        SSL_CTX_clear_options(sctx, SSL_OP_ENABLE_MIDDLEBOX_COMPAT);
        break;
    default:
        TEST_error("Invalid test value");
        goto err;
    }

    if (tst >= 6) {
        /* Get a session suitable for early_data */
        if (!TEST_true(create_ssl_objects(sctx, cctx, &sssl, &cssl, NULL, NULL))
                || !TEST_true(create_ssl_connection(sssl, cssl, SSL_ERROR_NONE)))
            goto err;
        sess = SSL_get1_session(cssl);
        if (!TEST_ptr(sess))
            goto err;
        SSL_shutdown(cssl);
        SSL_shutdown(sssl);
        SSL_free(sssl);
        SSL_free(cssl);
        sssl = cssl = NULL;
    }

    if ((tst >= 3 && tst <= 5) || tst >= 9) {
        /* HRR handshake */
#if defined(OPENSSL_NO_EC)
# if !defined(OPENSSL_NO_DH)
        if (!TEST_true(SSL_CTX_set1_groups_list(sctx, "ffdhe3072")))
            goto err;
# endif
#else
        if (!TEST_true(SSL_CTX_set1_groups_list(sctx, "P-256")))
            goto err;
#endif
    }

    s_to_c_fbio = BIO_new(bio_f_watchccs_filter());
    c_to_s_fbio = BIO_new(bio_f_watchccs_filter());
    if (!TEST_ptr(s_to_c_fbio)
            || !TEST_ptr(c_to_s_fbio)) {
        BIO_free(s_to_c_fbio);
        BIO_free(c_to_s_fbio);
        goto err;
    }

    /* BIOs get freed on error */
    if (!TEST_true(create_ssl_objects(sctx, cctx, &sssl, &cssl, s_to_c_fbio,
                                      c_to_s_fbio)))
        goto err;

    if (tst >= 6) {
        /* Early data */
        if (!TEST_true(SSL_set_session(cssl, sess))
                || !TEST_true(SSL_write_early_data(cssl, msg, strlen(msg),
                                                   &written))
                || (tst <= 8
                    && !TEST_int_eq(SSL_read_early_data(sssl, buf,  sizeof(buf),
                                                &readbytes),
                                                SSL_READ_EARLY_DATA_SUCCESS)))
            goto err;
        if (tst <= 8) {
            if (!TEST_int_gt(SSL_connect(cssl), 0))
                goto err;
        } else {
            if (!TEST_int_le(SSL_connect(cssl), 0))
                goto err;
        }
        if (!TEST_int_eq(SSL_read_early_data(sssl, buf,  sizeof(buf),
                                             &readbytes),
                         SSL_READ_EARLY_DATA_FINISH))
            goto err;
    }

    /* Perform handshake (or complete it if doing early data ) */
    if (!TEST_true(create_ssl_connection(sssl, cssl, SSL_ERROR_NONE)))
        goto err;

    /*
     * Check there were no unexpected CCS messages, all record versions
     * were as expected, and that the session ids were reflected by the server
     * correctly.
     */
    if (!TEST_false(badccs) || !TEST_false(badvers) || !TEST_false(badsessid))
        goto err;

    switch (tst) {
    case 0:
        if (!TEST_true(sccsseen)
                || !TEST_true(ccsaftersh)
                || !TEST_false(ccsbeforesh)
                || !TEST_size_t_gt(chsessidlen, 0))
            goto err;
        break;

    case 1:
        if (!TEST_true(sccsseen)
                || !TEST_false(ccsaftersh)
                || !TEST_false(ccsbeforesh)
                || !TEST_size_t_eq(chsessidlen, 0))
            goto err;
        break;

    case 2:
        if (!TEST_false(sccsseen)
                || !TEST_true(ccsaftersh)
                || !TEST_false(ccsbeforesh)
                || !TEST_size_t_gt(chsessidlen, 0))
            goto err;
        break;

    case 3:
        if (!TEST_true(sccsseen)
                || !TEST_true(ccsaftersh)
                || !TEST_false(ccsbeforesh)
                || !TEST_size_t_gt(chsessidlen, 0))
            goto err;
        break;

    case 4:
        if (!TEST_true(sccsseen)
                || !TEST_false(ccsaftersh)
                || !TEST_false(ccsbeforesh)
                || !TEST_size_t_eq(chsessidlen, 0))
            goto err;
        break;

    case 5:
        if (!TEST_false(sccsseen)
                || !TEST_true(ccsaftersh)
                || !TEST_false(ccsbeforesh)
                || !TEST_size_t_gt(chsessidlen, 0))
            goto err;
        break;

    case 6:
        if (!TEST_true(sccsseen)
                || !TEST_false(ccsaftersh)
                || !TEST_true(ccsbeforesh)
                || !TEST_size_t_gt(chsessidlen, 0))
            goto err;
        break;

    case 7:
        if (!TEST_true(sccsseen)
                || !TEST_false(ccsaftersh)
                || !TEST_false(ccsbeforesh)
                || !TEST_size_t_eq(chsessidlen, 0))
            goto err;
        break;

    case 8:
        if (!TEST_false(sccsseen)
                || !TEST_false(ccsaftersh)
                || !TEST_true(ccsbeforesh)
                || !TEST_size_t_gt(chsessidlen, 0))
            goto err;
        break;

    case 9:
        if (!TEST_true(sccsseen)
                || !TEST_false(ccsaftersh)
                || !TEST_true(ccsbeforesh)
                || !TEST_size_t_gt(chsessidlen, 0))
            goto err;
        break;

    case 10:
        if (!TEST_true(sccsseen)
                || !TEST_false(ccsaftersh)
                || !TEST_false(ccsbeforesh)
                || !TEST_size_t_eq(chsessidlen, 0))
            goto err;
        break;

    case 11:
        if (!TEST_false(sccsseen)
                || !TEST_false(ccsaftersh)
                || !TEST_true(ccsbeforesh)
                || !TEST_size_t_gt(chsessidlen, 0))
            goto err;
        break;

    default:
        TEST_error("Invalid test value");
        goto err;
    }

    ret = 1;
 err:
    SSL_SESSION_free(sess);
    SSL_free(sssl);
    SSL_free(cssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);

    return ret;
}