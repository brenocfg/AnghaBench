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
struct sk_buff {int dummy; } ;
struct rtl8169_private {int /*<<< orphan*/  napi; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct sk_buff* napi_alloc_skb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  prefetch (void*) ; 
 void* rtl8169_align (void*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,void*,int) ; 
 struct device* tp_to_dev (struct rtl8169_private*) ; 

__attribute__((used)) static struct sk_buff *rtl8169_try_rx_copy(void *data,
					   struct rtl8169_private *tp,
					   int pkt_size,
					   dma_addr_t addr)
{
	struct sk_buff *skb;
	struct device *d = tp_to_dev(tp);

	data = rtl8169_align(data);
	dma_sync_single_for_cpu(d, addr, pkt_size, DMA_FROM_DEVICE);
	prefetch(data);
	skb = napi_alloc_skb(&tp->napi, pkt_size);
	if (skb)
		skb_copy_to_linear_data(skb, data, pkt_size);
	dma_sync_single_for_device(d, addr, pkt_size, DMA_FROM_DEVICE);

	return skb;
}