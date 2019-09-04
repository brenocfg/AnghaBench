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
 int /*<<< orphan*/  MSG1 ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_info_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_EARLY_DATA_ACCEPTED ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_READ_EARLY_DATA_SUCCESS ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get1_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get_early_data_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_read_early_data (int /*<<< orphan*/ *,unsigned char*,int,size_t*) ; 
 int /*<<< orphan*/  SSL_session_reused (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_info_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_session (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_write_early_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  TEST_false (scalar_t__) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (int /*<<< orphan*/ ,size_t,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_size_t_eq (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int TLS1_2_VERSION ; 
 int TLS1_3_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ info_cb_failed ; 
 int info_cb_offset ; 
 int info_cb_this_state ; 
 int /*<<< orphan*/  privkey ; 
 int /*<<< orphan*/  setupearly_data_test (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sslapi_info_callback ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_info_callback(int tst)
{
    SSL_CTX *cctx = NULL, *sctx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    SSL_SESSION *clntsess = NULL;
    int testresult = 0;
    int tlsvers;

    if (tst < 2) {
/* We need either ECDHE or DHE for the TLSv1.2 test to work */
#if !defined(OPENSSL_NO_TLS1_2) && (!defined(OPENSSL_NO_EC) \
                                    || !defined(OPENSSL_NO_DH))
        tlsvers = TLS1_2_VERSION;
#else
        return 1;
#endif
    } else {
#ifndef OPENSSL_NO_TLS1_3
        tlsvers = TLS1_3_VERSION;
#else
        return 1;
#endif
    }

    /* Reset globals */
    info_cb_failed = 0;
    info_cb_this_state = -1;
    info_cb_offset = tst;

#ifndef OPENSSL_NO_TLS1_3
    if (tst >= 4) {
        SSL_SESSION *sess = NULL;
        size_t written, readbytes;
        unsigned char buf[80];

        /* early_data tests */
        if (!TEST_true(setupearly_data_test(&cctx, &sctx, &clientssl,
                                            &serverssl, &sess, 0)))
            goto end;

        /* We don't actually need this reference */
        SSL_SESSION_free(sess);

        SSL_set_info_callback((tst % 2) == 0 ? serverssl : clientssl,
                              sslapi_info_callback);

        /* Write and read some early data and then complete the connection */
        if (!TEST_true(SSL_write_early_data(clientssl, MSG1, strlen(MSG1),
                                            &written))
                || !TEST_size_t_eq(written, strlen(MSG1))
                || !TEST_int_eq(SSL_read_early_data(serverssl, buf,
                                                    sizeof(buf), &readbytes),
                                SSL_READ_EARLY_DATA_SUCCESS)
                || !TEST_mem_eq(MSG1, readbytes, buf, strlen(MSG1))
                || !TEST_int_eq(SSL_get_early_data_status(serverssl),
                                SSL_EARLY_DATA_ACCEPTED)
                || !TEST_true(create_ssl_connection(serverssl, clientssl,
                                                    SSL_ERROR_NONE))
                || !TEST_false(info_cb_failed))
            goto end;

        testresult = 1;
        goto end;
    }
#endif

    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(),
                                       TLS_client_method(),
                                       tlsvers, tlsvers, &sctx, &cctx, cert,
                                       privkey)))
        goto end;

    /*
     * For even numbered tests we check the server callbacks. For odd numbers we
     * check the client.
     */
    SSL_CTX_set_info_callback((tst % 2) == 0 ? sctx : cctx,
                              sslapi_info_callback);

    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl,
                                          &clientssl, NULL, NULL))
        || !TEST_true(create_ssl_connection(serverssl, clientssl,
                                            SSL_ERROR_NONE))
        || !TEST_false(info_cb_failed))
    goto end;



    clntsess = SSL_get1_session(clientssl);
    SSL_shutdown(clientssl);
    SSL_shutdown(serverssl);
    SSL_free(serverssl);
    SSL_free(clientssl);
    serverssl = clientssl = NULL;

    /* Now do a resumption */
    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl, NULL,
                                      NULL))
            || !TEST_true(SSL_set_session(clientssl, clntsess))
            || !TEST_true(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_NONE))
            || !TEST_true(SSL_session_reused(clientssl))
            || !TEST_false(info_cb_failed))
        goto end;

    testresult = 1;

 end:
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_SESSION_free(clntsess);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);
    return testresult;
}