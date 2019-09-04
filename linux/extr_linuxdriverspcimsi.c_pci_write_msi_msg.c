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
struct msi_msg {int dummy; } ;
struct msi_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pci_write_msi_msg (struct msi_desc*,struct msi_msg*) ; 
 struct msi_desc* irq_get_msi_desc (unsigned int) ; 

void pci_write_msi_msg(unsigned int irq, struct msi_msg *msg)
{
	struct msi_desc *entry = irq_get_msi_desc(irq);

	__pci_write_msi_msg(entry, msg);
}