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
struct test_tls_crypt_context {int /*<<< orphan*/  source; int /*<<< orphan*/  unwrapped; int /*<<< orphan*/  co; int /*<<< orphan*/  ciphertext; } ;

/* Variables and functions */
 scalar_t__ BLEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BPTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert_int_equal (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  assert_memory_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  assert_true (int) ; 
 int /*<<< orphan*/  skip_if_tls_crypt_not_supported (struct test_tls_crypt_context*) ; 
 int tls_crypt_unwrap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int tls_crypt_wrap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tls_crypt_loopback(void **state) {
    struct test_tls_crypt_context *ctx = (struct test_tls_crypt_context *) *state;

    skip_if_tls_crypt_not_supported(ctx);

    assert_true(tls_crypt_wrap(&ctx->source, &ctx->ciphertext, &ctx->co));
    assert_true(BLEN(&ctx->source) < BLEN(&ctx->ciphertext));
    assert_true(tls_crypt_unwrap(&ctx->ciphertext, &ctx->unwrapped, &ctx->co));
    assert_int_equal(BLEN(&ctx->source), BLEN(&ctx->unwrapped));
    assert_memory_equal(BPTR(&ctx->source), BPTR(&ctx->unwrapped),
                        BLEN(&ctx->source));
}