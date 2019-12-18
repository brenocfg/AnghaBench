#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* opt; } ;
struct TYPE_9__ {scalar_t__ auth_token_lifetime; } ;
struct TYPE_11__ {TYPE_2__ opt; int /*<<< orphan*/  auth_token; int /*<<< orphan*/ * auth_token_initial; } ;
struct TYPE_10__ {int /*<<< orphan*/  password; } ;
struct test_context {TYPE_5__ session; TYPE_4__ multi; TYPE_3__ up; } ;
struct TYPE_8__ {int renegotiate_seconds; int auth_token_lifetime; } ;

/* Variables and functions */
 int AUTH_TOKEN_EXPIRED ; 
 int AUTH_TOKEN_HMAC_OK ; 
 int /*<<< orphan*/  assert_int_equal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generate_auth_token (TYPE_3__*,TYPE_4__*) ; 
 int now ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_auth_token (TYPE_3__*,TYPE_4__*,TYPE_5__*) ; 

__attribute__((used)) static void
auth_token_test_timeout(void **state)
{
    struct test_context *ctx = (struct test_context *) *state;

    now = 100000;
    generate_auth_token(&ctx->up, &ctx->multi);
    strcpy(ctx->up.password, ctx->multi.auth_token);

    /* No time has passed */
    assert_int_equal(verify_auth_token(&ctx->up, &ctx->multi, &ctx->session),
                     AUTH_TOKEN_HMAC_OK);

    /* Token before validity, should be rejected */
    now = 100000 - 100;
    assert_int_equal(verify_auth_token(&ctx->up, &ctx->multi, &ctx->session),
                     AUTH_TOKEN_HMAC_OK|AUTH_TOKEN_EXPIRED);

    /* Token still in validity, should be accepted */
    now = 100000 + 2*ctx->session.opt->renegotiate_seconds - 20;
    assert_int_equal(verify_auth_token(&ctx->up, &ctx->multi, &ctx->session),
                     AUTH_TOKEN_HMAC_OK);

    /* Token past validity, should be rejected */
    now = 100000 + 2*ctx->session.opt->renegotiate_seconds + 20;
    assert_int_equal(verify_auth_token(&ctx->up, &ctx->multi, &ctx->session),
                     AUTH_TOKEN_HMAC_OK|AUTH_TOKEN_EXPIRED);

    /* Check if the mode for a client that never updates its token works */
    ctx->multi.auth_token_initial = strdup(ctx->up.password);
    assert_int_equal(verify_auth_token(&ctx->up, &ctx->multi, &ctx->session),
                     AUTH_TOKEN_HMAC_OK);

    /* But not when we reached our timeout */
    now = 100000 + ctx->session.opt->auth_token_lifetime + 1;
    assert_int_equal(verify_auth_token(&ctx->up, &ctx->multi, &ctx->session),
                     AUTH_TOKEN_HMAC_OK|AUTH_TOKEN_EXPIRED);

    free(ctx->multi.auth_token_initial);
    ctx->multi.auth_token_initial = NULL;

    /* regenerate the token util it hits the expiry */
    now = 100000;
    while (now < 100000 + ctx->session.opt->auth_token_lifetime + 1)
    {
        assert_int_equal(verify_auth_token(&ctx->up, &ctx->multi, &ctx->session),
                         AUTH_TOKEN_HMAC_OK);
        generate_auth_token(&ctx->up, &ctx->multi);
        strcpy(ctx->up.password, ctx->multi.auth_token);
        now += ctx->session.opt->renegotiate_seconds;
    }


    assert_int_equal(verify_auth_token(&ctx->up, &ctx->multi, &ctx->session),
                     AUTH_TOKEN_HMAC_OK|AUTH_TOKEN_EXPIRED);
    ctx->multi.opt.auth_token_lifetime = 0;

    /* Non expiring token should be fine */
    assert_int_equal(verify_auth_token(&ctx->up, &ctx->multi, &ctx->session),
                     AUTH_TOKEN_HMAC_OK);
}