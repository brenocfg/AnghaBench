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
typedef  int /*<<< orphan*/  u32 ;
struct netcp_intf {int /*<<< orphan*/  rx_pool; int /*<<< orphan*/  dev; int /*<<< orphan*/  ndev_dev; } ;
struct knav_dma_desc {int /*<<< orphan*/  next_desc; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ GET_SW_DATA0 (struct knav_dma_desc*) ; 
 scalar_t__ GET_SW_DATA1 (struct knav_dma_desc*) ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  __free_page (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pkt_info (scalar_t__*,int /*<<< orphan*/ *,scalar_t__*,struct knav_dma_desc*) ; 
 int /*<<< orphan*/  get_words (scalar_t__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  knav_pool_desc_put (int /*<<< orphan*/ ,struct knav_dma_desc*) ; 
 struct knav_dma_desc* knav_pool_desc_unmap (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  netcp_frag_free (int,void*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void netcp_free_rx_desc_chain(struct netcp_intf *netcp,
				     struct knav_dma_desc *desc)
{
	struct knav_dma_desc *ndesc;
	dma_addr_t dma_desc, dma_buf;
	unsigned int buf_len, dma_sz = sizeof(*ndesc);
	void *buf_ptr;
	u32 tmp;

	get_words(&dma_desc, 1, &desc->next_desc);

	while (dma_desc) {
		ndesc = knav_pool_desc_unmap(netcp->rx_pool, dma_desc, dma_sz);
		if (unlikely(!ndesc)) {
			dev_err(netcp->ndev_dev, "failed to unmap Rx desc\n");
			break;
		}
		get_pkt_info(&dma_buf, &tmp, &dma_desc, ndesc);
		/* warning!!!! We are retrieving the virtual ptr in the sw_data
		 * field as a 32bit value. Will not work on 64bit machines
		 */
		buf_ptr = (void *)GET_SW_DATA0(ndesc);
		buf_len = (int)GET_SW_DATA1(desc);
		dma_unmap_page(netcp->dev, dma_buf, PAGE_SIZE, DMA_FROM_DEVICE);
		__free_page(buf_ptr);
		knav_pool_desc_put(netcp->rx_pool, desc);
	}
	/* warning!!!! We are retrieving the virtual ptr in the sw_data
	 * field as a 32bit value. Will not work on 64bit machines
	 */
	buf_ptr = (void *)GET_SW_DATA0(desc);
	buf_len = (int)GET_SW_DATA1(desc);

	if (buf_ptr)
		netcp_frag_free(buf_len <= PAGE_SIZE, buf_ptr);
	knav_pool_desc_put(netcp->rx_pool, desc);
}