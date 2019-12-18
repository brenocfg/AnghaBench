#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sum_mgr {int /*<<< orphan*/  mgr_lock; int /*<<< orphan*/  mgr; } ;
struct TYPE_2__ {int msr; } ;
struct sum {int /*<<< orphan*/ * idx; TYPE_1__ rsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sum*) ; 
 int /*<<< orphan*/  mgr_put_resource (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sum_rsc_uninit (struct sum*) ; 

__attribute__((used)) static int put_sum_rsc(struct sum_mgr *mgr, struct sum *sum)
{
	unsigned long flags;
	int i;

	spin_lock_irqsave(&mgr->mgr_lock, flags);
	for (i = 0; i < sum->rsc.msr; i++)
		mgr_put_resource(&mgr->mgr, 1, sum->idx[i]);

	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	sum_rsc_uninit(sum);
	kfree(sum);

	return 0;
}