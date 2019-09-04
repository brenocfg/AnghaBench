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
typedef  int u8 ;
struct rtl_pci {int /*<<< orphan*/  pdev; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int /*<<< orphan*/  pci_read_config_byte (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int,int) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 

__attribute__((used)) static bool rtl_pci_get_amd_l1_patch(struct ieee80211_hw *hw)
{
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	bool status = false;
	u8 offset_e0;
	unsigned int offset_e4;

	pci_write_config_byte(rtlpci->pdev, 0xe0, 0xa0);

	pci_read_config_byte(rtlpci->pdev, 0xe0, &offset_e0);

	if (offset_e0 == 0xA0) {
		pci_read_config_dword(rtlpci->pdev, 0xe4, &offset_e4);
		if (offset_e4 & BIT(23))
			status = true;
	}

	return status;
}