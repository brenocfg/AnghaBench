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
struct pqi_io_request {int /*<<< orphan*/  sg_chain_buffer_dma_handle; int /*<<< orphan*/  sg_chain_buffer; struct pqi_io_request* iu; } ;
struct pqi_ctrl_info {size_t sg_chain_buffer_length; unsigned int max_io_slots; struct pqi_io_request* io_request_pool; TYPE_1__* pci_dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pqi_io_request*) ; 

__attribute__((used)) static void pqi_free_all_io_requests(struct pqi_ctrl_info *ctrl_info)
{
	unsigned int i;
	struct device *dev;
	size_t sg_chain_buffer_length;
	struct pqi_io_request *io_request;

	if (!ctrl_info->io_request_pool)
		return;

	dev = &ctrl_info->pci_dev->dev;
	sg_chain_buffer_length = ctrl_info->sg_chain_buffer_length;
	io_request = ctrl_info->io_request_pool;

	for (i = 0; i < ctrl_info->max_io_slots; i++) {
		kfree(io_request->iu);
		if (!io_request->sg_chain_buffer)
			break;
		dma_free_coherent(dev, sg_chain_buffer_length,
			io_request->sg_chain_buffer,
			io_request->sg_chain_buffer_dma_handle);
		io_request++;
	}

	kfree(ctrl_info->io_request_pool);
	ctrl_info->io_request_pool = NULL;
}