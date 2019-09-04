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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct rtl_priv {int dummy; } ;
struct rtl_pci {int /*<<< orphan*/  pdev; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PCI_TX_DESC_CONTENT (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  COMP_CMD ; 
 int /*<<< orphan*/  COMP_SEND ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DESC_RATE1M ; 
 scalar_t__ H2C_QUEUE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  RT_PRINT_DATA (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SET_TX_DESC_DATARATE (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_LS (scalar_t__*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_MACID (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_OFFSET (scalar_t__*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_QSEL (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  SET_TX_DESC_RATE_ID (scalar_t__*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_SW_SEQ (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_TXPKTSIZE (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_USE_RATE (scalar_t__*,int) ; 
 scalar_t__ _rtl8822be_map_hwqueue_to_fwqueue (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8822be_pre_fill_tx_bd_desc (struct ieee80211_hw*,scalar_t__*,scalar_t__*,scalar_t__,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl8822be_tx_fill_special_desc(struct ieee80211_hw *hw, u8 *pdesc,
				    u8 *pbd_desc, struct sk_buff *skb,
				    u8 hw_queue)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u8 fw_queue;
	u8 txdesc_len = 48;

	dma_addr_t mapping = pci_map_single(rtlpci->pdev, skb->data, skb->len,
					    PCI_DMA_TODEVICE);

	if (pci_dma_mapping_error(rtlpci->pdev, mapping)) {
		RT_TRACE(rtlpriv, COMP_SEND, DBG_DMESG, "DMA mapping error");
		return;
	}

	rtl8822be_pre_fill_tx_bd_desc(hw, pbd_desc, pdesc, hw_queue, skb,
				      mapping);

	/* it should be BEACON_QUEUE or H2C_QUEUE,
	 * so skb=NULL is safe to assert
	 */
	fw_queue = _rtl8822be_map_hwqueue_to_fwqueue(NULL, hw_queue);

	CLEAR_PCI_TX_DESC_CONTENT(pdesc, txdesc_len);

	/* common part for BEACON and H2C */
	SET_TX_DESC_TXPKTSIZE((u8 *)pdesc, (u16)(skb->len));

	SET_TX_DESC_QSEL(pdesc, fw_queue);

	if (hw_queue == H2C_QUEUE) {
		/* fill H2C */
		SET_TX_DESC_OFFSET(pdesc, 0);

	} else {
		/* fill beacon */
		SET_TX_DESC_OFFSET(pdesc, txdesc_len);

		SET_TX_DESC_DATARATE(pdesc, DESC_RATE1M);

		SET_TX_DESC_SW_SEQ(pdesc, 0);

		SET_TX_DESC_RATE_ID(pdesc, 7);
		SET_TX_DESC_MACID(pdesc, 0);

		SET_TX_DESC_LS(pdesc, 1);

		SET_TX_DESC_OFFSET(pdesc, 48);

		SET_TX_DESC_USE_RATE(pdesc, 1);
	}

	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_LOUD, "H2C Tx Cmd Content\n",
		      pdesc, txdesc_len);
}