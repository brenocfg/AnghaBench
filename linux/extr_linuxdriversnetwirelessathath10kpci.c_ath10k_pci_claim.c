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
struct pci_dev {int dummy; } ;
struct ath10k_pci {int /*<<< orphan*/  mem; int /*<<< orphan*/  mem_len; struct pci_dev* pdev; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int BAR_NUM ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EIO ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int,...) ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iomap (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int) ; 
 int pci_request_region (struct pci_dev*,int,char*) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct ath10k*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 

__attribute__((used)) static int ath10k_pci_claim(struct ath10k *ar)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	struct pci_dev *pdev = ar_pci->pdev;
	int ret;

	pci_set_drvdata(pdev, ar);

	ret = pci_enable_device(pdev);
	if (ret) {
		ath10k_err(ar, "failed to enable pci device: %d\n", ret);
		return ret;
	}

	ret = pci_request_region(pdev, BAR_NUM, "ath");
	if (ret) {
		ath10k_err(ar, "failed to request region BAR%d: %d\n", BAR_NUM,
			   ret);
		goto err_device;
	}

	/* Target expects 32 bit DMA. Enforce it. */
	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	if (ret) {
		ath10k_err(ar, "failed to set dma mask to 32-bit: %d\n", ret);
		goto err_region;
	}

	ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
	if (ret) {
		ath10k_err(ar, "failed to set consistent dma mask to 32-bit: %d\n",
			   ret);
		goto err_region;
	}

	pci_set_master(pdev);

	/* Arrange for access to Target SoC registers. */
	ar_pci->mem_len = pci_resource_len(pdev, BAR_NUM);
	ar_pci->mem = pci_iomap(pdev, BAR_NUM, 0);
	if (!ar_pci->mem) {
		ath10k_err(ar, "failed to iomap BAR%d\n", BAR_NUM);
		ret = -EIO;
		goto err_master;
	}

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot pci_mem 0x%pK\n", ar_pci->mem);
	return 0;

err_master:
	pci_clear_master(pdev);

err_region:
	pci_release_region(pdev, BAR_NUM);

err_device:
	pci_disable_device(pdev);

	return ret;
}