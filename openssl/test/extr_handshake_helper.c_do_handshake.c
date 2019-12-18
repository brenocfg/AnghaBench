#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ result; } ;
struct TYPE_8__ {scalar_t__ handshake_mode; int /*<<< orphan*/  resume_extra; int /*<<< orphan*/  extra; } ;
typedef  TYPE_1__ SSL_TEST_CTX ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  TYPE_2__ HANDSHAKE_RESULT ;

/* Variables and functions */
 int /*<<< orphan*/  HANDSHAKE_RESULT_free (TYPE_2__*) ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_TEST_FIRST_HANDSHAKE_FAILED ; 
 scalar_t__ SSL_TEST_HANDSHAKE_RESUME ; 
 scalar_t__ SSL_TEST_INTERNAL_ERROR ; 
 scalar_t__ SSL_TEST_SUCCESS ; 
 TYPE_2__* do_handshake_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

HANDSHAKE_RESULT *do_handshake(SSL_CTX *server_ctx, SSL_CTX *server2_ctx,
                               SSL_CTX *client_ctx, SSL_CTX *resume_server_ctx,
                               SSL_CTX *resume_client_ctx,
                               const SSL_TEST_CTX *test_ctx)
{
    HANDSHAKE_RESULT *result;
    SSL_SESSION *session = NULL, *serv_sess = NULL;

    result = do_handshake_internal(server_ctx, server2_ctx, client_ctx,
                                   test_ctx, &test_ctx->extra,
                                   NULL, NULL, &session, &serv_sess);
    if (result == NULL
            || test_ctx->handshake_mode != SSL_TEST_HANDSHAKE_RESUME
            || result->result == SSL_TEST_INTERNAL_ERROR)
        goto end;

    if (result->result != SSL_TEST_SUCCESS) {
        result->result = SSL_TEST_FIRST_HANDSHAKE_FAILED;
        goto end;
    }

    HANDSHAKE_RESULT_free(result);
    /* We don't support SNI on second handshake yet, so server2_ctx is NULL. */
    result = do_handshake_internal(resume_server_ctx, NULL, resume_client_ctx,
                                   test_ctx, &test_ctx->resume_extra,
                                   session, serv_sess, NULL, NULL);
 end:
    SSL_SESSION_free(session);
    SSL_SESSION_free(serv_sess);
    return result;
}