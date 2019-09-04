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
struct pqi_ctrl_info {scalar_t__ iomem_base; int /*<<< orphan*/  error_buffer_dma_handle; scalar_t__ error_buffer; int /*<<< orphan*/  error_buffer_length; TYPE_1__* pci_dev; int /*<<< orphan*/  admin_queue_memory_base_dma_handle; scalar_t__ admin_queue_memory_base; int /*<<< orphan*/  admin_queue_memory_length; int /*<<< orphan*/  queue_memory_base_dma_handle; scalar_t__ queue_memory_base; int /*<<< orphan*/  queue_memory_length; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqi_cleanup_pci_init (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_free_all_io_requests (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_free_ctrl_info (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_free_interrupts (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_stop_heartbeat_timer (struct pqi_ctrl_info*) ; 

__attribute__((used)) static void pqi_free_ctrl_resources(struct pqi_ctrl_info *ctrl_info)
{
	pqi_stop_heartbeat_timer(ctrl_info);
	pqi_free_interrupts(ctrl_info);
	if (ctrl_info->queue_memory_base)
		dma_free_coherent(&ctrl_info->pci_dev->dev,
			ctrl_info->queue_memory_length,
			ctrl_info->queue_memory_base,
			ctrl_info->queue_memory_base_dma_handle);
	if (ctrl_info->admin_queue_memory_base)
		dma_free_coherent(&ctrl_info->pci_dev->dev,
			ctrl_info->admin_queue_memory_length,
			ctrl_info->admin_queue_memory_base,
			ctrl_info->admin_queue_memory_base_dma_handle);
	pqi_free_all_io_requests(ctrl_info);
	if (ctrl_info->error_buffer)
		dma_free_coherent(&ctrl_info->pci_dev->dev,
			ctrl_info->error_buffer_length,
			ctrl_info->error_buffer,
			ctrl_info->error_buffer_dma_handle);
	if (ctrl_info->iomem_base)
		pqi_cleanup_pci_init(ctrl_info);
	pqi_free_ctrl_info(ctrl_info);
}