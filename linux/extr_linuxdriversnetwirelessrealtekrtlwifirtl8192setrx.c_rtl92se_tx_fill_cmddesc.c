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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; scalar_t__ cb; } ;
struct rtl_tcb_desc {scalar_t__ cmd_or_init; int /*<<< orphan*/  last_inipkt; } ;
struct rtl_priv {int dummy; } ;
struct rtl_pci {int /*<<< orphan*/  pdev; } ;
struct rtl_hal {int /*<<< orphan*/  h2c_txcmd_seq; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PCI_TX_DESC_CONTENT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMP_SEND ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 scalar_t__ DESC_PACKET_TYPE_INIT ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SET_BITS_TO_LE_4BYTE (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_FIRST_SEG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_LAST_SEG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_LINIP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_OFFSET (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_OWN (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_PKT_SIZE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_QUEUE_SEL (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_BUFFER_ADDRESS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_BUFFER_SIZE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_CMDDESC_SIZE_RTL8192S ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  wmb () ; 

void rtl92se_tx_fill_cmddesc(struct ieee80211_hw *hw, u8 *pdesc,
	bool firstseg, bool lastseg, struct sk_buff *skb)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_tcb_desc *tcb_desc = (struct rtl_tcb_desc *)(skb->cb);

	dma_addr_t mapping = pci_map_single(rtlpci->pdev, skb->data, skb->len,
			PCI_DMA_TODEVICE);

	if (pci_dma_mapping_error(rtlpci->pdev, mapping)) {
		RT_TRACE(rtlpriv, COMP_SEND, DBG_TRACE,
			 "DMA mapping error\n");
		return;
	}
	/* Clear all status	*/
	CLEAR_PCI_TX_DESC_CONTENT(pdesc, TX_CMDDESC_SIZE_RTL8192S);

	/* This bit indicate this packet is used for FW download. */
	if (tcb_desc->cmd_or_init == DESC_PACKET_TYPE_INIT) {
		/* For firmware downlaod we only need to set LINIP */
		SET_TX_DESC_LINIP(pdesc, tcb_desc->last_inipkt);

		/* 92SE must set as 1 for firmware download HW DMA error */
		SET_TX_DESC_FIRST_SEG(pdesc, 1);
		SET_TX_DESC_LAST_SEG(pdesc, 1);

		/* 92SE need not to set TX packet size when firmware download */
		SET_TX_DESC_PKT_SIZE(pdesc, (u16)(skb->len));
		SET_TX_DESC_TX_BUFFER_SIZE(pdesc, (u16)(skb->len));
		SET_TX_DESC_TX_BUFFER_ADDRESS(pdesc, mapping);

		wmb();
		SET_TX_DESC_OWN(pdesc, 1);
	} else { /* H2C Command Desc format (Host TXCMD) */
		/* 92SE must set as 1 for firmware download HW DMA error */
		SET_TX_DESC_FIRST_SEG(pdesc, 1);
		SET_TX_DESC_LAST_SEG(pdesc, 1);

		SET_TX_DESC_OFFSET(pdesc, 0x20);

		/* Buffer size + command header */
		SET_TX_DESC_PKT_SIZE(pdesc, (u16)(skb->len));
		/* Fixed queue of H2C command */
		SET_TX_DESC_QUEUE_SEL(pdesc, 0x13);

		SET_BITS_TO_LE_4BYTE(skb->data, 24, 7, rtlhal->h2c_txcmd_seq);

		SET_TX_DESC_TX_BUFFER_SIZE(pdesc, (u16)(skb->len));
		SET_TX_DESC_TX_BUFFER_ADDRESS(pdesc, mapping);

		wmb();
		SET_TX_DESC_OWN(pdesc, 1);

	}
}