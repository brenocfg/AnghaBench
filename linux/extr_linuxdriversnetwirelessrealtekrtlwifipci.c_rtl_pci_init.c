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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtl_pci_init_struct (struct ieee80211_hw*,struct pci_dev*) ; 
 int _rtl_pci_init_trx_ring (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int rtl_pci_init(struct ieee80211_hw *hw, struct pci_dev *pdev)
{
	int err;

	_rtl_pci_init_struct(hw, pdev);

	err = _rtl_pci_init_trx_ring(hw);
	if (err) {
		pr_err("tx ring initialization failed\n");
		return err;
	}

	return 0;
}