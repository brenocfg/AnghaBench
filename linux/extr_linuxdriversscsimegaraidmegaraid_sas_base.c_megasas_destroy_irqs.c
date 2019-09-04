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
struct megasas_instance {int msix_vectors; int /*<<< orphan*/ * irq_context; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
megasas_destroy_irqs(struct megasas_instance *instance) {

	int i;

	if (instance->msix_vectors)
		for (i = 0; i < instance->msix_vectors; i++) {
			free_irq(pci_irq_vector(instance->pdev, i),
				 &instance->irq_context[i]);
		}
	else
		free_irq(pci_irq_vector(instance->pdev, 0),
			 &instance->irq_context[0]);
}