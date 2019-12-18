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
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_post_handshake_auth (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int SSL_ERROR_SSL ; 
 int SSL_ERROR_ZERO_RETURN ; 
 int /*<<< orphan*/  SSL_KEY_UPDATE_REQUESTED ; 
 int SSL_RECEIVED_SHUTDOWN ; 
 int /*<<< orphan*/  SSL_SESSION_is_resumable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_VERIFY_PEER ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get_error (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * SSL_get_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_key_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_read_ex (int /*<<< orphan*/ *,char*,int,size_t*) ; 
 int /*<<< orphan*/  SSL_set_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_verify_client_post_handshake (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  SSL_write_ex (int /*<<< orphan*/ *,char*,int,size_t*) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ptr_ne (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_size_t_eq (size_t,int) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_2_VERSION ; 
 int /*<<< orphan*/  TLS1_3_VERSION ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_bare_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (char*,char*,size_t) ; 
 int /*<<< orphan*/  privkey ; 

__attribute__((used)) static int test_shutdown(int tst)
{
    SSL_CTX *cctx = NULL, *sctx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    int testresult = 0;
    char msg[] = "A test message";
    char buf[80];
    size_t written, readbytes;
    SSL_SESSION *sess;

#ifdef OPENSSL_NO_TLS1_2
    if (tst <= 1)
        return 1;
#endif
#ifdef OPENSSL_NO_TLS1_3
    if (tst >= 2)
        return 1;
#endif

    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(),
                                       TLS_client_method(),
                                       TLS1_VERSION,
                                       (tst <= 1) ? TLS1_2_VERSION
                                                  : TLS1_3_VERSION,
                                       &sctx, &cctx, cert, privkey)))
        goto end;

    if (tst == 5)
        SSL_CTX_set_post_handshake_auth(cctx, 1);

    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                             NULL, NULL)))
        goto end;

    if (tst == 3) {
        if (!TEST_true(create_bare_ssl_connection(serverssl, clientssl,
                                                  SSL_ERROR_NONE, 1))
                || !TEST_ptr_ne(sess = SSL_get_session(clientssl), NULL)
                || !TEST_false(SSL_SESSION_is_resumable(sess)))
            goto end;
    } else if (!TEST_true(create_ssl_connection(serverssl, clientssl,
                                              SSL_ERROR_NONE))
            || !TEST_ptr_ne(sess = SSL_get_session(clientssl), NULL)
            || !TEST_true(SSL_SESSION_is_resumable(sess))) {
        goto end;
    }

    if (!TEST_int_eq(SSL_shutdown(clientssl), 0))
        goto end;

    if (tst >= 4) {
        /*
         * Reading on the server after the client has sent close_notify should
         * fail and provide SSL_ERROR_ZERO_RETURN
         */
        if (!TEST_false(SSL_read_ex(serverssl, buf, sizeof(buf), &readbytes))
                || !TEST_int_eq(SSL_get_error(serverssl, 0),
                                SSL_ERROR_ZERO_RETURN)
                || !TEST_int_eq(SSL_get_shutdown(serverssl),
                                SSL_RECEIVED_SHUTDOWN)
                   /*
                    * Even though we're shutdown on receive we should still be
                    * able to write.
                    */
                || !TEST_true(SSL_write(serverssl, msg, sizeof(msg))))
            goto end;
        if (tst == 4
                && !TEST_true(SSL_key_update(serverssl,
                                             SSL_KEY_UPDATE_REQUESTED)))
            goto end;
        if (tst == 5) {
            SSL_set_verify(serverssl, SSL_VERIFY_PEER, NULL);
            if (!TEST_true(SSL_verify_client_post_handshake(serverssl)))
                goto end;
        }
        if ((tst == 4 || tst == 5)
                && !TEST_true(SSL_write(serverssl, msg, sizeof(msg))))
            goto end;
        if (!TEST_int_eq(SSL_shutdown(serverssl), 1))
            goto end;
        if (tst == 4 || tst == 5) {
            /* Should still be able to read data from server */
            if (!TEST_true(SSL_read_ex(clientssl, buf, sizeof(buf),
                                       &readbytes))
                    || !TEST_size_t_eq(readbytes, sizeof(msg))
                    || !TEST_int_eq(memcmp(msg, buf, readbytes), 0)
                    || !TEST_true(SSL_read_ex(clientssl, buf, sizeof(buf),
                                              &readbytes))
                    || !TEST_size_t_eq(readbytes, sizeof(msg))
                    || !TEST_int_eq(memcmp(msg, buf, readbytes), 0))
                goto end;
        }
    }

    /* Writing on the client after sending close_notify shouldn't be possible */
    if (!TEST_false(SSL_write_ex(clientssl, msg, sizeof(msg), &written)))
        goto end;

    if (tst < 4) {
        /*
         * For these tests the client has sent close_notify but it has not yet
         * been received by the server. The server has not sent close_notify
         * yet.
         */
        if (!TEST_int_eq(SSL_shutdown(serverssl), 0)
                   /*
                    * Writing on the server after sending close_notify shouldn't
                    * be possible.
                    */
                || !TEST_false(SSL_write_ex(serverssl, msg, sizeof(msg), &written))
                || !TEST_int_eq(SSL_shutdown(clientssl), 1)
                || !TEST_ptr_ne(sess = SSL_get_session(clientssl), NULL)
                || !TEST_true(SSL_SESSION_is_resumable(sess))
                || !TEST_int_eq(SSL_shutdown(serverssl), 1))
            goto end;
    } else if (tst == 4 || tst == 5) {
        /*
         * In this test the client has sent close_notify and it has been
         * received by the server which has responded with a close_notify. The
         * client needs to read the close_notify sent by the server.
         */
        if (!TEST_int_eq(SSL_shutdown(clientssl), 1)
                || !TEST_ptr_ne(sess = SSL_get_session(clientssl), NULL)
                || !TEST_true(SSL_SESSION_is_resumable(sess)))
            goto end;
    } else {
        /*
         * tst == 6
         *
         * The client has sent close_notify and is expecting a close_notify
         * back, but instead there is application data first. The shutdown
         * should fail with a fatal error.
         */
        if (!TEST_int_eq(SSL_shutdown(clientssl), -1)
                || !TEST_int_eq(SSL_get_error(clientssl, -1), SSL_ERROR_SSL))
            goto end;
    }

    testresult = 1;

 end:
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);

    return testresult;
}