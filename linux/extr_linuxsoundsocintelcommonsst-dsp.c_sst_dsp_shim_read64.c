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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  shim; } ;
struct sst_dsp {int /*<<< orphan*/  spinlock; TYPE_2__ addr; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* read64 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 sst_dsp_shim_read64(struct sst_dsp *sst, u32 offset)
{
	unsigned long flags;
	u64 val;

	spin_lock_irqsave(&sst->spinlock, flags);
	val = sst->ops->read64(sst->addr.shim, offset);
	spin_unlock_irqrestore(&sst->spinlock, flags);

	return val;
}