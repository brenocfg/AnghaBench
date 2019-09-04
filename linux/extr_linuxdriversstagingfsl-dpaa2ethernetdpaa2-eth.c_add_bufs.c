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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct dpaa2_eth_priv {TYPE_2__* net_dev; int /*<<< orphan*/  rx_buf_align; } ;
struct dpaa2_eth_channel {int /*<<< orphan*/  dpio; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {struct device* parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int DPAA2_ETH_BUFS_PER_CMD ; 
 int /*<<< orphan*/  DPAA2_ETH_RX_BUF_SIZE ; 
 int EBUSY ; 
 void* PTR_ALIGN (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dma_map_single (struct device*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_eth_buf_raw_size (struct dpaa2_eth_priv*) ; 
 int dpaa2_io_service_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_bufs (struct dpaa2_eth_priv*,int /*<<< orphan*/ *,int) ; 
 void* napi_alloc_frag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_free_frag (void*) ; 
 int /*<<< orphan*/  trace_dpaa2_eth_buf_seed (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int add_bufs(struct dpaa2_eth_priv *priv,
		    struct dpaa2_eth_channel *ch, u16 bpid)
{
	struct device *dev = priv->net_dev->dev.parent;
	u64 buf_array[DPAA2_ETH_BUFS_PER_CMD];
	void *buf;
	dma_addr_t addr;
	int i, err;

	for (i = 0; i < DPAA2_ETH_BUFS_PER_CMD; i++) {
		/* Allocate buffer visible to WRIOP + skb shared info +
		 * alignment padding
		 */
		buf = napi_alloc_frag(dpaa2_eth_buf_raw_size(priv));
		if (unlikely(!buf))
			goto err_alloc;

		buf = PTR_ALIGN(buf, priv->rx_buf_align);

		addr = dma_map_single(dev, buf, DPAA2_ETH_RX_BUF_SIZE,
				      DMA_FROM_DEVICE);
		if (unlikely(dma_mapping_error(dev, addr)))
			goto err_map;

		buf_array[i] = addr;

		/* tracing point */
		trace_dpaa2_eth_buf_seed(priv->net_dev,
					 buf, dpaa2_eth_buf_raw_size(priv),
					 addr, DPAA2_ETH_RX_BUF_SIZE,
					 bpid);
	}

release_bufs:
	/* In case the portal is busy, retry until successful */
	while ((err = dpaa2_io_service_release(ch->dpio, bpid,
					       buf_array, i)) == -EBUSY)
		cpu_relax();

	/* If release command failed, clean up and bail out;
	 * not much else we can do about it
	 */
	if (err) {
		free_bufs(priv, buf_array, i);
		return 0;
	}

	return i;

err_map:
	skb_free_frag(buf);
err_alloc:
	/* If we managed to allocate at least some buffers,
	 * release them to hardware
	 */
	if (i)
		goto release_bufs;

	return 0;
}