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
struct pqi_ctrl_info {int num_msix_vectors_initialized; int /*<<< orphan*/ * queue_groups; int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pqi_free_irqs(struct pqi_ctrl_info *ctrl_info)
{
	int i;

	for (i = 0; i < ctrl_info->num_msix_vectors_initialized; i++)
		free_irq(pci_irq_vector(ctrl_info->pci_dev, i),
			&ctrl_info->queue_groups[i]);

	ctrl_info->num_msix_vectors_initialized = 0;
}