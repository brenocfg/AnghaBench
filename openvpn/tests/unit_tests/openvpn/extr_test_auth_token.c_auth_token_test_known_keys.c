#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  auth_token; } ;
struct TYPE_5__ {int /*<<< orphan*/  password; } ;
struct test_context {int /*<<< orphan*/  session; TYPE_2__ multi; TYPE_1__ up; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_TOKEN_HMAC_OK ; 
 int /*<<< orphan*/  assert_int_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_string_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generate_auth_token (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ now ; 
 int /*<<< orphan*/  now0key0 ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_auth_token (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zerohmac (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
auth_token_test_known_keys(void **state)
{
    struct test_context *ctx = (struct test_context *) *state;

    now = 0;
    /* Preload the session id so the same session id is used here */
    ctx->multi.auth_token = strdup(now0key0);

    /* Zero the hmac part to ensure we have a newly generated token */
    zerohmac(ctx->multi.auth_token);

    generate_auth_token(&ctx->up, &ctx->multi);

    assert_string_equal(now0key0, ctx->multi.auth_token);

    strcpy(ctx->up.password, ctx->multi.auth_token);
    assert_int_equal(verify_auth_token(&ctx->up, &ctx->multi, &ctx->session),
                     AUTH_TOKEN_HMAC_OK);
}