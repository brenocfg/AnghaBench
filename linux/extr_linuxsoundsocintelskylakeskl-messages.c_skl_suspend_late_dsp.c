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
struct TYPE_4__ {scalar_t__ func; } ;
struct delayed_work {TYPE_2__ work; } ;
struct TYPE_3__ {struct delayed_work work; } ;
struct skl_sst {TYPE_1__ d0i3; } ;
struct skl {scalar_t__ supend_active; struct skl_sst* skl_sst; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (struct delayed_work*) ; 
 int /*<<< orphan*/  flush_delayed_work (struct delayed_work*) ; 

int skl_suspend_late_dsp(struct skl *skl)
{
	struct skl_sst *ctx = skl->skl_sst;
	struct delayed_work *dwork;

	if (!ctx)
		return 0;

	dwork = &ctx->d0i3.work;

	if (dwork->work.func) {
		if (skl->supend_active)
			flush_delayed_work(dwork);
		else
			cancel_delayed_work_sync(dwork);
	}

	return 0;
}