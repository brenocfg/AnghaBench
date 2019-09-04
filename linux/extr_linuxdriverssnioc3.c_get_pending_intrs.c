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
typedef  int /*<<< orphan*/  uint32_t ;
struct ioc3_driver_data {int /*<<< orphan*/  ir_lock; TYPE_1__* vma; } ;
struct TYPE_2__ {int /*<<< orphan*/  sio_ies; int /*<<< orphan*/  sio_ir; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline uint32_t get_pending_intrs(struct ioc3_driver_data *idd)
{
	unsigned long flag;
	uint32_t intrs = 0;

	spin_lock_irqsave(&idd->ir_lock, flag);
	intrs = readl(&idd->vma->sio_ir);
	intrs &= readl(&idd->vma->sio_ies);
	spin_unlock_irqrestore(&idd->ir_lock, flag);
	return intrs;
}