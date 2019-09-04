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
struct wcn36xx_dxe_desc {int /*<<< orphan*/  dst_addr_l; } ;
struct wcn36xx_dxe_ctl {struct sk_buff* skb; struct wcn36xx_dxe_desc* desc; } ;
struct sk_buff {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  WCN36XX_PKT_SIZE ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tail_pointer (struct sk_buff*) ; 

__attribute__((used)) static int wcn36xx_dxe_fill_skb(struct device *dev,
				struct wcn36xx_dxe_ctl *ctl,
				gfp_t gfp)
{
	struct wcn36xx_dxe_desc *dxe = ctl->desc;
	struct sk_buff *skb;

	skb = alloc_skb(WCN36XX_PKT_SIZE, gfp);
	if (skb == NULL)
		return -ENOMEM;

	dxe->dst_addr_l = dma_map_single(dev,
					 skb_tail_pointer(skb),
					 WCN36XX_PKT_SIZE,
					 DMA_FROM_DEVICE);
	if (dma_mapping_error(dev, dxe->dst_addr_l)) {
		dev_err(dev, "unable to map skb\n");
		kfree_skb(skb);
		return -ENOMEM;
	}
	ctl->skb = skb;

	return 0;
}