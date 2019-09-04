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
struct pci_epc {int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* start ) (struct pci_epc*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct pci_epc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct pci_epc*) ; 

int pci_epc_start(struct pci_epc *epc)
{
	int ret;
	unsigned long flags;

	if (IS_ERR(epc))
		return -EINVAL;

	if (!epc->ops->start)
		return 0;

	spin_lock_irqsave(&epc->lock, flags);
	ret = epc->ops->start(epc);
	spin_unlock_irqrestore(&epc->lock, flags);

	return ret;
}