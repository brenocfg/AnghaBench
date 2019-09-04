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
struct vmd_irq_list {int dummy; } ;
struct vmd_irq {struct vmd_irq_list* irq; } ;
struct vmd_dev {int dummy; } ;
struct msi_msg {int address_lo; scalar_t__ data; int /*<<< orphan*/  address_hi; } ;
struct irq_data {struct vmd_irq* chip_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSI_ADDR_BASE_HI ; 
 int MSI_ADDR_BASE_LO ; 
 int MSI_ADDR_DEST_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_from_irqs (struct vmd_dev*,struct vmd_irq_list*) ; 
 struct vmd_dev* irq_data_get_irq_handler_data (struct irq_data*) ; 

__attribute__((used)) static void vmd_compose_msi_msg(struct irq_data *data, struct msi_msg *msg)
{
	struct vmd_irq *vmdirq = data->chip_data;
	struct vmd_irq_list *irq = vmdirq->irq;
	struct vmd_dev *vmd = irq_data_get_irq_handler_data(data);

	msg->address_hi = MSI_ADDR_BASE_HI;
	msg->address_lo = MSI_ADDR_BASE_LO |
			  MSI_ADDR_DEST_ID(index_from_irqs(vmd, irq));
	msg->data = 0;
}