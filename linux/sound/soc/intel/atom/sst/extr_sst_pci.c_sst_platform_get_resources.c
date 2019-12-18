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
struct pci_dev {int dummy; } ;
struct intel_sst_drv {scalar_t__ dev_id; int /*<<< orphan*/ * dram; int /*<<< orphan*/  dev; void* dram_base; void* dram_end; int /*<<< orphan*/ * iram; void* iram_base; void* iram_end; int /*<<< orphan*/ * mailbox; void* mailbox_add; int /*<<< orphan*/ * shim; void* shim_phy_add; int /*<<< orphan*/ * ddr; void* ddr_end; TYPE_2__* pdata; void* ddr_base; struct pci_dev* pci; } ;
struct TYPE_4__ {TYPE_1__* lib_info; } ;
struct TYPE_3__ {int mod_base; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SST_DRV_NAME ; 
 scalar_t__ SST_MRFLD_PCI_ID ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 void* pci_resource_end (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int) ; 
 void* pci_resource_start (struct pci_dev*,int) ; 
 void* pcim_iomap (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int relocate_imr_addr_mrfld (void*) ; 

__attribute__((used)) static int sst_platform_get_resources(struct intel_sst_drv *ctx)
{
	int ddr_base, ret = 0;
	struct pci_dev *pci = ctx->pci;

	ret = pci_request_regions(pci, SST_DRV_NAME);
	if (ret)
		return ret;

	/* map registers */
	/* DDR base */
	if (ctx->dev_id == SST_MRFLD_PCI_ID) {
		ctx->ddr_base = pci_resource_start(pci, 0);
		/* check that the relocated IMR base matches with FW Binary */
		ddr_base = relocate_imr_addr_mrfld(ctx->ddr_base);
		if (!ctx->pdata->lib_info) {
			dev_err(ctx->dev, "lib_info pointer NULL\n");
			ret = -EINVAL;
			goto do_release_regions;
		}
		if (ddr_base != ctx->pdata->lib_info->mod_base) {
			dev_err(ctx->dev,
					"FW LSP DDR BASE does not match with IFWI\n");
			ret = -EINVAL;
			goto do_release_regions;
		}
		ctx->ddr_end = pci_resource_end(pci, 0);

		ctx->ddr = pcim_iomap(pci, 0,
					pci_resource_len(pci, 0));
		if (!ctx->ddr) {
			ret = -EINVAL;
			goto do_release_regions;
		}
		dev_dbg(ctx->dev, "sst: DDR Ptr %p\n", ctx->ddr);
	} else {
		ctx->ddr = NULL;
	}
	/* SHIM */
	ctx->shim_phy_add = pci_resource_start(pci, 1);
	ctx->shim = pcim_iomap(pci, 1, pci_resource_len(pci, 1));
	if (!ctx->shim) {
		ret = -EINVAL;
		goto do_release_regions;
	}
	dev_dbg(ctx->dev, "SST Shim Ptr %p\n", ctx->shim);

	/* Shared SRAM */
	ctx->mailbox_add = pci_resource_start(pci, 2);
	ctx->mailbox = pcim_iomap(pci, 2, pci_resource_len(pci, 2));
	if (!ctx->mailbox) {
		ret = -EINVAL;
		goto do_release_regions;
	}
	dev_dbg(ctx->dev, "SRAM Ptr %p\n", ctx->mailbox);

	/* IRAM */
	ctx->iram_end = pci_resource_end(pci, 3);
	ctx->iram_base = pci_resource_start(pci, 3);
	ctx->iram = pcim_iomap(pci, 3, pci_resource_len(pci, 3));
	if (!ctx->iram) {
		ret = -EINVAL;
		goto do_release_regions;
	}
	dev_dbg(ctx->dev, "IRAM Ptr %p\n", ctx->iram);

	/* DRAM */
	ctx->dram_end = pci_resource_end(pci, 4);
	ctx->dram_base = pci_resource_start(pci, 4);
	ctx->dram = pcim_iomap(pci, 4, pci_resource_len(pci, 4));
	if (!ctx->dram) {
		ret = -EINVAL;
		goto do_release_regions;
	}
	dev_dbg(ctx->dev, "DRAM Ptr %p\n", ctx->dram);
do_release_regions:
	pci_release_regions(pci);
	return 0;
}