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
typedef  int /*<<< orphan*/  sess_id_ctx ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_sess_set_new_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_psk_find_session_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_psk_use_session_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_session_cache_mode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_session_id_context (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_SESSION_up_ref (int /*<<< orphan*/ *) ; 
 int SSL_SESS_CACHE_CLIENT ; 
 int SSL_SESS_CACHE_NO_INTERNAL_STORE ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_int_eq (int,scalar_t__) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/ * clientpsk ; 
 int /*<<< orphan*/ * create_a_psk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_session_cb ; 
 scalar_t__ find_session_cb_cnt ; 
 scalar_t__ new_called ; 
 int /*<<< orphan*/  new_session_cb ; 
 int /*<<< orphan*/  pskid ; 
 int /*<<< orphan*/ * serverpsk ; 
 int /*<<< orphan*/  srvid ; 
 int /*<<< orphan*/  use_session_cb ; 
 scalar_t__ use_session_cb_cnt ; 

__attribute__((used)) static int test_psk_tickets(void)
{
    SSL_CTX *sctx = NULL, *cctx = NULL;
    SSL *serverssl = NULL, *clientssl = NULL;
    int testresult = 0;
    int sess_id_ctx = 1;

    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(), TLS_client_method(),
                                       TLS1_VERSION, 0, &sctx,
                                       &cctx, NULL, NULL))
            || !TEST_true(SSL_CTX_set_session_id_context(sctx,
                                                         (void *)&sess_id_ctx,
                                                         sizeof(sess_id_ctx))))
        goto end;

    SSL_CTX_set_session_cache_mode(cctx, SSL_SESS_CACHE_CLIENT
                                         | SSL_SESS_CACHE_NO_INTERNAL_STORE);
    SSL_CTX_set_psk_use_session_callback(cctx, use_session_cb);
    SSL_CTX_set_psk_find_session_callback(sctx, find_session_cb);
    SSL_CTX_sess_set_new_cb(cctx, new_session_cb);
    use_session_cb_cnt = 0;
    find_session_cb_cnt = 0;
    srvid = pskid;
    new_called = 0;

    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                      NULL, NULL)))
        goto end;
    clientpsk = serverpsk = create_a_psk(clientssl);
    if (!TEST_ptr(clientpsk))
        goto end;
    SSL_SESSION_up_ref(clientpsk);

    if (!TEST_true(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_NONE))
            || !TEST_int_eq(1, find_session_cb_cnt)
            || !TEST_int_eq(1, use_session_cb_cnt)
               /* We should always get 1 ticket when using external PSK */
            || !TEST_int_eq(1, new_called))
        goto end;

    testresult = 1;

 end:
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);
    SSL_SESSION_free(clientpsk);
    SSL_SESSION_free(serverpsk);
    clientpsk = serverpsk = NULL;

    return testresult;
}