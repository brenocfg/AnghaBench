#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  smp_resp; int /*<<< orphan*/  smp_req; } ;
struct sas_task {TYPE_2__ smp_task; } ;
struct asd_ascb {TYPE_1__* ha; struct sas_task* uldd_task; } ;
struct TYPE_3__ {int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  pci_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asd_unbuild_smp_ascb(struct asd_ascb *a)
{
	struct sas_task *task = a->uldd_task;

	BUG_ON(!task);
	pci_unmap_sg(a->ha->pcidev, &task->smp_task.smp_req, 1,
		     PCI_DMA_TODEVICE);
	pci_unmap_sg(a->ha->pcidev, &task->smp_task.smp_resp, 1,
		     PCI_DMA_FROMDEVICE);
}