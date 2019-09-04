#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int len; } ;
struct TYPE_8__ {scalar_t__ earlymode_enable; } ;
struct rtl_priv {TYPE_4__ rtlhal; TYPE_2__* cfg; } ;
struct rtl_pci {TYPE_3__* tx_ring; } ;
struct ieee80211_hw {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_7__ {int cur_tx_wp; scalar_t__ dma; } ;
struct TYPE_6__ {TYPE_1__* mod_params; } ;
struct TYPE_5__ {int dma64; } ;

/* Variables and functions */
 size_t BEACON_QUEUE ; 
 int /*<<< orphan*/  CLEAR_PCI_TX_DESC_CONTENT (size_t*,int) ; 
 int RTL8192EE_SEG_NUM ; 
 int /*<<< orphan*/  SET_TXBUFFER_DESC_ADD_HIGH_WITH_OFFSET (size_t*,int,int,int) ; 
 int /*<<< orphan*/  SET_TXBUFFER_DESC_ADD_LOW_WITH_OFFSET (size_t*,int,scalar_t__) ; 
 int /*<<< orphan*/  SET_TXBUFFER_DESC_AMSDU_WITH_OFFSET (size_t*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TXBUFFER_DESC_LEN_WITH_OFFSET (size_t*,int,int) ; 
 int /*<<< orphan*/  SET_TX_BUFF_DESC_ADDR_HIGH_0 (size_t*,int,int) ; 
 int /*<<< orphan*/  SET_TX_BUFF_DESC_ADDR_LOW_0 (size_t*,scalar_t__) ; 
 int /*<<< orphan*/  SET_TX_BUFF_DESC_LEN_0 (size_t*,int) ; 
 int /*<<< orphan*/  SET_TX_BUFF_DESC_OWN (size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_BUFF_DESC_PSB (size_t*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_PKT_SIZE (size_t*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_BUFFER_SIZE (size_t*,int) ; 
 int TX_DESC_SIZE ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl92ee_pre_fill_tx_bd_desc(struct ieee80211_hw *hw,
				 u8 *tx_bd_desc, u8 *desc, u8 queue_index,
				 struct sk_buff *skb, dma_addr_t addr)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u32 pkt_len = skb->len;
	u16 desc_size = 40; /*tx desc size*/
	u32 psblen = 0;
	u16 tx_page_size = 0;
	u32 total_packet_size = 0;
	u16 current_bd_desc;
	u8 i = 0;
	u16 real_desc_size = 0x28;
	u16	append_early_mode_size = 0;
	u8 segmentnum = 1 << (RTL8192EE_SEG_NUM + 1);
	dma_addr_t desc_dma_addr;
	bool dma64 = rtlpriv->cfg->mod_params->dma64;

	tx_page_size = 2;
	current_bd_desc = rtlpci->tx_ring[queue_index].cur_tx_wp;

	total_packet_size = desc_size+pkt_len;

	if (rtlpriv->rtlhal.earlymode_enable)	{
		if (queue_index < BEACON_QUEUE) {
			append_early_mode_size = 8;
			total_packet_size += append_early_mode_size;
		}
	}

	if (tx_page_size > 0) {
		psblen = (pkt_len + real_desc_size + append_early_mode_size) /
			 (tx_page_size * 128);

		if (psblen * (tx_page_size * 128) < total_packet_size)
			psblen += 1;
	}

	/* tx desc addr */
	desc_dma_addr = rtlpci->tx_ring[queue_index].dma +
			(current_bd_desc * TX_DESC_SIZE);

	/* Reset */
	SET_TX_BUFF_DESC_LEN_0(tx_bd_desc, 0);
	SET_TX_BUFF_DESC_PSB(tx_bd_desc, 0);
	SET_TX_BUFF_DESC_OWN(tx_bd_desc, 0);

	for (i = 1; i < segmentnum; i++) {
		SET_TXBUFFER_DESC_LEN_WITH_OFFSET(tx_bd_desc, i, 0);
		SET_TXBUFFER_DESC_AMSDU_WITH_OFFSET(tx_bd_desc, i, 0);
		SET_TXBUFFER_DESC_ADD_LOW_WITH_OFFSET(tx_bd_desc, i, 0);
		SET_TXBUFFER_DESC_ADD_HIGH_WITH_OFFSET(tx_bd_desc, i, 0, dma64);
	}

	/* Clear all status */
	CLEAR_PCI_TX_DESC_CONTENT(desc, TX_DESC_SIZE);

	if (rtlpriv->rtlhal.earlymode_enable) {
		if (queue_index < BEACON_QUEUE) {
			/* This if needs braces */
			SET_TX_BUFF_DESC_LEN_0(tx_bd_desc, desc_size + 8);
		} else {
			SET_TX_BUFF_DESC_LEN_0(tx_bd_desc, desc_size);
		}
	} else {
		SET_TX_BUFF_DESC_LEN_0(tx_bd_desc, desc_size);
	}
	SET_TX_BUFF_DESC_PSB(tx_bd_desc, psblen);
	SET_TX_BUFF_DESC_ADDR_LOW_0(tx_bd_desc, desc_dma_addr);
	SET_TX_BUFF_DESC_ADDR_HIGH_0(tx_bd_desc, ((u64)desc_dma_addr >> 32),
				     dma64);

	SET_TXBUFFER_DESC_LEN_WITH_OFFSET(tx_bd_desc, 1, pkt_len);
	/* don't using extendsion mode. */
	SET_TXBUFFER_DESC_AMSDU_WITH_OFFSET(tx_bd_desc, 1, 0);
	SET_TXBUFFER_DESC_ADD_LOW_WITH_OFFSET(tx_bd_desc, 1, addr);
	SET_TXBUFFER_DESC_ADD_HIGH_WITH_OFFSET(tx_bd_desc, 1,
					       ((u64)addr >> 32), dma64);

	SET_TX_DESC_PKT_SIZE(desc, (u16)(pkt_len));
	SET_TX_DESC_TX_BUFFER_SIZE(desc, (u16)(pkt_len));
}