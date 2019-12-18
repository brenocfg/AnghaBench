#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  decrypt; } ;
struct TYPE_7__ {TYPE_2__ key_ctx_bi; } ;
struct test_tls_crypt_context {TYPE_3__ co; int /*<<< orphan*/  unwrapped; int /*<<< orphan*/  ciphertext; int /*<<< orphan*/  source; int /*<<< orphan*/  kt; } ;
struct TYPE_5__ {int member_0; } ;
struct key {TYPE_1__ member_0; } ;

/* Variables and functions */
 scalar_t__ BLEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_true (int) ; 
 int /*<<< orphan*/  free_key_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_key_ctx (int /*<<< orphan*/ *,struct key*,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  skip_if_tls_crypt_not_supported (struct test_tls_crypt_context*) ; 
 int /*<<< orphan*/  tls_crypt_unwrap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int tls_crypt_wrap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void
tls_crypt_fail_invalid_key(void **state) {
    struct test_tls_crypt_context *ctx = (struct test_tls_crypt_context *) *state;

    skip_if_tls_crypt_not_supported(ctx);

    /* Change decrypt key */
    struct key key = { { 1 } };
    free_key_ctx(&ctx->co.key_ctx_bi.decrypt);
    init_key_ctx(&ctx->co.key_ctx_bi.decrypt, &key, &ctx->kt, false, "TEST");

    assert_true(tls_crypt_wrap(&ctx->source, &ctx->ciphertext, &ctx->co));
    assert_true(BLEN(&ctx->source) < BLEN(&ctx->ciphertext));
    assert_false(tls_crypt_unwrap(&ctx->ciphertext, &ctx->unwrapped, &ctx->co));
}