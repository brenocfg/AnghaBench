#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct fsi_master {int /*<<< orphan*/  lock; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fsi_reg_mask_set (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void _fsi_master_mask_set(struct fsi_master *master,
			       u32 reg, u32 mask, u32 data)
{
	unsigned long flags;

	spin_lock_irqsave(&master->lock, flags);
	__fsi_reg_mask_set(master->base + reg, mask, data);
	spin_unlock_irqrestore(&master->lock, flags);
}