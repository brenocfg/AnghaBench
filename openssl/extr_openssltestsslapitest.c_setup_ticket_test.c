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

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_sess_set_new_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_num_tickets (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_session_cache_mode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_session_id_context (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  SSL_OP_NO_TICKET ; 
 int SSL_SESS_CACHE_CLIENT ; 
 int SSL_SESS_CACHE_NO_INTERNAL_STORE ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_cachesession_cb ; 
 int /*<<< orphan*/  privkey ; 

__attribute__((used)) static int setup_ticket_test(int stateful, int idx, SSL_CTX **sctx,
                             SSL_CTX **cctx)
{
    int sess_id_ctx = 1;

    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(), TLS_client_method(),
                                       TLS1_VERSION, 0, sctx,
                                       cctx, cert, privkey))
            || !TEST_true(SSL_CTX_set_num_tickets(*sctx, idx))
            || !TEST_true(SSL_CTX_set_session_id_context(*sctx,
                                                         (void *)&sess_id_ctx,
                                                         sizeof(sess_id_ctx))))
        return 0;

    if (stateful)
        SSL_CTX_set_options(*sctx, SSL_OP_NO_TICKET);

    SSL_CTX_set_session_cache_mode(*cctx, SSL_SESS_CACHE_CLIENT
                                          | SSL_SESS_CACHE_NO_INTERNAL_STORE);
    SSL_CTX_sess_set_new_cb(*cctx, new_cachesession_cb);

    return 1;
}