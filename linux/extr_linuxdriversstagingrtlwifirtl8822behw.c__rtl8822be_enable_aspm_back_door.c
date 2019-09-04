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
struct rtl_ps_ctl {int /*<<< orphan*/  support_backdoor; } ;
struct rtl_pci {int /*<<< orphan*/  pdev; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int ASPM_L1_LATENCY ; 
 int BIT (int) ; 
 int /*<<< orphan*/  pci_read_config_byte (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int,int) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _rtl8822be_enable_aspm_back_door(struct ieee80211_hw *hw)
{
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u8 tmp;

	if (!ppsc->support_backdoor)
		return;

	pci_read_config_byte(rtlpci->pdev, 0x70f, &tmp);
	pci_write_config_byte(rtlpci->pdev, 0x70f, tmp | ASPM_L1_LATENCY << 3);

	pci_read_config_byte(rtlpci->pdev, 0x719, &tmp);
	pci_write_config_byte(rtlpci->pdev, 0x719, tmp | BIT(3) | BIT(4));
}