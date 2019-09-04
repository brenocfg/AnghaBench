#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* expected_cipher; int /*<<< orphan*/  expected_client_ca_names; int /*<<< orphan*/  expected_server_ca_names; struct TYPE_5__* expected_session_ticket_app_data; struct TYPE_5__* expected_alpn_protocol; struct TYPE_5__* expected_npn_protocol; } ;
typedef  TYPE_1__ SSL_TEST_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  X509_NAME_free ; 
 int /*<<< orphan*/  sk_X509_NAME_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_test_ctx_free_extra_data (TYPE_1__*) ; 

void SSL_TEST_CTX_free(SSL_TEST_CTX *ctx)
{
    ssl_test_ctx_free_extra_data(ctx);
    OPENSSL_free(ctx->expected_npn_protocol);
    OPENSSL_free(ctx->expected_alpn_protocol);
    OPENSSL_free(ctx->expected_session_ticket_app_data);
    sk_X509_NAME_pop_free(ctx->expected_server_ca_names, X509_NAME_free);
    sk_X509_NAME_pop_free(ctx->expected_client_ca_names, X509_NAME_free);
    OPENSSL_free(ctx->expected_cipher);
    OPENSSL_free(ctx);
}