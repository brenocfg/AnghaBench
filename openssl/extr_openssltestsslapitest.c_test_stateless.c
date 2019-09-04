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
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_clear_options (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_stateless_cookie_generate_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_stateless_cookie_verify_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_ERROR_WANT_READ ; 
 int /*<<< orphan*/  SSL_OP_ENABLE_MIDDLEBOX_COMPAT ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_stateless (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generate_stateless_cookie_callback ; 
 int /*<<< orphan*/  privkey ; 
 int /*<<< orphan*/  shutdown_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_stateless_cookie_callback ; 

__attribute__((used)) static int test_stateless(void)
{
    SSL_CTX *sctx = NULL, *cctx = NULL;
    SSL *serverssl = NULL, *clientssl = NULL;
    int testresult = 0;

    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(), TLS_client_method(),
                                       TLS1_VERSION, 0,
                                       &sctx, &cctx, cert, privkey)))
        goto end;

    /* The arrival of CCS messages can confuse the test */
    SSL_CTX_clear_options(cctx, SSL_OP_ENABLE_MIDDLEBOX_COMPAT);

    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                      NULL, NULL))
               /* Send the first ClientHello */
            || !TEST_false(create_ssl_connection(serverssl, clientssl,
                                                 SSL_ERROR_WANT_READ))
               /*
                * This should fail with a -1 return because we have no callbacks
                * set up
                */
            || !TEST_int_eq(SSL_stateless(serverssl), -1))
        goto end;

    /* Fatal error so abandon the connection from this client */
    SSL_free(clientssl);
    clientssl = NULL;

    /* Set up the cookie generation and verification callbacks */
    SSL_CTX_set_stateless_cookie_generate_cb(sctx, generate_stateless_cookie_callback);
    SSL_CTX_set_stateless_cookie_verify_cb(sctx, verify_stateless_cookie_callback);

    /*
     * Create a new connection from the client (we can reuse the server SSL
     * object).
     */
    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                             NULL, NULL))
               /* Send the first ClientHello */
            || !TEST_false(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_WANT_READ))
               /* This should fail because there is no cookie */
            || !TEST_int_eq(SSL_stateless(serverssl), 0))
        goto end;

    /* Abandon the connection from this client */
    SSL_free(clientssl);
    clientssl = NULL;

    /*
     * Now create a connection from a new client but with the same server SSL
     * object
     */
    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                             NULL, NULL))
               /* Send the first ClientHello */
            || !TEST_false(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_WANT_READ))
               /* This should fail because there is no cookie */
            || !TEST_int_eq(SSL_stateless(serverssl), 0)
               /* Send the second ClientHello */
            || !TEST_false(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_WANT_READ))
               /* This should succeed because a cookie is now present */
            || !TEST_int_eq(SSL_stateless(serverssl), 1)
               /* Complete the connection */
            || !TEST_true(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_NONE)))
        goto end;

    shutdown_ssl_connection(serverssl, clientssl);
    serverssl = clientssl = NULL;
    testresult = 1;

 end:
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);
    return testresult;

}