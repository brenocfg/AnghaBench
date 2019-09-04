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
struct TYPE_6__ {void* req_count; } ;
struct TYPE_5__ {int /*<<< orphan*/  owner; void* res_count; } ;
struct vnt_rx_desc {int /*<<< orphan*/  buff_addr; TYPE_3__ rd1; TYPE_2__ rd0; struct vnt_rd_info* rd_info; } ;
struct vnt_rd_info {int /*<<< orphan*/  skb_dma; int /*<<< orphan*/ * skb; } ;
struct vnt_private {scalar_t__ rx_buf_sz; TYPE_1__* pcid; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  OWNED_BY_NIC ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tailroom (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool device_alloc_rx_buf(struct vnt_private *priv,
				struct vnt_rx_desc *rd)
{
	struct vnt_rd_info *rd_info = rd->rd_info;

	rd_info->skb = dev_alloc_skb((int)priv->rx_buf_sz);
	if (!rd_info->skb)
		return false;

	rd_info->skb_dma =
		dma_map_single(&priv->pcid->dev,
			       skb_put(rd_info->skb, skb_tailroom(rd_info->skb)),
			       priv->rx_buf_sz, DMA_FROM_DEVICE);
	if (dma_mapping_error(&priv->pcid->dev, rd_info->skb_dma)) {
		dev_kfree_skb(rd_info->skb);
		rd_info->skb = NULL;
		return false;
	}

	*((unsigned int *)&rd->rd0) = 0; /* FIX cast */

	rd->rd0.res_count = cpu_to_le16(priv->rx_buf_sz);
	rd->rd0.owner = OWNED_BY_NIC;
	rd->rd1.req_count = cpu_to_le16(priv->rx_buf_sz);
	rd->buff_addr = cpu_to_le32(rd_info->skb_dma);

	return true;
}