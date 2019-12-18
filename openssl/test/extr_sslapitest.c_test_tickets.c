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
 size_t OSSL_NELEM (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_post_handshake_auth (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_int_eq (int,scalar_t__) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_resumption (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int do_cache ; 
 scalar_t__ new_called ; 
 int /*<<< orphan*/  post_handshake_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** sesscache ; 
 int /*<<< orphan*/  setup_ticket_test (int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int test_tickets(int stateful, int idx)
{
    SSL_CTX *sctx = NULL, *cctx = NULL;
    SSL *serverssl = NULL, *clientssl = NULL;
    int testresult = 0;
    size_t j;

    /* idx is the test number, but also the number of tickets we want */

    new_called = 0;
    do_cache = 1;

    if (!setup_ticket_test(stateful, idx, &sctx, &cctx))
        goto end;

    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl,
                                          &clientssl, NULL, NULL)))
        goto end;

    if (!TEST_true(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_NONE))
               /* Check we got the number of tickets we were expecting */
            || !TEST_int_eq(idx, new_called))
        goto end;

    SSL_shutdown(clientssl);
    SSL_shutdown(serverssl);
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);
    clientssl = serverssl = NULL;
    sctx = cctx = NULL;

    /*
     * Now we try to resume with the tickets we previously created. The
     * resumption attempt is expected to fail (because we're now using a new
     * SSL_CTX). We should see idx number of tickets issued again.
     */

    /* Stop caching sessions - just count them */
    do_cache = 0;

    if (!setup_ticket_test(stateful, idx, &sctx, &cctx))
        goto end;

    if (!check_resumption(idx, sctx, cctx, 0))
        goto end;

    /* Start again with caching sessions */
    new_called = 0;
    do_cache = 1;
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);
    sctx = cctx = NULL;

    if (!setup_ticket_test(stateful, idx, &sctx, &cctx))
        goto end;

    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl,
                                          &clientssl, NULL, NULL)))
        goto end;

    SSL_set_post_handshake_auth(clientssl, 1);

    if (!TEST_true(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_NONE))
               /* Check we got the number of tickets we were expecting */
            || !TEST_int_eq(idx, new_called))
        goto end;

    /* After a post-handshake authentication we should get new tickets issued */
    if (!post_handshake_verify(serverssl, clientssl)
            || !TEST_int_eq(idx * 2, new_called))
        goto end;

    SSL_shutdown(clientssl);
    SSL_shutdown(serverssl);
    SSL_free(serverssl);
    SSL_free(clientssl);
    serverssl = clientssl = NULL;

    /* Stop caching sessions - just count them */
    do_cache = 0;

    /*
     * Check we can resume with all the tickets we created. This time around the
     * resumptions should all be successful.
     */
    if (!check_resumption(idx, sctx, cctx, 1))
        goto end;

    testresult = 1;

 end:
    SSL_free(serverssl);
    SSL_free(clientssl);
    for (j = 0; j < OSSL_NELEM(sesscache); j++) {
        SSL_SESSION_free(sesscache[j]);
        sesscache[j] = NULL;
    }
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);

    return testresult;
}