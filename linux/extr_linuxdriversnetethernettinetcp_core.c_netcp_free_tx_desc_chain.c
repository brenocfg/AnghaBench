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
struct netcp_intf {int /*<<< orphan*/  ndev_dev; int /*<<< orphan*/  tx_pool; int /*<<< orphan*/  dev; } ;
struct knav_dma_desc {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__*,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pkt_info (scalar_t__*,unsigned int*,scalar_t__*,struct knav_dma_desc*) ; 
 int /*<<< orphan*/  knav_pool_desc_put (int /*<<< orphan*/ ,struct knav_dma_desc*) ; 
 struct knav_dma_desc* knav_pool_desc_unmap (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 

__attribute__((used)) static void netcp_free_tx_desc_chain(struct netcp_intf *netcp,
				     struct knav_dma_desc *desc,
				     unsigned int desc_sz)
{
	struct knav_dma_desc *ndesc = desc;
	dma_addr_t dma_desc, dma_buf;
	unsigned int buf_len;

	while (ndesc) {
		get_pkt_info(&dma_buf, &buf_len, &dma_desc, ndesc);

		if (dma_buf && buf_len)
			dma_unmap_single(netcp->dev, dma_buf, buf_len,
					 DMA_TO_DEVICE);
		else
			dev_warn(netcp->ndev_dev, "bad Tx desc buf(%pad), len(%d)\n",
				 &dma_buf, buf_len);

		knav_pool_desc_put(netcp->tx_pool, ndesc);
		ndesc = NULL;
		if (dma_desc) {
			ndesc = knav_pool_desc_unmap(netcp->tx_pool, dma_desc,
						     desc_sz);
			if (!ndesc)
				dev_err(netcp->ndev_dev, "failed to unmap Tx desc\n");
		}
	}
}