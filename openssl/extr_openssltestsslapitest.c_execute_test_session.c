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
 int /*<<< orphan*/  SSL_CTX_add_session (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_remove_session (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_sess_set_get_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_sess_set_new_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_sess_set_remove_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_max_proto_version (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_min_proto_version (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_session_cache_mode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_OP_NO_TICKET ; 
 int /*<<< orphan*/ * SSL_SESSION_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int SSL_SESS_CACHE_CLIENT ; 
 int SSL_SESS_CACHE_NO_INTERNAL_STORE ; 
 int SSL_SESS_CACHE_SERVER ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get1_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_session_reused (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_session (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (scalar_t__,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int TLS1_1_VERSION ; 
 int TLS1_2_VERSION ; 
 int TLS1_3_VERSION ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ get_called ; 
 int /*<<< orphan*/ * get_sess_val ; 
 int /*<<< orphan*/  get_session_cb ; 
 scalar_t__ new_called ; 
 int /*<<< orphan*/ * new_session_cb ; 
 int /*<<< orphan*/  privkey ; 
 scalar_t__ remove_called ; 
 int /*<<< orphan*/ * remove_session_cb ; 
 int /*<<< orphan*/  shutdown_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int execute_test_session(int maxprot, int use_int_cache,
                                int use_ext_cache)
{
    SSL_CTX *sctx = NULL, *cctx = NULL;
    SSL *serverssl1 = NULL, *clientssl1 = NULL;
    SSL *serverssl2 = NULL, *clientssl2 = NULL;
# ifndef OPENSSL_NO_TLS1_1
    SSL *serverssl3 = NULL, *clientssl3 = NULL;
# endif
    SSL_SESSION *sess1 = NULL, *sess2 = NULL;
    int testresult = 0, numnewsesstick = 1;

    new_called = remove_called = 0;

    /* TLSv1.3 sends 2 NewSessionTickets */
    if (maxprot == TLS1_3_VERSION)
        numnewsesstick = 2;

    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(), TLS_client_method(),
                                       TLS1_VERSION, 0,
                                       &sctx, &cctx, cert, privkey)))
        return 0;

    /*
     * Only allow the max protocol version so we can force a connection failure
     * later
     */
    SSL_CTX_set_min_proto_version(cctx, maxprot);
    SSL_CTX_set_max_proto_version(cctx, maxprot);

    /* Set up session cache */
    if (use_ext_cache) {
        SSL_CTX_sess_set_new_cb(cctx, new_session_cb);
        SSL_CTX_sess_set_remove_cb(cctx, remove_session_cb);
    }
    if (use_int_cache) {
        /* Also covers instance where both are set */
        SSL_CTX_set_session_cache_mode(cctx, SSL_SESS_CACHE_CLIENT);
    } else {
        SSL_CTX_set_session_cache_mode(cctx,
                                       SSL_SESS_CACHE_CLIENT
                                       | SSL_SESS_CACHE_NO_INTERNAL_STORE);
    }

    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl1, &clientssl1,
                                      NULL, NULL))
            || !TEST_true(create_ssl_connection(serverssl1, clientssl1,
                                                SSL_ERROR_NONE))
            || !TEST_ptr(sess1 = SSL_get1_session(clientssl1)))
        goto end;

    /* Should fail because it should already be in the cache */
    if (use_int_cache && !TEST_false(SSL_CTX_add_session(cctx, sess1)))
        goto end;
    if (use_ext_cache
            && (!TEST_int_eq(new_called, numnewsesstick)

                || !TEST_int_eq(remove_called, 0)))
        goto end;

    new_called = remove_called = 0;
    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl2,
                                      &clientssl2, NULL, NULL))
            || !TEST_true(SSL_set_session(clientssl2, sess1))
            || !TEST_true(create_ssl_connection(serverssl2, clientssl2,
                                                SSL_ERROR_NONE))
            || !TEST_true(SSL_session_reused(clientssl2)))
        goto end;

    if (maxprot == TLS1_3_VERSION) {
        /*
         * In TLSv1.3 we should have created a new session even though we have
         * resumed. Since we attempted a resume we should also have removed the
         * old ticket from the cache so that we try to only use tickets once.
         */
        if (use_ext_cache
                && (!TEST_int_eq(new_called, 1)
                    || !TEST_int_eq(remove_called, 1)))
            goto end;
    } else {
        /*
         * In TLSv1.2 we expect to have resumed so no sessions added or
         * removed.
         */
        if (use_ext_cache
                && (!TEST_int_eq(new_called, 0)
                    || !TEST_int_eq(remove_called, 0)))
            goto end;
    }

    SSL_SESSION_free(sess1);
    if (!TEST_ptr(sess1 = SSL_get1_session(clientssl2)))
        goto end;
    shutdown_ssl_connection(serverssl2, clientssl2);
    serverssl2 = clientssl2 = NULL;

    new_called = remove_called = 0;
    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl2,
                                      &clientssl2, NULL, NULL))
            || !TEST_true(create_ssl_connection(serverssl2, clientssl2,
                                                SSL_ERROR_NONE)))
        goto end;

    if (!TEST_ptr(sess2 = SSL_get1_session(clientssl2)))
        goto end;

    if (use_ext_cache
            && (!TEST_int_eq(new_called, numnewsesstick)
                || !TEST_int_eq(remove_called, 0)))
        goto end;

    new_called = remove_called = 0;
    /*
     * This should clear sess2 from the cache because it is a "bad" session.
     * See SSL_set_session() documentation.
     */
    if (!TEST_true(SSL_set_session(clientssl2, sess1)))
        goto end;
    if (use_ext_cache
            && (!TEST_int_eq(new_called, 0) || !TEST_int_eq(remove_called, 1)))
        goto end;
    if (!TEST_ptr_eq(SSL_get_session(clientssl2), sess1))
        goto end;

    if (use_int_cache) {
        /* Should succeeded because it should not already be in the cache */
        if (!TEST_true(SSL_CTX_add_session(cctx, sess2))
                || !TEST_true(SSL_CTX_remove_session(cctx, sess2)))
            goto end;
    }

    new_called = remove_called = 0;
    /* This shouldn't be in the cache so should fail */
    if (!TEST_false(SSL_CTX_remove_session(cctx, sess2)))
        goto end;

    if (use_ext_cache
            && (!TEST_int_eq(new_called, 0) || !TEST_int_eq(remove_called, 1)))
        goto end;

# if !defined(OPENSSL_NO_TLS1_1)
    new_called = remove_called = 0;
    /* Force a connection failure */
    SSL_CTX_set_max_proto_version(sctx, TLS1_1_VERSION);
    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl3,
                                      &clientssl3, NULL, NULL))
            || !TEST_true(SSL_set_session(clientssl3, sess1))
            /* This should fail because of the mismatched protocol versions */
            || !TEST_false(create_ssl_connection(serverssl3, clientssl3,
                                                 SSL_ERROR_NONE)))
        goto end;

    /* We should have automatically removed the session from the cache */
    if (use_ext_cache
            && (!TEST_int_eq(new_called, 0) || !TEST_int_eq(remove_called, 1)))
        goto end;

    /* Should succeed because it should not already be in the cache */
    if (use_int_cache && !TEST_true(SSL_CTX_add_session(cctx, sess2)))
        goto end;
# endif

    /* Now do some tests for server side caching */
    if (use_ext_cache) {
        SSL_CTX_sess_set_new_cb(cctx, NULL);
        SSL_CTX_sess_set_remove_cb(cctx, NULL);
        SSL_CTX_sess_set_new_cb(sctx, new_session_cb);
        SSL_CTX_sess_set_remove_cb(sctx, remove_session_cb);
        SSL_CTX_sess_set_get_cb(sctx, get_session_cb);
        get_sess_val = NULL;
    }

    SSL_CTX_set_session_cache_mode(cctx, 0);
    /* Internal caching is the default on the server side */
    if (!use_int_cache)
        SSL_CTX_set_session_cache_mode(sctx,
                                       SSL_SESS_CACHE_SERVER
                                       | SSL_SESS_CACHE_NO_INTERNAL_STORE);

    SSL_free(serverssl1);
    SSL_free(clientssl1);
    serverssl1 = clientssl1 = NULL;
    SSL_free(serverssl2);
    SSL_free(clientssl2);
    serverssl2 = clientssl2 = NULL;
    SSL_SESSION_free(sess1);
    sess1 = NULL;
    SSL_SESSION_free(sess2);
    sess2 = NULL;

    SSL_CTX_set_max_proto_version(sctx, maxprot);
    if (maxprot == TLS1_2_VERSION)
        SSL_CTX_set_options(sctx, SSL_OP_NO_TICKET);
    new_called = remove_called = get_called = 0;
    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl1, &clientssl1,
                                      NULL, NULL))
            || !TEST_true(create_ssl_connection(serverssl1, clientssl1,
                                                SSL_ERROR_NONE))
            || !TEST_ptr(sess1 = SSL_get1_session(clientssl1))
            || !TEST_ptr(sess2 = SSL_get1_session(serverssl1)))
        goto end;

    if (use_int_cache) {
        if (maxprot == TLS1_3_VERSION && !use_ext_cache) {
            /*
             * In TLSv1.3 it should not have been added to the internal cache,
             * except in the case where we also have an external cache (in that
             * case it gets added to the cache in order to generate remove
             * events after timeout).
             */
            if (!TEST_false(SSL_CTX_remove_session(sctx, sess2)))
                goto end;
        } else {
            /* Should fail because it should already be in the cache */
            if (!TEST_false(SSL_CTX_add_session(sctx, sess2)))
                goto end;
        }
    }

    if (use_ext_cache) {
        SSL_SESSION *tmp = sess2;

        if (!TEST_int_eq(new_called, numnewsesstick)
                || !TEST_int_eq(remove_called, 0)
                || !TEST_int_eq(get_called, 0))
            goto end;
        /*
         * Delete the session from the internal cache to force a lookup from
         * the external cache. We take a copy first because
         * SSL_CTX_remove_session() also marks the session as non-resumable.
         */
        if (use_int_cache && maxprot != TLS1_3_VERSION) {
            if (!TEST_ptr(tmp = SSL_SESSION_dup(sess2))
                    || !TEST_true(SSL_CTX_remove_session(sctx, sess2)))
                goto end;
            SSL_SESSION_free(sess2);
        }
        sess2 = tmp;
    }

    new_called = remove_called = get_called = 0;
    get_sess_val = sess2;
    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl2,
                                      &clientssl2, NULL, NULL))
            || !TEST_true(SSL_set_session(clientssl2, sess1))
            || !TEST_true(create_ssl_connection(serverssl2, clientssl2,
                                                SSL_ERROR_NONE))
            || !TEST_true(SSL_session_reused(clientssl2)))
        goto end;

    if (use_ext_cache) {
        if (!TEST_int_eq(remove_called, 0))
            goto end;

        if (maxprot == TLS1_3_VERSION) {
            if (!TEST_int_eq(new_called, 1)
                    || !TEST_int_eq(get_called, 0))
                goto end;
        } else {
            if (!TEST_int_eq(new_called, 0)
                    || !TEST_int_eq(get_called, 1))
                goto end;
        }
    }

    testresult = 1;

 end:
    SSL_free(serverssl1);
    SSL_free(clientssl1);
    SSL_free(serverssl2);
    SSL_free(clientssl2);
# ifndef OPENSSL_NO_TLS1_1
    SSL_free(serverssl3);
    SSL_free(clientssl3);
# endif
    SSL_SESSION_free(sess1);
    SSL_SESSION_free(sess2);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);

    return testresult;
}