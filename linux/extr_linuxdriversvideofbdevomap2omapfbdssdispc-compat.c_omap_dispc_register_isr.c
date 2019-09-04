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
typedef  scalar_t__ u32 ;
struct omap_dispc_isr_data {void* arg; scalar_t__ mask; int /*<<< orphan*/ * isr; } ;
typedef  int /*<<< orphan*/ * omap_dispc_isr_t ;
struct TYPE_2__ {int /*<<< orphan*/  irq_lock; struct omap_dispc_isr_data* registered_isr; } ;

/* Variables and functions */
 int DISPC_MAX_NR_ISRS ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  _omap_dispc_set_irqs () ; 
 TYPE_1__ dispc_compat ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int omap_dispc_register_isr(omap_dispc_isr_t isr, void *arg, u32 mask)
{
	int i;
	int ret;
	unsigned long flags;
	struct omap_dispc_isr_data *isr_data;

	if (isr == NULL)
		return -EINVAL;

	spin_lock_irqsave(&dispc_compat.irq_lock, flags);

	/* check for duplicate entry */
	for (i = 0; i < DISPC_MAX_NR_ISRS; i++) {
		isr_data = &dispc_compat.registered_isr[i];
		if (isr_data->isr == isr && isr_data->arg == arg &&
				isr_data->mask == mask) {
			ret = -EINVAL;
			goto err;
		}
	}

	isr_data = NULL;
	ret = -EBUSY;

	for (i = 0; i < DISPC_MAX_NR_ISRS; i++) {
		isr_data = &dispc_compat.registered_isr[i];

		if (isr_data->isr != NULL)
			continue;

		isr_data->isr = isr;
		isr_data->arg = arg;
		isr_data->mask = mask;
		ret = 0;

		break;
	}

	if (ret)
		goto err;

	_omap_dispc_set_irqs();

	spin_unlock_irqrestore(&dispc_compat.irq_lock, flags);

	return 0;
err:
	spin_unlock_irqrestore(&dispc_compat.irq_lock, flags);

	return ret;
}