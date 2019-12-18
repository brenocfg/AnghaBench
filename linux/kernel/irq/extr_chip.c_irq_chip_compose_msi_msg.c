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
struct msi_msg {int dummy; } ;
struct irq_data {TYPE_1__* chip; struct irq_data* parent_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* irq_compose_msi_msg ) (struct irq_data*,struct msi_msg*) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  stub1 (struct irq_data*,struct msi_msg*) ; 

int irq_chip_compose_msi_msg(struct irq_data *data, struct msi_msg *msg)
{
	struct irq_data *pos = NULL;

#ifdef	CONFIG_IRQ_DOMAIN_HIERARCHY
	for (; data; data = data->parent_data)
#endif
		if (data->chip && data->chip->irq_compose_msi_msg)
			pos = data;
	if (!pos)
		return -ENOSYS;

	pos->chip->irq_compose_msi_msg(pos, msg);

	return 0;
}