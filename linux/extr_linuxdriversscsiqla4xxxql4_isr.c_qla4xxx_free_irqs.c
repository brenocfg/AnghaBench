#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_qla_host {TYPE_1__* pdev; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {scalar_t__ msix_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_IRQ_ATTACHED ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct scsi_qla_host*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_irq_vector (TYPE_1__*,int) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qla4xxx_free_irqs(struct scsi_qla_host *ha)
{
	if (!test_and_clear_bit(AF_IRQ_ATTACHED, &ha->flags))
		return;

	if (ha->pdev->msix_enabled)
		free_irq(pci_irq_vector(ha->pdev, 1), ha);
	free_irq(pci_irq_vector(ha->pdev, 0), ha);
	pci_free_irq_vectors(ha->pdev);
}