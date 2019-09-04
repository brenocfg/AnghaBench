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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u16 ;
struct rtl_priv {TYPE_2__* cfg; } ;
struct rtl_pci {struct rtl8192_tx_ring* tx_ring; } ;
struct rtl8192_tx_ring {int entries; int cur_tx_wp; int /*<<< orphan*/  cur_tx_rp; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_4__ {TYPE_1__* mod_params; } ;
struct TYPE_3__ {int dma64; } ;

/* Variables and functions */
 int BEACON_QUEUE ; 
 int DMA_BIT_MASK (int) ; 
#define  HW_DESC_OWN 129 
#define  HW_DESC_RX_PREPARE 128 
 scalar_t__ MAX_RECEIVE_BUFFER_SIZE ; 
 scalar_t__ RX_DESC_SIZE ; 
 int /*<<< orphan*/  SET_RX_BUFFER_DESC_DATA_LENGTH (int*,scalar_t__) ; 
 int /*<<< orphan*/  SET_RX_BUFFER_DESC_FS (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_RX_BUFFER_DESC_LS (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_RX_BUFFER_DESC_TOTAL_LENGTH (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_RX_BUFFER_PHYSICAL_HIGH (int*,int,int) ; 
 int /*<<< orphan*/  SET_RX_BUFFER_PHYSICAL_LOW (int*,int) ; 
 int /*<<< orphan*/  SET_TX_BUFF_DESC_OWN (int*,int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  get_desc_address_from_queue_index (int) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

void rtl8822be_set_desc(struct ieee80211_hw *hw, u8 *pdesc, bool istx,
			u8 desc_name, u8 *val)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 q_idx = *val;
	bool dma64 = rtlpriv->cfg->mod_params->dma64;

	if (istx) {
		switch (desc_name) {
		case HW_DESC_OWN: {
			struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
			struct rtl8192_tx_ring *ring = &rtlpci->tx_ring[q_idx];
			u16 max_tx_desc = ring->entries;

			if (q_idx == BEACON_QUEUE) {
				/* in case of beacon, pdesc is BD desc. */
				u8 *pbd_desc = pdesc;

				ring->cur_tx_wp = 0;
				ring->cur_tx_rp = 0;
				SET_TX_BUFF_DESC_OWN(pbd_desc, 1);
				return;
			}

			/* make sure tx desc is available by caller */
			ring->cur_tx_wp = ((ring->cur_tx_wp + 1) % max_tx_desc);

			rtl_write_word(
				rtlpriv,
				get_desc_address_from_queue_index(
					q_idx),
				ring->cur_tx_wp);
		} break;
		}
	} else {
		switch (desc_name) {
		case HW_DESC_RX_PREPARE:
			SET_RX_BUFFER_DESC_LS(pdesc, 0);
			SET_RX_BUFFER_DESC_FS(pdesc, 0);
			SET_RX_BUFFER_DESC_TOTAL_LENGTH(pdesc, 0);

			SET_RX_BUFFER_DESC_DATA_LENGTH(
				pdesc, MAX_RECEIVE_BUFFER_SIZE + RX_DESC_SIZE);

			SET_RX_BUFFER_PHYSICAL_LOW(
				pdesc, (*(dma_addr_t *)val) & DMA_BIT_MASK(32));
			SET_RX_BUFFER_PHYSICAL_HIGH(
				pdesc, ((u64)(*(dma_addr_t *)val) >> 32),
				dma64);
			break;
		default:
			WARN_ONCE(true, "ERR rxdesc :%d not process\n",
				  desc_name);
			break;
		}
	}
}