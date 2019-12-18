#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ra_ctx {TYPE_1__* vo; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  sync; int /*<<< orphan*/  (* XGetSyncValues ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*) ;} ;
typedef  int int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  window; int /*<<< orphan*/  display; } ;
struct TYPE_3__ {TYPE_2__* x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*)) ; 
 int /*<<< orphan*/  oml_sync_swap (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*) ; 

__attribute__((used)) static void update_vsync_oml(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;

    assert(p->XGetSyncValues);

    int64_t ust, msc, sbc;
    if (!p->XGetSyncValues(ctx->vo->x11->display, ctx->vo->x11->window,
                           &ust, &msc, &sbc))
        ust = msc = sbc = -1;

    oml_sync_swap(&p->sync, ust, msc, sbc);
}