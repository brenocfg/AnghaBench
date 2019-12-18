#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  test_app ;
struct TYPE_19__ {scalar_t__ servername_callback; } ;
struct TYPE_20__ {TYPE_1__ server; } ;
struct TYPE_21__ {scalar_t__ method; scalar_t__ handshake_mode; TYPE_2__ extra; } ;
typedef  TYPE_3__ SSL_TEST_CTX ;
typedef  TYPE_3__ SSL_CTX ;
typedef  int /*<<< orphan*/  HANDSHAKE_RESULT ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  CONF_modules_load (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONF_modules_unload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTLS_client_method () ; 
 int /*<<< orphan*/  DTLS_server_method () ; 
 int /*<<< orphan*/  HANDSHAKE_RESULT_free (int /*<<< orphan*/ *) ; 
 int MAX_TESTCASE_NAME_LENGTH ; 
 int /*<<< orphan*/  OPENSSL_INIT_LOAD_CONFIG ; 
 int /*<<< orphan*/  OPENSSL_init_ssl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_config (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  SSL_CTX_free (TYPE_3__*) ; 
 TYPE_3__* SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_max_proto_version (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* SSL_TEST_CTX_create (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SSL_TEST_CTX_free (TYPE_3__*) ; 
 scalar_t__ SSL_TEST_HANDSHAKE_RESUME ; 
 scalar_t__ SSL_TEST_METHOD_DTLS ; 
 scalar_t__ SSL_TEST_METHOD_TLS ; 
 scalar_t__ SSL_TEST_SERVERNAME_CB_NONE ; 
 int /*<<< orphan*/  TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_3__*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int check_test (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  conf ; 
 int /*<<< orphan*/ * do_handshake (TYPE_3__*,TYPE_3__*,TYPE_3__*,TYPE_3__*,TYPE_3__*,TYPE_3__*) ; 

__attribute__((used)) static int test_handshake(int idx)
{
    int ret = 0;
    SSL_CTX *server_ctx = NULL, *server2_ctx = NULL, *client_ctx = NULL,
        *resume_server_ctx = NULL, *resume_client_ctx = NULL;
    SSL_TEST_CTX *test_ctx = NULL;
    HANDSHAKE_RESULT *result = NULL;
    char test_app[MAX_TESTCASE_NAME_LENGTH];

    BIO_snprintf(test_app, sizeof(test_app), "test-%d", idx);

    test_ctx = SSL_TEST_CTX_create(conf, test_app);
    if (!TEST_ptr(test_ctx))
        goto err;

#ifndef OPENSSL_NO_DTLS
    if (test_ctx->method == SSL_TEST_METHOD_DTLS) {
        server_ctx = SSL_CTX_new(DTLS_server_method());
        if (!TEST_true(SSL_CTX_set_max_proto_version(server_ctx, 0)))
            goto err;
        if (test_ctx->extra.server.servername_callback !=
            SSL_TEST_SERVERNAME_CB_NONE) {
            if (!TEST_ptr(server2_ctx = SSL_CTX_new(DTLS_server_method())))
                goto err;
        }
        client_ctx = SSL_CTX_new(DTLS_client_method());
        if (!TEST_true(SSL_CTX_set_max_proto_version(client_ctx, 0)))
            goto err;
        if (test_ctx->handshake_mode == SSL_TEST_HANDSHAKE_RESUME) {
            resume_server_ctx = SSL_CTX_new(DTLS_server_method());
            if (!TEST_true(SSL_CTX_set_max_proto_version(resume_server_ctx, 0)))
                goto err;
            resume_client_ctx = SSL_CTX_new(DTLS_client_method());
            if (!TEST_true(SSL_CTX_set_max_proto_version(resume_client_ctx, 0)))
                goto err;
            if (!TEST_ptr(resume_server_ctx)
                    || !TEST_ptr(resume_client_ctx))
                goto err;
        }
    }
#endif
    if (test_ctx->method == SSL_TEST_METHOD_TLS) {
        server_ctx = SSL_CTX_new(TLS_server_method());
        if (!TEST_true(SSL_CTX_set_max_proto_version(server_ctx, 0)))
            goto err;
        /* SNI on resumption isn't supported/tested yet. */
        if (test_ctx->extra.server.servername_callback !=
            SSL_TEST_SERVERNAME_CB_NONE) {
            if (!TEST_ptr(server2_ctx = SSL_CTX_new(TLS_server_method())))
                goto err;
            if (!TEST_true(SSL_CTX_set_max_proto_version(server2_ctx, 0)))
                goto err;
        }
        client_ctx = SSL_CTX_new(TLS_client_method());
        if (!TEST_true(SSL_CTX_set_max_proto_version(client_ctx, 0)))
            goto err;

        if (test_ctx->handshake_mode == SSL_TEST_HANDSHAKE_RESUME) {
            resume_server_ctx = SSL_CTX_new(TLS_server_method());
            if (!TEST_true(SSL_CTX_set_max_proto_version(resume_server_ctx, 0)))
                goto err;
            resume_client_ctx = SSL_CTX_new(TLS_client_method());
            if (!TEST_true(SSL_CTX_set_max_proto_version(resume_client_ctx, 0)))
                goto err;
            if (!TEST_ptr(resume_server_ctx)
                    || !TEST_ptr(resume_client_ctx))
                goto err;
        }
    }

#ifdef OPENSSL_NO_AUTOLOAD_CONFIG
    if (!TEST_true(OPENSSL_init_ssl(OPENSSL_INIT_LOAD_CONFIG, NULL)))
        goto err;
#endif

    if (!TEST_ptr(server_ctx)
            || !TEST_ptr(client_ctx)
            || !TEST_int_gt(CONF_modules_load(conf, test_app, 0),  0))
        goto err;

    if (!SSL_CTX_config(server_ctx, "server")
        || !SSL_CTX_config(client_ctx, "client")) {
        goto err;
    }

    if (server2_ctx != NULL && !SSL_CTX_config(server2_ctx, "server2"))
        goto err;
    if (resume_server_ctx != NULL
        && !SSL_CTX_config(resume_server_ctx, "resume-server"))
        goto err;
    if (resume_client_ctx != NULL
        && !SSL_CTX_config(resume_client_ctx, "resume-client"))
        goto err;

    result = do_handshake(server_ctx, server2_ctx, client_ctx,
                          resume_server_ctx, resume_client_ctx, test_ctx);

    if (result != NULL)
        ret = check_test(result, test_ctx);

err:
    CONF_modules_unload(0);
    SSL_CTX_free(server_ctx);
    SSL_CTX_free(server2_ctx);
    SSL_CTX_free(client_ctx);
    SSL_CTX_free(resume_server_ctx);
    SSL_CTX_free(resume_client_ctx);
    SSL_TEST_CTX_free(test_ctx);
    HANDSHAKE_RESULT_free(result);
    return ret;
}