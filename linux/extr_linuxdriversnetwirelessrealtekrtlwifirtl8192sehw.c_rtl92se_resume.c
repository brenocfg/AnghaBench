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
typedef  int u32 ;
struct rtl_pci {int /*<<< orphan*/  pdev; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int,int) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 

void rtl92se_resume(struct ieee80211_hw *hw)
{
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u32 val;

	pci_read_config_dword(rtlpci->pdev, 0x40, &val);
	if ((val & 0x0000ff00) != 0)
		pci_write_config_dword(rtlpci->pdev, 0x40,
			val & 0xffff00ff);
}