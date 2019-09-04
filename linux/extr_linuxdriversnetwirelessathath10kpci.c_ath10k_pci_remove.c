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
struct ath10k_pci {int dummy; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_PCI ; 
 int /*<<< orphan*/  ath10k_core_destroy (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_core_unregister (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_pci_deinit_irq (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_free_irq (struct ath10k*) ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_release (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_release_resource (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_sleep_sync (struct ath10k*) ; 
 struct ath10k* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void ath10k_pci_remove(struct pci_dev *pdev)
{
	struct ath10k *ar = pci_get_drvdata(pdev);
	struct ath10k_pci *ar_pci;

	ath10k_dbg(ar, ATH10K_DBG_PCI, "pci remove\n");

	if (!ar)
		return;

	ar_pci = ath10k_pci_priv(ar);

	if (!ar_pci)
		return;

	ath10k_core_unregister(ar);
	ath10k_pci_free_irq(ar);
	ath10k_pci_deinit_irq(ar);
	ath10k_pci_release_resource(ar);
	ath10k_pci_sleep_sync(ar);
	ath10k_pci_release(ar);
	ath10k_core_destroy(ar);
}