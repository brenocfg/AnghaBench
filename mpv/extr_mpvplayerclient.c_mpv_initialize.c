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
struct TYPE_5__ {int /*<<< orphan*/  mpctx; } ;
typedef  TYPE_1__ mpv_handle ;

/* Variables and functions */
 int MPV_ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  lock_core (TYPE_1__*) ; 
 scalar_t__ mp_initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_wakeup_core (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_core (TYPE_1__*) ; 

int mpv_initialize(mpv_handle *ctx)
{
    lock_core(ctx);
    int res = mp_initialize(ctx->mpctx, NULL) ? MPV_ERROR_INVALID_PARAMETER : 0;
    mp_wakeup_core(ctx->mpctx);
    unlock_core(ctx);
    return res;
}