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

/* Variables and functions */
 int /*<<< orphan*/  SSL3_RT_MAX_PLAIN_LENGTH ; 
 int /*<<< orphan*/  SSL_CTX_set_max_early_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_psk_find_session_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_psk_use_session_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_read_ahead (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_SESSION_set_max_early_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_SESSION_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get1_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_session (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_tlsext_host_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/ * clientpsk ; 
 int /*<<< orphan*/ * create_a_psk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_session_cb ; 
 scalar_t__ find_session_cb_cnt ; 
 int /*<<< orphan*/  privkey ; 
 int /*<<< orphan*/  pskid ; 
 int /*<<< orphan*/ * serverpsk ; 
 int /*<<< orphan*/  srvid ; 
 int /*<<< orphan*/  use_session_cb ; 
 scalar_t__ use_session_cb_cnt ; 

__attribute__((used)) static int setupearly_data_test(SSL_CTX **cctx, SSL_CTX **sctx, SSL **clientssl,
                                SSL **serverssl, SSL_SESSION **sess, int idx)
{
    if (*sctx == NULL
            && !TEST_true(create_ssl_ctx_pair(TLS_server_method(),
                                              TLS_client_method(),
                                              TLS1_VERSION, 0,
                                              sctx, cctx, cert, privkey)))
        return 0;

    if (!TEST_true(SSL_CTX_set_max_early_data(*sctx, SSL3_RT_MAX_PLAIN_LENGTH)))
        return 0;

    if (idx == 1) {
        /* When idx == 1 we repeat the tests with read_ahead set */
        SSL_CTX_set_read_ahead(*cctx, 1);
        SSL_CTX_set_read_ahead(*sctx, 1);
    } else if (idx == 2) {
        /* When idx == 2 we are doing early_data with a PSK. Set up callbacks */
        SSL_CTX_set_psk_use_session_callback(*cctx, use_session_cb);
        SSL_CTX_set_psk_find_session_callback(*sctx, find_session_cb);
        use_session_cb_cnt = 0;
        find_session_cb_cnt = 0;
        srvid = pskid;
    }

    if (!TEST_true(create_ssl_objects(*sctx, *cctx, serverssl, clientssl,
                                      NULL, NULL)))
        return 0;

    /*
     * For one of the run throughs (doesn't matter which one), we'll try sending
     * some SNI data in the initial ClientHello. This will be ignored (because
     * there is no SNI cb set up by the server), so it should not impact
     * early_data.
     */
    if (idx == 1
            && !TEST_true(SSL_set_tlsext_host_name(*clientssl, "localhost")))
        return 0;

    if (idx == 2) {
        clientpsk = create_a_psk(*clientssl);
        if (!TEST_ptr(clientpsk)
                   /*
                    * We just choose an arbitrary value for max_early_data which
                    * should be big enough for testing purposes.
                    */
                || !TEST_true(SSL_SESSION_set_max_early_data(clientpsk,
                                                             0x100))
                || !TEST_true(SSL_SESSION_up_ref(clientpsk))) {
            SSL_SESSION_free(clientpsk);
            clientpsk = NULL;
            return 0;
        }
        serverpsk = clientpsk;

        if (sess != NULL) {
            if (!TEST_true(SSL_SESSION_up_ref(clientpsk))) {
                SSL_SESSION_free(clientpsk);
                SSL_SESSION_free(serverpsk);
                clientpsk = serverpsk = NULL;
                return 0;
            }
            *sess = clientpsk;
        }
        return 1;
    }

    if (sess == NULL)
        return 1;

    if (!TEST_true(create_ssl_connection(*serverssl, *clientssl,
                                         SSL_ERROR_NONE)))
        return 0;

    *sess = SSL_get1_session(*clientssl);
    SSL_shutdown(*clientssl);
    SSL_shutdown(*serverssl);
    SSL_free(*serverssl);
    SSL_free(*clientssl);
    *serverssl = *clientssl = NULL;

    if (!TEST_true(create_ssl_objects(*sctx, *cctx, serverssl,
                                      clientssl, NULL, NULL))
            || !TEST_true(SSL_set_session(*clientssl, *sess)))
        return 0;

    return 1;
}