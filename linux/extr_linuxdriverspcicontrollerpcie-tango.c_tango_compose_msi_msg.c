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
struct tango_pcie {int /*<<< orphan*/  msi_doorbell; } ;
struct msi_msg {int /*<<< orphan*/  data; int /*<<< orphan*/  address_hi; int /*<<< orphan*/  address_lo; } ;
struct irq_data {int /*<<< orphan*/  hwirq; struct tango_pcie* chip_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tango_compose_msi_msg(struct irq_data *d, struct msi_msg *msg)
{
	struct tango_pcie *pcie = d->chip_data;
	msg->address_lo = lower_32_bits(pcie->msi_doorbell);
	msg->address_hi = upper_32_bits(pcie->msi_doorbell);
	msg->data = d->hwirq;
}