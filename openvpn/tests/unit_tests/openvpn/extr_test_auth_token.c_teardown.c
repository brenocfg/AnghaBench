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
struct TYPE_5__ {struct test_context* opt; } ;
struct TYPE_4__ {int /*<<< orphan*/  auth_token_key; } ;
struct TYPE_6__ {TYPE_1__ opt; } ;
struct test_context {TYPE_2__ session; TYPE_3__ multi; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct test_context*) ; 
 int /*<<< orphan*/  free_key_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wipe_auth_token (TYPE_3__*) ; 

__attribute__((used)) static int
teardown(void **state)
{
    struct test_context *ctx = (struct test_context *) *state;

    free_key_ctx(&ctx->multi.opt.auth_token_key);
    wipe_auth_token(&ctx->multi);

    free(ctx->session.opt);
    free(ctx);

    return 0;
}