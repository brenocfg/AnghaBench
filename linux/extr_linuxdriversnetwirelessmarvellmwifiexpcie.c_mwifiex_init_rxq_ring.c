#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  void* u16 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {struct mwifiex_pcie_card_reg* reg; } ;
struct pcie_service_card {struct mwifiex_pfu_buf_desc** rxbd_ring; scalar_t__ rxbd_ring_vbase; struct sk_buff** rx_buf_list; TYPE_1__ pcie; } ;
struct mwifiex_pfu_buf_desc {int flags; void* len; void* paddr; scalar_t__ offset; void* frag_len; } ;
struct mwifiex_pcie_card_reg {int ring_flag_eop; int ring_flag_sop; scalar_t__ pfu_enabled; } ;
struct mwifiex_pcie_buf_desc {int flags; void* len; void* paddr; scalar_t__ offset; void* frag_len; } ;
struct mwifiex_adapter {struct pcie_service_card* card; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INFO ; 
 int MWIFIEX_MAX_TXRX_BD ; 
 int /*<<< orphan*/  MWIFIEX_RX_DATA_BUF_SIZE ; 
 void* MWIFIEX_SKB_DMA_ADDR (struct sk_buff*) ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 struct sk_buff* mwifiex_alloc_dma_align_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ mwifiex_map_pci_memory (struct mwifiex_adapter*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_init_rxq_ring(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;
	const struct mwifiex_pcie_card_reg *reg = card->pcie.reg;
	struct sk_buff *skb;
	struct mwifiex_pcie_buf_desc *desc;
	struct mwifiex_pfu_buf_desc *desc2;
	dma_addr_t buf_pa;
	int i;

	for (i = 0; i < MWIFIEX_MAX_TXRX_BD; i++) {
		/* Allocate skb here so that firmware can DMA data from it */
		skb = mwifiex_alloc_dma_align_buf(MWIFIEX_RX_DATA_BUF_SIZE,
						  GFP_KERNEL);
		if (!skb) {
			mwifiex_dbg(adapter, ERROR,
				    "Unable to allocate skb for RX ring.\n");
			kfree(card->rxbd_ring_vbase);
			return -ENOMEM;
		}

		if (mwifiex_map_pci_memory(adapter, skb,
					   MWIFIEX_RX_DATA_BUF_SIZE,
					   PCI_DMA_FROMDEVICE))
			return -1;

		buf_pa = MWIFIEX_SKB_DMA_ADDR(skb);

		mwifiex_dbg(adapter, INFO,
			    "info: RX ring: skb=%p len=%d data=%p buf_pa=%#x:%x\n",
			    skb, skb->len, skb->data, (u32)buf_pa,
			    (u32)((u64)buf_pa >> 32));

		card->rx_buf_list[i] = skb;
		if (reg->pfu_enabled) {
			card->rxbd_ring[i] = (void *)card->rxbd_ring_vbase +
					     (sizeof(*desc2) * i);
			desc2 = card->rxbd_ring[i];
			desc2->paddr = buf_pa;
			desc2->len = (u16)skb->len;
			desc2->frag_len = (u16)skb->len;
			desc2->flags = reg->ring_flag_eop | reg->ring_flag_sop;
			desc2->offset = 0;
		} else {
			card->rxbd_ring[i] = (void *)(card->rxbd_ring_vbase +
					     (sizeof(*desc) * i));
			desc = card->rxbd_ring[i];
			desc->paddr = buf_pa;
			desc->len = (u16)skb->len;
			desc->flags = 0;
		}
	}

	return 0;
}