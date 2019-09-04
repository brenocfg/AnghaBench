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
typedef  void sk_buff ;
struct rtl8169_private {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
struct RxDesc {int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ R8169_RX_BUF_SIZE ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int dev_to_node (struct device*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc_node (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netif_err (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 void* rtl8169_align (void*) ; 
 int /*<<< orphan*/  rtl8169_mark_to_asic (struct RxDesc*) ; 
 struct device* tp_to_dev (struct rtl8169_private*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *rtl8169_alloc_rx_data(struct rtl8169_private *tp,
					     struct RxDesc *desc)
{
	void *data;
	dma_addr_t mapping;
	struct device *d = tp_to_dev(tp);
	int node = dev_to_node(d);

	data = kmalloc_node(R8169_RX_BUF_SIZE, GFP_KERNEL, node);
	if (!data)
		return NULL;

	if (rtl8169_align(data) != data) {
		kfree(data);
		data = kmalloc_node(R8169_RX_BUF_SIZE + 15, GFP_KERNEL, node);
		if (!data)
			return NULL;
	}

	mapping = dma_map_single(d, rtl8169_align(data), R8169_RX_BUF_SIZE,
				 DMA_FROM_DEVICE);
	if (unlikely(dma_mapping_error(d, mapping))) {
		if (net_ratelimit())
			netif_err(tp, drv, tp->dev, "Failed to map RX DMA!\n");
		goto err_out;
	}

	desc->addr = cpu_to_le64(mapping);
	rtl8169_mark_to_asic(desc);
	return data;

err_out:
	kfree(data);
	return NULL;
}