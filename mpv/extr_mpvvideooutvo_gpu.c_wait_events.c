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
struct vo {struct gpu_priv* priv; } ;
struct gpu_priv {TYPE_2__* ctx; } ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_4__ {TYPE_1__* fns; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* wait_events ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vo_wait_default (struct vo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wait_events(struct vo *vo, int64_t until_time_us)
{
    struct gpu_priv *p = vo->priv;
    if (p->ctx && p->ctx->fns->wait_events) {
        p->ctx->fns->wait_events(p->ctx, until_time_us);
    } else {
        vo_wait_default(vo, until_time_us);
    }
}