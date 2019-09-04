#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/  mpctx; } ;
typedef  TYPE_1__ mpv_handle ;

/* Variables and functions */
 int /*<<< orphan*/  lock_core (TYPE_1__*) ; 
 int mp_hook_continue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_core (TYPE_1__*) ; 

int mpv_hook_continue(mpv_handle *ctx, uint64_t id)
{
    lock_core(ctx);
    int r = mp_hook_continue(ctx->mpctx, ctx->name, id);
    unlock_core(ctx);
    return r;
}