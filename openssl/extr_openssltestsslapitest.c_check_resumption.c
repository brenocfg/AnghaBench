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
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_session_reused (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_post_handshake_auth (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_set_session (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (scalar_t__,int) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ new_called ; 
 int /*<<< orphan*/  post_handshake_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** sesscache ; 

__attribute__((used)) static int check_resumption(int idx, SSL_CTX *sctx, SSL_CTX *cctx, int succ)
{
    SSL *serverssl = NULL, *clientssl = NULL;
    int i;

    /* Test that we can resume with all the tickets we got given */
    for (i = 0; i < idx * 2; i++) {
        new_called = 0;
        if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl,
                                              &clientssl, NULL, NULL))
                || !TEST_true(SSL_set_session(clientssl, sesscache[i])))
            goto end;

        SSL_set_post_handshake_auth(clientssl, 1);

        if (!TEST_true(create_ssl_connection(serverssl, clientssl,
                                                    SSL_ERROR_NONE)))
            goto end;

        /*
         * Following a successful resumption we only get 1 ticket. After a
         * failed one we should get idx tickets.
         */
        if (succ) {
            if (!TEST_true(SSL_session_reused(clientssl))
                    || !TEST_int_eq(new_called, 1))
                goto end;
        } else {
            if (!TEST_false(SSL_session_reused(clientssl))
                    || !TEST_int_eq(new_called, idx))
                goto end;
        }

        new_called = 0;
        /* After a post-handshake authentication we should get 1 new ticket */
        if (succ
                && (!post_handshake_verify(serverssl, clientssl)
                    || !TEST_int_eq(new_called, 1)))
            goto end;

        SSL_shutdown(clientssl);
        SSL_shutdown(serverssl);
        SSL_free(serverssl);
        SSL_free(clientssl);
        serverssl = clientssl = NULL;
        SSL_SESSION_free(sesscache[i]);
        sesscache[i] = NULL;
    }

    return 1;

 end:
    SSL_free(clientssl);
    SSL_free(serverssl);
    return 0;
}