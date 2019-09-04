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
typedef  unsigned int u32 ;
struct skb_shared_info {int dummy; } ;
struct page {int dummy; } ;
struct netcp_intf {unsigned int rx_queue_id; int /*<<< orphan*/  rx_pool; int /*<<< orphan*/ * rx_fdq; int /*<<< orphan*/  dev; int /*<<< orphan*/  ndev_dev; } ;
struct knav_dma_desc {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int GFP_ATOMIC ; 
 int GFP_DMA ; 
 scalar_t__ IS_ERR_OR_NULL (struct knav_dma_desc*) ; 
 unsigned int KNAV_DMA_DESC_HAS_EPIB ; 
 unsigned int KNAV_DMA_DESC_PKT_LEN_MASK ; 
 unsigned int KNAV_DMA_DESC_PSLEN_SHIFT ; 
 unsigned int KNAV_DMA_DESC_PS_INFO_IN_DESC ; 
 unsigned int KNAV_DMA_DESC_RETQ_MASK ; 
 unsigned int KNAV_DMA_DESC_RETQ_SHIFT ; 
 unsigned int KNAV_DMA_NUM_PS_WORDS ; 
 unsigned int NETCP_PACKET_SIZE ; 
 unsigned int NETCP_SOP_OFFSET ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  SET_SW_DATA0 (unsigned int,struct knav_dma_desc*) ; 
 int /*<<< orphan*/  SET_SW_DATA1 (unsigned int,struct knav_dma_desc*) ; 
 unsigned int SKB_DATA_ALIGN (int) ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct knav_dma_desc* knav_pool_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knav_pool_desc_map (int /*<<< orphan*/ ,struct knav_dma_desc*,int,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  knav_pool_desc_put (int /*<<< orphan*/ ,struct knav_dma_desc*) ; 
 int /*<<< orphan*/  knav_queue_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 void* netdev_alloc_frag (unsigned int) ; 
 int /*<<< orphan*/  set_desc_info (unsigned int,unsigned int,struct knav_dma_desc*) ; 
 int /*<<< orphan*/  set_org_pkt_info (int /*<<< orphan*/ ,unsigned int,struct knav_dma_desc*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int netcp_allocate_rx_buf(struct netcp_intf *netcp, int fdq)
{
	struct knav_dma_desc *hwdesc;
	unsigned int buf_len, dma_sz;
	u32 desc_info, pkt_info;
	struct page *page;
	dma_addr_t dma;
	void *bufptr;
	u32 sw_data[2];

	/* Allocate descriptor */
	hwdesc = knav_pool_desc_get(netcp->rx_pool);
	if (IS_ERR_OR_NULL(hwdesc)) {
		dev_dbg(netcp->ndev_dev, "out of rx pool desc\n");
		return -ENOMEM;
	}

	if (likely(fdq == 0)) {
		unsigned int primary_buf_len;
		/* Allocate a primary receive queue entry */
		buf_len = NETCP_PACKET_SIZE + NETCP_SOP_OFFSET;
		primary_buf_len = SKB_DATA_ALIGN(buf_len) +
				SKB_DATA_ALIGN(sizeof(struct skb_shared_info));

		bufptr = netdev_alloc_frag(primary_buf_len);
		sw_data[1] = primary_buf_len;

		if (unlikely(!bufptr)) {
			dev_warn_ratelimited(netcp->ndev_dev,
					     "Primary RX buffer alloc failed\n");
			goto fail;
		}
		dma = dma_map_single(netcp->dev, bufptr, buf_len,
				     DMA_TO_DEVICE);
		if (unlikely(dma_mapping_error(netcp->dev, dma)))
			goto fail;

		/* warning!!!! We are saving the virtual ptr in the sw_data
		 * field as a 32bit value. Will not work on 64bit machines
		 */
		sw_data[0] = (u32)bufptr;
	} else {
		/* Allocate a secondary receive queue entry */
		page = alloc_page(GFP_ATOMIC | GFP_DMA);
		if (unlikely(!page)) {
			dev_warn_ratelimited(netcp->ndev_dev, "Secondary page alloc failed\n");
			goto fail;
		}
		buf_len = PAGE_SIZE;
		dma = dma_map_page(netcp->dev, page, 0, buf_len, DMA_TO_DEVICE);
		/* warning!!!! We are saving the virtual ptr in the sw_data
		 * field as a 32bit value. Will not work on 64bit machines
		 */
		sw_data[0] = (u32)page;
		sw_data[1] = 0;
	}

	desc_info =  KNAV_DMA_DESC_PS_INFO_IN_DESC;
	desc_info |= buf_len & KNAV_DMA_DESC_PKT_LEN_MASK;
	pkt_info =  KNAV_DMA_DESC_HAS_EPIB;
	pkt_info |= KNAV_DMA_NUM_PS_WORDS << KNAV_DMA_DESC_PSLEN_SHIFT;
	pkt_info |= (netcp->rx_queue_id & KNAV_DMA_DESC_RETQ_MASK) <<
		    KNAV_DMA_DESC_RETQ_SHIFT;
	set_org_pkt_info(dma, buf_len, hwdesc);
	SET_SW_DATA0(sw_data[0], hwdesc);
	SET_SW_DATA1(sw_data[1], hwdesc);
	set_desc_info(desc_info, pkt_info, hwdesc);

	/* Push to FDQs */
	knav_pool_desc_map(netcp->rx_pool, hwdesc, sizeof(*hwdesc), &dma,
			   &dma_sz);
	knav_queue_push(netcp->rx_fdq[fdq], dma, sizeof(*hwdesc), 0);
	return 0;

fail:
	knav_pool_desc_put(netcp->rx_pool, hwdesc);
	return -ENOMEM;
}