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
struct srcimp_mgr {int /*<<< orphan*/  mgr_lock; int /*<<< orphan*/  mgr; } ;
struct TYPE_2__ {int msr; } ;
struct srcimp {int /*<<< orphan*/ * idx; TYPE_1__ rsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct srcimp*) ; 
 int /*<<< orphan*/  mgr_put_resource (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  srcimp_rsc_uninit (struct srcimp*) ; 

__attribute__((used)) static int put_srcimp_rsc(struct srcimp_mgr *mgr, struct srcimp *srcimp)
{
	unsigned long flags;
	int i;

	spin_lock_irqsave(&mgr->mgr_lock, flags);
	for (i = 0; i < srcimp->rsc.msr; i++)
		mgr_put_resource(&mgr->mgr, 1, srcimp->idx[i]);

	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	srcimp_rsc_uninit(srcimp);
	kfree(srcimp);

	return 0;
}