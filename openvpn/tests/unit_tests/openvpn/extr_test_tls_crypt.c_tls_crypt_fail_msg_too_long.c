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
struct test_tls_crypt_context {int /*<<< orphan*/  co; int /*<<< orphan*/  ciphertext; int /*<<< orphan*/  source; } ;

/* Variables and functions */
 scalar_t__ BLEN (int /*<<< orphan*/ *) ; 
 scalar_t__ TESTBUF_SIZE ; 
 int /*<<< orphan*/  assert_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_non_null (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_write_alloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  skip_if_tls_crypt_not_supported (struct test_tls_crypt_context*) ; 
 scalar_t__ tls_crypt_buf_overhead () ; 
 int /*<<< orphan*/  tls_crypt_wrap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tls_crypt_fail_msg_too_long(void **state) {
    struct test_tls_crypt_context *ctx = (struct test_tls_crypt_context *) *state;

    skip_if_tls_crypt_not_supported(ctx);

    buf_clear(&ctx->source);
    assert_non_null(buf_write_alloc(&ctx->source,
                                    TESTBUF_SIZE - BLEN(&ctx->ciphertext) - tls_crypt_buf_overhead() + 1));
    assert_false(tls_crypt_wrap(&ctx->source, &ctx->ciphertext, &ctx->co));
}