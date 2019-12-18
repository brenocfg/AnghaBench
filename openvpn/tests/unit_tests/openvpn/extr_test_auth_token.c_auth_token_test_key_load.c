#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  auth_token_key; } ;
struct TYPE_6__ {TYPE_1__ opt; } ;
struct TYPE_5__ {int /*<<< orphan*/  password; } ;
struct test_context {int /*<<< orphan*/  session; TYPE_3__ multi; TYPE_2__ up; } ;

/* Variables and functions */
 int /*<<< orphan*/  INLINE_FILE_TAG ; 
 int /*<<< orphan*/  allx01inline ; 
 int /*<<< orphan*/  assert_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auth_token_init_secret (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_key_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  now0key0 ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_auth_token (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zeroinline ; 

__attribute__((used)) static void
auth_token_test_key_load(void **state)
{
    struct test_context *ctx = (struct test_context *) *state;

    free_key_ctx(&ctx->multi.opt.auth_token_key);
    auth_token_init_secret(&ctx->multi.opt.auth_token_key, INLINE_FILE_TAG, zeroinline);
    strcpy(ctx->up.password, now0key0);
    assert_true(verify_auth_token(&ctx->up, &ctx->multi, &ctx->session));

    free_key_ctx(&ctx->multi.opt.auth_token_key);
    auth_token_init_secret(&ctx->multi.opt.auth_token_key, INLINE_FILE_TAG, allx01inline);
    assert_false(verify_auth_token(&ctx->up, &ctx->multi, &ctx->session));
}