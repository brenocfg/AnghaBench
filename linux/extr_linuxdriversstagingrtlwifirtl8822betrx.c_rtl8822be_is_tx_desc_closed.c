#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u16 ;
struct TYPE_4__ {scalar_t__ rfoff_reason; } ;
struct TYPE_3__ {scalar_t__ driver_is_goingto_unload; } ;
struct rtl_priv {TYPE_2__ psc; TYPE_1__ rtlhal; } ;
struct rtl_pci {struct rtl8192_tx_ring* tx_ring; } ;
struct rtl8192_tx_ring {int cur_tx_rp; int cur_tx_wp; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 size_t BEACON_QUEUE ; 
 scalar_t__ RF_CHANGE_BY_PS ; 
 scalar_t__ get_desc_address_from_queue_index (size_t) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_word (struct rtl_priv*,scalar_t__) ; 

bool rtl8822be_is_tx_desc_closed(struct ieee80211_hw *hw, u8 hw_queue,
				 u16 index)
{
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	bool ret = false;
	struct rtl8192_tx_ring *ring = &rtlpci->tx_ring[hw_queue];
	u16 cur_tx_rp, cur_tx_wp;
	u16 tmp16;

	/*
	 * design rule:
	 *     idx <= cur_tx_rp <= hw_rp <= cur_tx_wp = hw_wp
	 */

	if (index == ring->cur_tx_rp) {
		/* update only if sw_rp reach hw_rp */
		tmp16 = rtl_read_word(
			    rtlpriv,
			    get_desc_address_from_queue_index(hw_queue) + 2);

		cur_tx_rp = tmp16 & 0x01ff;
		cur_tx_wp = ring->cur_tx_wp;

		/* don't need to update ring->cur_tx_wp */
		ring->cur_tx_rp = cur_tx_rp;
	}

	if (index == ring->cur_tx_rp)
		ret = false;	/* no more */
	else
		ret = true;	/* more */

	if (hw_queue == BEACON_QUEUE)
		ret = true;

	if (rtlpriv->rtlhal.driver_is_goingto_unload ||
	    rtlpriv->psc.rfoff_reason > RF_CHANGE_BY_PS)
		ret = true;

	return ret;
}