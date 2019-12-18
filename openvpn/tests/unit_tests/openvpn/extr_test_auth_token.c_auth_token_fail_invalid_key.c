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
struct TYPE_8__ {TYPE_1__ opt; int /*<<< orphan*/  auth_token; } ;
struct TYPE_7__ {int /*<<< orphan*/  password; } ;
struct test_context {int /*<<< orphan*/  session; TYPE_3__ multi; TYPE_2__ up; int /*<<< orphan*/  kt; } ;
struct key {int dummy; } ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_TOKEN_HMAC_OK ; 
 int /*<<< orphan*/  assert_int_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_key_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generate_auth_token (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  init_key_ctx (int /*<<< orphan*/ *,struct key*,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  memset (struct key*,char,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_auth_token (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
auth_token_fail_invalid_key(void **state)
{
    struct test_context *ctx = (struct test_context *) *state;

    generate_auth_token(&ctx->up, &ctx->multi);
    strcpy(ctx->up.password, ctx->multi.auth_token);
    assert_int_equal(verify_auth_token(&ctx->up, &ctx->multi, &ctx->session),
                     AUTH_TOKEN_HMAC_OK);

    /* Change auth-token key */
    struct key key;
    memset(&key, '1', sizeof(key));
    free_key_ctx(&ctx->multi.opt.auth_token_key);
    init_key_ctx(&ctx->multi.opt.auth_token_key, &key, &ctx->kt, false, "TEST");

    assert_int_equal(verify_auth_token(&ctx->up, &ctx->multi, &ctx->session), 0);

    /* Load original test key again */
    memset(&key, 0, sizeof(key));
    free_key_ctx(&ctx->multi.opt.auth_token_key);
    init_key_ctx(&ctx->multi.opt.auth_token_key, &key, &ctx->kt, false, "TEST");
    assert_int_equal(verify_auth_token(&ctx->up, &ctx->multi, &ctx->session),
                     AUTH_TOKEN_HMAC_OK);

}