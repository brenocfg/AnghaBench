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
struct test_tls_crypt_v2_context {int /*<<< orphan*/  gc; int /*<<< orphan*/  client_key; int /*<<< orphan*/  server_keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct test_tls_crypt_v2_context*) ; 
 int /*<<< orphan*/  free_key_ctx_bi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gc_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
test_tls_crypt_v2_teardown(void **state) {
    struct test_tls_crypt_v2_context *ctx =
            (struct test_tls_crypt_v2_context *) *state;

    free_key_ctx_bi(&ctx->server_keys);
    free_key_ctx_bi(&ctx->client_key);

    gc_free(&ctx->gc);

    free(ctx);

    return 0;
}