#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  auth_token_key; } ;
struct TYPE_8__ {int /*<<< orphan*/  auth_token; TYPE_1__ opt; } ;
struct TYPE_7__ {int /*<<< orphan*/  password; } ;
struct test_context {int /*<<< orphan*/  session; TYPE_3__ multi; TYPE_2__ up; } ;

/* Variables and functions */
 int /*<<< orphan*/  INLINE_FILE_TAG ; 
 int /*<<< orphan*/  assert_string_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auth_token_init_secret (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_key_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generate_auth_token (TYPE_2__*,TYPE_3__*) ; 
 int now ; 
 int /*<<< orphan*/  random_key ; 
 int /*<<< orphan*/  random_token ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_auth_token (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zerohmac (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
auth_token_test_random_keys(void **state)
{
    struct test_context *ctx = (struct test_context *) *state;

    now = 0x5c331e9c;
    /* Preload the session id so the same session id is used here */
    ctx->multi.auth_token = strdup(random_token);

    free_key_ctx(&ctx->multi.opt.auth_token_key);
    auth_token_init_secret(&ctx->multi.opt.auth_token_key, INLINE_FILE_TAG, random_key);

    /* Zero the hmac part to ensure we have a newly generated token */
    zerohmac(ctx->multi.auth_token);

    generate_auth_token(&ctx->up, &ctx->multi);

    assert_string_equal(random_token, ctx->multi.auth_token);

    strcpy(ctx->up.password, ctx->multi.auth_token);
    assert_true(verify_auth_token(&ctx->up, &ctx->multi, &ctx->session));
}