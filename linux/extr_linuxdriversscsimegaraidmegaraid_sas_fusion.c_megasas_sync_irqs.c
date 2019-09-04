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
typedef  int u32 ;
struct megasas_instance {scalar_t__ msix_vectors; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

void megasas_sync_irqs(unsigned long instance_addr)
{
	u32 count, i;
	struct megasas_instance *instance =
		(struct megasas_instance *)instance_addr;

	count = instance->msix_vectors > 0 ? instance->msix_vectors : 1;

	for (i = 0; i < count; i++)
		synchronize_irq(pci_irq_vector(instance->pdev, i));
}