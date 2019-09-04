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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct rtl_priv {int dummy; } ;
struct rtl_pci {int /*<<< orphan*/  pdev; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PCI_TX_DESC_CONTENT (int*,int) ; 
 int /*<<< orphan*/  COMP_CMD ; 
 int /*<<< orphan*/  COMP_SEND ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  DESC_RATE1M ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int QSLT_BEACON ; 
 int /*<<< orphan*/  RT_PRINT_DATA (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SET_TX_DESC_FIRST_SEG (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_LAST_SEG (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_LINIP (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_MACID (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_OFFSET (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_OWN (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_PKT_SIZE (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_QUEUE_SEL (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_RATE_ID (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_SEQ (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_BUFFER_ADDRESS (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_BUFFER_SIZE (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_RATE (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_USE_RATE (int*,int) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl92ee_tx_fill_cmddesc(struct ieee80211_hw *hw,
			     u8 *pdesc, bool firstseg,
			     bool lastseg, struct sk_buff *skb)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u8 fw_queue = QSLT_BEACON;
	dma_addr_t mapping = pci_map_single(rtlpci->pdev,
					    skb->data, skb->len,
					    PCI_DMA_TODEVICE);
	u8 txdesc_len = 40;

	if (pci_dma_mapping_error(rtlpci->pdev, mapping)) {
		RT_TRACE(rtlpriv, COMP_SEND, DBG_TRACE,
			 "DMA mapping error\n");
		return;
	}
	CLEAR_PCI_TX_DESC_CONTENT(pdesc, txdesc_len);

	if (firstseg)
		SET_TX_DESC_OFFSET(pdesc, txdesc_len);

	SET_TX_DESC_TX_RATE(pdesc, DESC_RATE1M);

	SET_TX_DESC_SEQ(pdesc, 0);

	SET_TX_DESC_LINIP(pdesc, 0);

	SET_TX_DESC_QUEUE_SEL(pdesc, fw_queue);

	SET_TX_DESC_FIRST_SEG(pdesc, 1);
	SET_TX_DESC_LAST_SEG(pdesc, 1);

	SET_TX_DESC_TX_BUFFER_SIZE(pdesc, (u16)(skb->len));

	SET_TX_DESC_TX_BUFFER_ADDRESS(pdesc, mapping);

	SET_TX_DESC_RATE_ID(pdesc, 7);
	SET_TX_DESC_MACID(pdesc, 0);

	SET_TX_DESC_OWN(pdesc, 1);

	SET_TX_DESC_PKT_SIZE((u8 *)pdesc, (u16)(skb->len));

	SET_TX_DESC_FIRST_SEG(pdesc, 1);
	SET_TX_DESC_LAST_SEG(pdesc, 1);

	SET_TX_DESC_OFFSET(pdesc, 40);

	SET_TX_DESC_USE_RATE(pdesc, 1);

	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_LOUD,
		      "H2C Tx Cmd Content\n", pdesc, txdesc_len);
}