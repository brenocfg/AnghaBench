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
struct ath10k_pci {int /*<<< orphan*/  link_ctl; int /*<<< orphan*/  pdev; } ;
struct ath10k {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int /*<<< orphan*/  PCI_EXP_LNKCTL ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_pci_irq_enable (struct ath10k*) ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_rx_post (struct ath10k*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcie_capability_write_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_pci_hif_start(struct ath10k *ar)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot hif start\n");

	napi_enable(&ar->napi);

	ath10k_pci_irq_enable(ar);
	ath10k_pci_rx_post(ar);

	pcie_capability_write_word(ar_pci->pdev, PCI_EXP_LNKCTL,
				   ar_pci->link_ctl);

	return 0;
}