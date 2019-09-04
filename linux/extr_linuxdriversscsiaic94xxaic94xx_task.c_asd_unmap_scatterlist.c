#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sas_task {scalar_t__ data_dir; scalar_t__ num_scatter; scalar_t__ task_proto; int /*<<< orphan*/  scatter; int /*<<< orphan*/  total_xfer_len; } ;
struct asd_ha_struct {int /*<<< orphan*/  pcidev; } ;
struct asd_ascb {int /*<<< orphan*/  sg_arr; struct asd_ha_struct* ha; TYPE_3__* scb; struct sas_task* uldd_task; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {TYPE_1__* sg_element; } ;
struct TYPE_6__ {TYPE_2__ ssp_task; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus_addr; } ;

/* Variables and functions */
 scalar_t__ PCI_DMA_NONE ; 
 scalar_t__ SAS_PROTOCOL_STP ; 
 int /*<<< orphan*/  asd_free_coherent (struct asd_ha_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void asd_unmap_scatterlist(struct asd_ascb *ascb)
{
	struct asd_ha_struct *asd_ha = ascb->ha;
	struct sas_task *task = ascb->uldd_task;

	if (task->data_dir == PCI_DMA_NONE)
		return;

	if (task->num_scatter == 0) {
		dma_addr_t dma = (dma_addr_t)
		       le64_to_cpu(ascb->scb->ssp_task.sg_element[0].bus_addr);
		pci_unmap_single(ascb->ha->pcidev, dma, task->total_xfer_len,
				 task->data_dir);
		return;
	}

	asd_free_coherent(asd_ha, ascb->sg_arr);
	if (task->task_proto != SAS_PROTOCOL_STP)
		pci_unmap_sg(asd_ha->pcidev, task->scatter, task->num_scatter,
			     task->data_dir);
}