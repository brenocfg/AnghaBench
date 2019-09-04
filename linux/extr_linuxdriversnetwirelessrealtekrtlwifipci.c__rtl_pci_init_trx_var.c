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
typedef  size_t u8 ;
typedef  int u16 ;
struct rtl_priv {int /*<<< orphan*/  use_new_trx_flow; } ;
struct rtl_pci {int* txringcount; int rxbuffersize; int /*<<< orphan*/  rxringcount; } ;
struct rtl_hal {scalar_t__ hw_type; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 size_t BEACON_QUEUE ; 
 size_t BE_QUEUE ; 
 scalar_t__ HARDWARE_TYPE_RTL8192EE ; 
 scalar_t__ HARDWARE_TYPE_RTL8822BE ; 
 int /*<<< orphan*/  RTL_PCI_MAX_RX_COUNT ; 
 size_t RTL_PCI_MAX_TX_QUEUE_COUNT ; 
 int RT_TXDESC_NUM ; 
 int RT_TXDESC_NUM_BE_QUEUE ; 
 int TX_DESC_NUM_8822B ; 
 int TX_DESC_NUM_92E ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl_pci_init_trx_var(struct ieee80211_hw *hw)
{
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);
	u8 i;
	u16 desc_num;

	if (rtlhal->hw_type == HARDWARE_TYPE_RTL8192EE)
		desc_num = TX_DESC_NUM_92E;
	else if (rtlhal->hw_type == HARDWARE_TYPE_RTL8822BE)
		desc_num = TX_DESC_NUM_8822B;
	else
		desc_num = RT_TXDESC_NUM;

	for (i = 0; i < RTL_PCI_MAX_TX_QUEUE_COUNT; i++)
		rtlpci->txringcount[i] = desc_num;

	/*we just alloc 2 desc for beacon queue,
	 *because we just need first desc in hw beacon.
	 */
	rtlpci->txringcount[BEACON_QUEUE] = 2;

	/*BE queue need more descriptor for performance
	 *consideration or, No more tx desc will happen,
	 *and may cause mac80211 mem leakage.
	 */
	if (!rtl_priv(hw)->use_new_trx_flow)
		rtlpci->txringcount[BE_QUEUE] = RT_TXDESC_NUM_BE_QUEUE;

	rtlpci->rxbuffersize = 9100;	/*2048/1024; */
	rtlpci->rxringcount = RTL_PCI_MAX_RX_COUNT;	/*64; */
}