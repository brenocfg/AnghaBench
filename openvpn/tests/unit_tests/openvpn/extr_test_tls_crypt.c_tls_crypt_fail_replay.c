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
struct buffer {int dummy; } ;
struct test_tls_crypt_context {int /*<<< orphan*/  co; int /*<<< orphan*/  unwrapped; struct buffer ciphertext; struct buffer source; } ;

/* Variables and functions */
 scalar_t__ BLEN (struct buffer*) ; 
 int /*<<< orphan*/  assert_false (int) ; 
 int /*<<< orphan*/  assert_true (int) ; 
 int /*<<< orphan*/  buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_if_tls_crypt_not_supported (struct test_tls_crypt_context*) ; 
 int tls_crypt_unwrap (struct buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int tls_crypt_wrap (struct buffer*,struct buffer*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tls_crypt_fail_replay(void **state) {
    struct test_tls_crypt_context *ctx = (struct test_tls_crypt_context *) *state;

    skip_if_tls_crypt_not_supported(ctx);

    assert_true(tls_crypt_wrap(&ctx->source, &ctx->ciphertext, &ctx->co));
    assert_true(BLEN(&ctx->source) < BLEN(&ctx->ciphertext));
    struct buffer tmp = ctx->ciphertext;
    assert_true(tls_crypt_unwrap(&tmp, &ctx->unwrapped, &ctx->co));
    buf_clear(&ctx->unwrapped);
    assert_false(tls_crypt_unwrap(&ctx->ciphertext, &ctx->unwrapped, &ctx->co));
}