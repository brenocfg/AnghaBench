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
struct csio_lnode {int /*<<< orphan*/  flags; TYPE_1__* mgmt_req; } ;
struct csio_ioreq {int dummy; } ;
struct csio_hw {int /*<<< orphan*/  pdev; } ;
struct csio_dma_buf {int len; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  paddr; } ;
struct TYPE_3__ {struct csio_dma_buf dma_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_LNF_FDMI_ENABLE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*) ; 
 int /*<<< orphan*/  csio_ln_err (struct csio_lnode*,char*) ; 
 struct csio_hw* csio_lnode_to_hw (struct csio_lnode*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_err_nomem ; 
 int /*<<< orphan*/  pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
csio_ln_fdmi_init(struct csio_lnode *ln)
{
	struct csio_hw *hw = csio_lnode_to_hw(ln);
	struct csio_dma_buf	*dma_buf;

	/* Allocate MGMT request required for FDMI */
	ln->mgmt_req = kzalloc(sizeof(struct csio_ioreq), GFP_KERNEL);
	if (!ln->mgmt_req) {
		csio_ln_err(ln, "Failed to alloc ioreq for FDMI\n");
		CSIO_INC_STATS(hw, n_err_nomem);
		return -ENOMEM;
	}

	/* Allocate Dma buffers for FDMI response Payload */
	dma_buf = &ln->mgmt_req->dma_buf;
	dma_buf->len = 2048;
	dma_buf->vaddr = pci_alloc_consistent(hw->pdev, dma_buf->len,
						&dma_buf->paddr);
	if (!dma_buf->vaddr) {
		csio_err(hw, "Failed to alloc DMA buffer for FDMI!\n");
		kfree(ln->mgmt_req);
		ln->mgmt_req = NULL;
		return -ENOMEM;
	}

	ln->flags |= CSIO_LNF_FDMI_ENABLE;
	return 0;
}