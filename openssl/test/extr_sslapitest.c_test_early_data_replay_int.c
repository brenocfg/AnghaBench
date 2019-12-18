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
typedef  int /*<<< orphan*/  SSL_CONF_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  MSG1 ; 
 int /*<<< orphan*/  SSL_CONF_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CONF_CTX_new () ; 
 int /*<<< orphan*/  SSL_CONF_CTX_set_flags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CONF_CTX_set_ssl_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SSL_CONF_FLAG_FILE ; 
 int SSL_CONF_FLAG_SERVER ; 
 scalar_t__ SSL_CONF_cmd (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_allow_early_data_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SSL_EARLY_DATA_ACCEPTED ; 
 int SSL_EARLY_DATA_REJECTED ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_OP_NO_ANTI_REPLAY ; 
 int SSL_READ_EARLY_DATA_FINISH ; 
 int SSL_READ_EARLY_DATA_SUCCESS ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_connect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_get_early_data_status (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_read_early_data (int /*<<< orphan*/ *,unsigned char*,int,size_t*) ; 
 scalar_t__ SSL_session_reused (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_set_session (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_write_early_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  TEST_int_eq (scalar_t__,int) ; 
 int /*<<< orphan*/  TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_size_t_eq (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (scalar_t__) ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  allow_early_data_cb ; 
 scalar_t__ allow_ed_cb_called ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/ * clientpsk ; 
 scalar_t__ create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  privkey ; 
 int /*<<< orphan*/ * serverpsk ; 
 scalar_t__ setupearly_data_test (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_early_data_replay_int(int idx, int usecb, int confopt)
{
    SSL_CTX *cctx = NULL, *sctx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    int testresult = 0;
    SSL_SESSION *sess = NULL;
    size_t readbytes, written;
    unsigned char buf[20];

    allow_ed_cb_called = 0;

    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(), TLS_client_method(),
                                       TLS1_VERSION, 0, &sctx,
                                       &cctx, cert, privkey)))
        return 0;

    if (usecb > 0) {
        if (confopt == 0) {
            SSL_CTX_set_options(sctx, SSL_OP_NO_ANTI_REPLAY);
        } else {
            SSL_CONF_CTX *confctx = SSL_CONF_CTX_new();

            if (!TEST_ptr(confctx))
                goto end;
            SSL_CONF_CTX_set_flags(confctx, SSL_CONF_FLAG_FILE
                                            | SSL_CONF_FLAG_SERVER);
            SSL_CONF_CTX_set_ssl_ctx(confctx, sctx);
            if (!TEST_int_eq(SSL_CONF_cmd(confctx, "Options", "-AntiReplay"),
                             2)) {
                SSL_CONF_CTX_free(confctx);
                goto end;
            }
            SSL_CONF_CTX_free(confctx);
        }
        SSL_CTX_set_allow_early_data_cb(sctx, allow_early_data_cb, &usecb);
    }

    if (!TEST_true(setupearly_data_test(&cctx, &sctx, &clientssl,
                                        &serverssl, &sess, idx)))
        goto end;

    /*
     * The server is configured to accept early data. Create a connection to
     * "use up" the ticket
     */
    if (!TEST_true(create_ssl_connection(serverssl, clientssl, SSL_ERROR_NONE))
            || !TEST_true(SSL_session_reused(clientssl)))
        goto end;

    SSL_shutdown(clientssl);
    SSL_shutdown(serverssl);
    SSL_free(serverssl);
    SSL_free(clientssl);
    serverssl = clientssl = NULL;

    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl,
                                      &clientssl, NULL, NULL))
            || !TEST_true(SSL_set_session(clientssl, sess)))
        goto end;

    /* Write and read some early data */
    if (!TEST_true(SSL_write_early_data(clientssl, MSG1, strlen(MSG1),
                                        &written))
            || !TEST_size_t_eq(written, strlen(MSG1)))
        goto end;

    if (usecb <= 1) {
        if (!TEST_int_eq(SSL_read_early_data(serverssl, buf, sizeof(buf),
                                             &readbytes),
                         SSL_READ_EARLY_DATA_FINISH)
                   /*
                    * The ticket was reused, so the we should have rejected the
                    * early data
                    */
                || !TEST_int_eq(SSL_get_early_data_status(serverssl),
                                SSL_EARLY_DATA_REJECTED))
            goto end;
    } else {
        /* In this case the callback decides to accept the early data */
        if (!TEST_int_eq(SSL_read_early_data(serverssl, buf, sizeof(buf),
                                             &readbytes),
                         SSL_READ_EARLY_DATA_SUCCESS)
                || !TEST_mem_eq(MSG1, strlen(MSG1), buf, readbytes)
                   /*
                    * Server will have sent its flight so client can now send
                    * end of early data and complete its half of the handshake
                    */
                || !TEST_int_gt(SSL_connect(clientssl), 0)
                || !TEST_int_eq(SSL_read_early_data(serverssl, buf, sizeof(buf),
                                             &readbytes),
                                SSL_READ_EARLY_DATA_FINISH)
                || !TEST_int_eq(SSL_get_early_data_status(serverssl),
                                SSL_EARLY_DATA_ACCEPTED))
            goto end;
    }

    /* Complete the connection */
    if (!TEST_true(create_ssl_connection(serverssl, clientssl, SSL_ERROR_NONE))
            || !TEST_int_eq(SSL_session_reused(clientssl), (usecb > 0) ? 1 : 0)
            || !TEST_int_eq(allow_ed_cb_called, usecb > 0 ? 1 : 0))
        goto end;

    testresult = 1;

 end:
    SSL_SESSION_free(sess);
    SSL_SESSION_free(clientpsk);
    SSL_SESSION_free(serverpsk);
    clientpsk = serverpsk = NULL;
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);
    return testresult;
}