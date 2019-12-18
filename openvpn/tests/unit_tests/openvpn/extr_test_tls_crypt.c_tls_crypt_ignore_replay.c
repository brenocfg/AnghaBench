#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct buffer {int dummy; } ;
struct test_tls_crypt_context {TYPE_1__ co; int /*<<< orphan*/  unwrapped; struct buffer ciphertext; struct buffer source; } ;

/* Variables and functions */
 scalar_t__ BLEN (struct buffer*) ; 
 int /*<<< orphan*/  CO_IGNORE_PACKET_ID ; 
 int /*<<< orphan*/  assert_true (int) ; 
 int /*<<< orphan*/  buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_if_tls_crypt_not_supported (struct test_tls_crypt_context*) ; 
 int tls_crypt_unwrap (struct buffer*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int tls_crypt_wrap (struct buffer*,struct buffer*,TYPE_1__*) ; 

__attribute__((used)) static void
tls_crypt_ignore_replay(void **state) {
    struct test_tls_crypt_context *ctx = (struct test_tls_crypt_context *) *state;

    skip_if_tls_crypt_not_supported(ctx);

    ctx->co.flags |= CO_IGNORE_PACKET_ID;

    assert_true(tls_crypt_wrap(&ctx->source, &ctx->ciphertext, &ctx->co));
    assert_true(BLEN(&ctx->source) < BLEN(&ctx->ciphertext));
    struct buffer tmp = ctx->ciphertext;
    assert_true(tls_crypt_unwrap(&tmp, &ctx->unwrapped, &ctx->co));
    buf_clear(&ctx->unwrapped);
    assert_true(tls_crypt_unwrap(&ctx->ciphertext, &ctx->unwrapped, &ctx->co));
}