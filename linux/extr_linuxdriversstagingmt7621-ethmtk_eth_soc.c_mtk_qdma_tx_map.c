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
typedef  int u32 ;
struct skb_frag_struct {int dummy; } ;
struct sk_buff {scalar_t__ ip_summed; int /*<<< orphan*/  xmit_more; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct mtk_tx_ring {int /*<<< orphan*/  tx_free_count; struct mtk_tx_dma* tx_next_free; struct mtk_tx_dma* tx_last_free; } ;
struct mtk_tx_dma {int /*<<< orphan*/  txd3; int /*<<< orphan*/  txd2; int /*<<< orphan*/  txd4; int /*<<< orphan*/  txd1; } ;
struct mtk_tx_buf {struct sk_buff* skb; int /*<<< orphan*/  flags; } ;
struct mtk_mac {int id; struct mtk_eth* hw; } ;
struct mtk_eth {TYPE_1__* soc; } ;
typedef  int dma_addr_t ;
struct TYPE_4__ {unsigned int nr_frags; struct skb_frag_struct* frags; } ;
struct TYPE_3__ {int txd4; int mac_count; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 scalar_t__ DMA_DUMMY_DESC ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MTK_QTX_CTX_PTR ; 
 int /*<<< orphan*/  MTK_TX_FLAGS_PAGE0 ; 
 int /*<<< orphan*/  MTK_TX_FLAGS_SINGLE0 ; 
 int QDMA_TX_SWC ; 
 int /*<<< orphan*/  TX_DMA_BUF_LEN ; 
 int TX_DMA_CHKSUM ; 
 int /*<<< orphan*/  TX_DMA_DESP2_DEF ; 
 int TX_DMA_FPORT_SHIFT ; 
 int TX_DMA_INS_VLAN_MT7621 ; 
 int TX_DMA_LS0 ; 
 int TX_DMA_PLEN0 (unsigned int) ; 
 int TX_DMA_TSO ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_addr0 ; 
 int /*<<< orphan*/  dma_len0 ; 
 int dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct mtk_tx_buf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct mtk_tx_buf*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (struct mtk_tx_buf*,int /*<<< orphan*/ ,int) ; 
 unsigned int min (int,int /*<<< orphan*/ ) ; 
 struct mtk_tx_buf* mtk_desc_to_tx_buf (struct mtk_tx_ring*,struct mtk_tx_dma*) ; 
 void* mtk_tx_next_qdma (struct mtk_tx_ring*,struct mtk_tx_dma*) ; 
 int /*<<< orphan*/  mtk_txd_unmap (int /*<<< orphan*/ *,struct mtk_tx_buf*) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_sent_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_xmit_stopped (int /*<<< orphan*/ ) ; 
 int skb_frag_dma_map (int /*<<< orphan*/ *,struct skb_frag_struct*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int skb_frag_size (struct skb_frag_struct*) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 int skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int mtk_qdma_tx_map(struct sk_buff *skb, struct net_device *dev,
			   int tx_num, struct mtk_tx_ring *ring, bool gso)
{
	struct mtk_mac *mac = netdev_priv(dev);
	struct mtk_eth *eth = mac->hw;
	struct mtk_tx_dma *itxd, *txd;
	struct mtk_tx_buf *tx_buf;
	dma_addr_t mapped_addr;
	unsigned int nr_frags;
	int i, n_desc = 1;
	u32 txd4 = eth->soc->txd4;

	itxd = ring->tx_next_free;
	if (itxd == ring->tx_last_free)
		return -ENOMEM;

	if (eth->soc->mac_count > 1)
		txd4 |= (mac->id + 1) << TX_DMA_FPORT_SHIFT;

	tx_buf = mtk_desc_to_tx_buf(ring, itxd);
	memset(tx_buf, 0, sizeof(*tx_buf));

	if (gso)
		txd4 |= TX_DMA_TSO;

	/* TX Checksum offload */
	if (skb->ip_summed == CHECKSUM_PARTIAL)
		txd4 |= TX_DMA_CHKSUM;

	/* VLAN header offload */
	if (skb_vlan_tag_present(skb))
		txd4 |= TX_DMA_INS_VLAN_MT7621 | skb_vlan_tag_get(skb);

	mapped_addr = dma_map_single(&dev->dev, skb->data,
				     skb_headlen(skb), DMA_TO_DEVICE);
	if (unlikely(dma_mapping_error(&dev->dev, mapped_addr)))
		return -ENOMEM;

	WRITE_ONCE(itxd->txd1, mapped_addr);
	tx_buf->flags |= MTK_TX_FLAGS_SINGLE0;
	dma_unmap_addr_set(tx_buf, dma_addr0, mapped_addr);
	dma_unmap_len_set(tx_buf, dma_len0, skb_headlen(skb));

	/* TX SG offload */
	txd = itxd;
	nr_frags = skb_shinfo(skb)->nr_frags;
	for (i = 0; i < nr_frags; i++) {
		struct skb_frag_struct *frag = &skb_shinfo(skb)->frags[i];
		unsigned int offset = 0;
		int frag_size = skb_frag_size(frag);

		while (frag_size) {
			bool last_frag = false;
			unsigned int frag_map_size;

			txd = mtk_tx_next_qdma(ring, txd);
			if (txd == ring->tx_last_free)
				goto err_dma;

			n_desc++;
			frag_map_size = min(frag_size, TX_DMA_BUF_LEN);
			mapped_addr = skb_frag_dma_map(&dev->dev, frag, offset,
						       frag_map_size,
						       DMA_TO_DEVICE);
			if (unlikely(dma_mapping_error(&dev->dev, mapped_addr)))
				goto err_dma;

			if (i == nr_frags - 1 &&
			    (frag_size - frag_map_size) == 0)
				last_frag = true;

			WRITE_ONCE(txd->txd1, mapped_addr);
			WRITE_ONCE(txd->txd3, (QDMA_TX_SWC |
					       TX_DMA_PLEN0(frag_map_size) |
					       last_frag * TX_DMA_LS0) |
					       mac->id);
			WRITE_ONCE(txd->txd4, 0);

			tx_buf->skb = (struct sk_buff *)DMA_DUMMY_DESC;
			tx_buf = mtk_desc_to_tx_buf(ring, txd);
			memset(tx_buf, 0, sizeof(*tx_buf));

			tx_buf->flags |= MTK_TX_FLAGS_PAGE0;
			dma_unmap_addr_set(tx_buf, dma_addr0, mapped_addr);
			dma_unmap_len_set(tx_buf, dma_len0, frag_map_size);
			frag_size -= frag_map_size;
			offset += frag_map_size;
		}
	}

	/* store skb to cleanup */
	tx_buf->skb = skb;

	WRITE_ONCE(itxd->txd4, txd4);
	WRITE_ONCE(itxd->txd3, (QDMA_TX_SWC | TX_DMA_PLEN0(skb_headlen(skb)) |
				(!nr_frags * TX_DMA_LS0)));

	netdev_sent_queue(dev, skb->len);
	skb_tx_timestamp(skb);

	ring->tx_next_free = mtk_tx_next_qdma(ring, txd);
	atomic_sub(n_desc, &ring->tx_free_count);

	/* make sure that all changes to the dma ring are flushed before we
	 * continue
	 */
	wmb();

	if (netif_xmit_stopped(netdev_get_tx_queue(dev, 0)) || !skb->xmit_more)
		mtk_w32(eth, txd->txd2, MTK_QTX_CTX_PTR);

	return 0;

err_dma:
	do {
		tx_buf = mtk_desc_to_tx_buf(ring, txd);

		/* unmap dma */
		mtk_txd_unmap(&dev->dev, tx_buf);

		itxd->txd3 = TX_DMA_DESP2_DEF;
		itxd = mtk_tx_next_qdma(ring, itxd);
	} while (itxd != txd);

	return -ENOMEM;
}