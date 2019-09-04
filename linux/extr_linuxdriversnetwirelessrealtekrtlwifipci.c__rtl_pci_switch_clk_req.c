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
typedef  int /*<<< orphan*/  u8 ;
struct rtl_pci {int /*<<< orphan*/  pdev; } ;
struct rtl_hal {scalar_t__ hw_type; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ HARDWARE_TYPE_RTL8192SE ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (int /*<<< orphan*/ ) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void _rtl_pci_switch_clk_req(struct ieee80211_hw *hw, u8 value)
{
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	pci_write_config_byte(rtlpci->pdev, 0x81, value);

	if (rtlhal->hw_type == HARDWARE_TYPE_RTL8192SE)
		udelay(100);
}