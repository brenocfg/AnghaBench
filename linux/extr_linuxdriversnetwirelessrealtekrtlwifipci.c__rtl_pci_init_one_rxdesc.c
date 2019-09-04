#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ cb; } ;
struct rtl_priv {TYPE_3__* cfg; scalar_t__ use_new_trx_flow; } ;
struct rtl_pci {int /*<<< orphan*/  rxbuffersize; TYPE_1__* rx_ring; int /*<<< orphan*/  pdev; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_desc ) (struct ieee80211_hw*,int*,int,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_4__ {struct sk_buff** rx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_DESC_RXBUFF_ADDR ; 
 int /*<<< orphan*/  HW_DESC_RXOWN ; 
 int /*<<< orphan*/  HW_DESC_RXPKT_LEN ; 
 int /*<<< orphan*/  HW_DESC_RX_PREPARE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct ieee80211_hw*,int*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct ieee80211_hw*,int*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int _rtl_pci_init_one_rxdesc(struct ieee80211_hw *hw,
				    struct sk_buff *new_skb, u8 *entry,
				    int rxring_idx, int desc_idx)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u32 bufferaddress;
	u8 tmp_one = 1;
	struct sk_buff *skb;

	if (likely(new_skb)) {
		skb = new_skb;
		goto remap;
	}
	skb = dev_alloc_skb(rtlpci->rxbuffersize);
	if (!skb)
		return 0;

remap:
	/* just set skb->cb to mapping addr for pci_unmap_single use */
	*((dma_addr_t *)skb->cb) =
		pci_map_single(rtlpci->pdev, skb_tail_pointer(skb),
			       rtlpci->rxbuffersize, PCI_DMA_FROMDEVICE);
	bufferaddress = *((dma_addr_t *)skb->cb);
	if (pci_dma_mapping_error(rtlpci->pdev, bufferaddress))
		return 0;
	rtlpci->rx_ring[rxring_idx].rx_buf[desc_idx] = skb;
	if (rtlpriv->use_new_trx_flow) {
		/* skb->cb may be 64 bit address */
		rtlpriv->cfg->ops->set_desc(hw, (u8 *)entry, false,
					    HW_DESC_RX_PREPARE,
					    (u8 *)(dma_addr_t *)skb->cb);
	} else {
		rtlpriv->cfg->ops->set_desc(hw, (u8 *)entry, false,
					    HW_DESC_RXBUFF_ADDR,
					    (u8 *)&bufferaddress);
		rtlpriv->cfg->ops->set_desc(hw, (u8 *)entry, false,
					    HW_DESC_RXPKT_LEN,
					    (u8 *)&rtlpci->rxbuffersize);
		rtlpriv->cfg->ops->set_desc(hw, (u8 *)entry, false,
					    HW_DESC_RXOWN,
					    (u8 *)&tmp_one);
	}
	return 1;
}