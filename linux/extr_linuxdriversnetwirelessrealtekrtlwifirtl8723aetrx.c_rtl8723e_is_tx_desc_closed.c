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
typedef  int /*<<< orphan*/  u16 ;
struct rtl_pci {struct rtl8192_tx_ring* tx_ring; } ;
struct rtl8192_tx_ring {size_t idx; int /*<<< orphan*/ * desc; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_DESC_OWN ; 
 int /*<<< orphan*/  rtl8723e_get_desc (struct ieee80211_hw*,size_t*,int,int /*<<< orphan*/ ) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 

bool rtl8723e_is_tx_desc_closed(struct ieee80211_hw *hw,
				u8 hw_queue, u16 index)
{
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl8192_tx_ring *ring = &rtlpci->tx_ring[hw_queue];
	u8 *entry = (u8 *)(&ring->desc[ring->idx]);
	u8 own = (u8)rtl8723e_get_desc(hw, entry, true, HW_DESC_OWN);

	/**
	 *beacon packet will only use the first
	 *descriptor defautly,and the own may not
	 *be cleared by the hardware
	 */
	if (own)
		return false;
	return true;
}