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
struct rtl_priv {int dummy; } ;
struct rtl_pci {int* irq_mask; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_HISR0_8822B ; 
 int /*<<< orphan*/  REG_HISR1_8822B ; 
 int /*<<< orphan*/  REG_HISR3_8822B ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

void rtl8822be_interrupt_recognized(struct ieee80211_hw *hw, u32 *p_inta,
				    u32 *p_intb, u32 *p_intc, u32 *p_intd)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	*p_inta =
		rtl_read_dword(rtlpriv, REG_HISR0_8822B) & rtlpci->irq_mask[0];
	rtl_write_dword(rtlpriv, REG_HISR0_8822B, *p_inta);

	*p_intb =
		rtl_read_dword(rtlpriv, REG_HISR1_8822B) & rtlpci->irq_mask[1];
	rtl_write_dword(rtlpriv, REG_HISR1_8822B, *p_intb);

	*p_intd =
		rtl_read_dword(rtlpriv, REG_HISR3_8822B) & rtlpci->irq_mask[3];
	rtl_write_dword(rtlpriv, REG_HISR3_8822B, *p_intd);
}