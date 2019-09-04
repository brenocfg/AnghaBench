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
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ BIO_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int CLI_TO_SRV_EPOCH_0_RECS ; 
 int CLI_TO_SRV_EPOCH_1_RECS ; 
 int CLI_TO_SRV_RESUME_EPOCH_0_RECS ; 
 int CLI_TO_SRV_RESUME_EPOCH_1_RECS ; 
 int /*<<< orphan*/  DTLS1_VERSION ; 
 int /*<<< orphan*/  DTLS_client_method () ; 
 int /*<<< orphan*/  DTLS_server_method () ; 
 int /*<<< orphan*/  DTLS_set_timer_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMPACKET_CTRL_GET_DROP_REC ; 
 int /*<<< orphan*/  MEMPACKET_CTRL_SET_DROP_EPOCH ; 
 int /*<<< orphan*/  MEMPACKET_CTRL_SET_DROP_REC ; 
 int SRV_TO_CLI_EPOCH_0_RECS ; 
 int SRV_TO_CLI_RESUME_EPOCH_0_RECS ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get1_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get_wbio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_session_reused (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_session (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_int_eq (int,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int TOTAL_FULL_HAND_RECORDS ; 
 int /*<<< orphan*/  bio_f_tls_dump_filter () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  privkey ; 
 int /*<<< orphan*/  timer_cb ; 

__attribute__((used)) static int test_dtls_drop_records(int idx)
{
    SSL_CTX *sctx = NULL, *cctx = NULL;
    SSL *serverssl = NULL, *clientssl = NULL;
    BIO *c_to_s_fbio, *mempackbio;
    int testresult = 0;
    int epoch = 0;
    SSL_SESSION *sess = NULL;
    int cli_to_srv_epoch0, cli_to_srv_epoch1, srv_to_cli_epoch0;

    if (!TEST_true(create_ssl_ctx_pair(DTLS_server_method(),
                                       DTLS_client_method(),
                                       DTLS1_VERSION, 0,
                                       &sctx, &cctx, cert, privkey)))
        return 0;

    if (idx >= TOTAL_FULL_HAND_RECORDS) {
        /* We're going to do a resumption handshake. Get a session first. */
        if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                          NULL, NULL))
                || !TEST_true(create_ssl_connection(serverssl, clientssl,
                              SSL_ERROR_NONE))
                || !TEST_ptr(sess = SSL_get1_session(clientssl)))
            goto end;

        SSL_shutdown(clientssl);
        SSL_shutdown(serverssl);
        SSL_free(serverssl);
        SSL_free(clientssl);
        serverssl = clientssl = NULL;

        cli_to_srv_epoch0 = CLI_TO_SRV_RESUME_EPOCH_0_RECS;
        cli_to_srv_epoch1 = CLI_TO_SRV_RESUME_EPOCH_1_RECS;
        srv_to_cli_epoch0 = SRV_TO_CLI_RESUME_EPOCH_0_RECS;
        idx -= TOTAL_FULL_HAND_RECORDS;
    } else {
        cli_to_srv_epoch0 = CLI_TO_SRV_EPOCH_0_RECS;
        cli_to_srv_epoch1 = CLI_TO_SRV_EPOCH_1_RECS;
        srv_to_cli_epoch0 = SRV_TO_CLI_EPOCH_0_RECS;
    }

    c_to_s_fbio = BIO_new(bio_f_tls_dump_filter());
    if (!TEST_ptr(c_to_s_fbio))
        goto end;

    /* BIO is freed by create_ssl_connection on error */
    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                      NULL, c_to_s_fbio)))
        goto end;

    if (sess != NULL) {
        if (!TEST_true(SSL_set_session(clientssl, sess)))
            goto end;
    }

    DTLS_set_timer_cb(clientssl, timer_cb);
    DTLS_set_timer_cb(serverssl, timer_cb);

    /* Work out which record to drop based on the test number */
    if (idx >= cli_to_srv_epoch0 + cli_to_srv_epoch1) {
        mempackbio = SSL_get_wbio(serverssl);
        idx -= cli_to_srv_epoch0 + cli_to_srv_epoch1;
        if (idx >= srv_to_cli_epoch0) {
            epoch = 1;
            idx -= srv_to_cli_epoch0;
        }
    } else {
        mempackbio = SSL_get_wbio(clientssl);
        if (idx >= cli_to_srv_epoch0) {
            epoch = 1;
            idx -= cli_to_srv_epoch0;
        }
         mempackbio = BIO_next(mempackbio);
    }
    BIO_ctrl(mempackbio, MEMPACKET_CTRL_SET_DROP_EPOCH, epoch, NULL);
    BIO_ctrl(mempackbio, MEMPACKET_CTRL_SET_DROP_REC, idx, NULL);

    if (!TEST_true(create_ssl_connection(serverssl, clientssl, SSL_ERROR_NONE)))
        goto end;

    if (sess != NULL && !TEST_true(SSL_session_reused(clientssl)))
        goto end;

    /* If the test did what we planned then it should have dropped a record */
    if (!TEST_int_eq((int)BIO_ctrl(mempackbio, MEMPACKET_CTRL_GET_DROP_REC, 0,
                                   NULL), -1))
        goto end;

    testresult = 1;
 end:
    SSL_SESSION_free(sess);
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);

    return testresult;
}