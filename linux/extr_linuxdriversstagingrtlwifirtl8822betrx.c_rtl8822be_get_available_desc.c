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
struct rtl8192_tx_ring {int /*<<< orphan*/  cur_tx_wp; int /*<<< orphan*/  cur_tx_rp; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_DESC_NUM_8822B ; 
 int /*<<< orphan*/  calc_fifo_space (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 

u16 rtl8822be_get_available_desc(struct ieee80211_hw *hw, u8 q_idx)
{
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl8192_tx_ring *ring = &rtlpci->tx_ring[q_idx];

	return calc_fifo_space(ring->cur_tx_rp, ring->cur_tx_wp,
			       TX_DESC_NUM_8822B);
}