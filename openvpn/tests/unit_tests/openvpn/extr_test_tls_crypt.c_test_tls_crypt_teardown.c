#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  key_ctx_bi; } ;
struct test_tls_crypt_context {TYPE_1__ co; int /*<<< orphan*/  unwrapped; int /*<<< orphan*/  ciphertext; int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct test_tls_crypt_context*) ; 
 int /*<<< orphan*/  free_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_key_ctx_bi (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
test_tls_crypt_teardown(void **state) {
    struct test_tls_crypt_context *ctx =
            (struct test_tls_crypt_context *)*state;

    free_buf(&ctx->source);
    free_buf(&ctx->ciphertext);
    free_buf(&ctx->unwrapped);

    free_key_ctx_bi(&ctx->co.key_ctx_bi);

    free(ctx);

    return 0;
}