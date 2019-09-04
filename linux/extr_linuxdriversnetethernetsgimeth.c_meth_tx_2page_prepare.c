#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* cat_buf; scalar_t__ dt; } ;
struct TYPE_6__ {int raw; } ;
struct TYPE_10__ {TYPE_4__ data; TYPE_1__ header; } ;
typedef  TYPE_5__ tx_packet ;
struct sk_buff {int len; scalar_t__ data; } ;
struct meth_private {size_t tx_write; TYPE_5__* tx_ring; } ;
typedef  int dma_addr_t ;
struct TYPE_7__ {int start_addr; int len; } ;
struct TYPE_8__ {TYPE_2__ form; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int METH_TX_CMD_INT_EN ; 
 scalar_t__ PAGE_ALIGN (unsigned long) ; 
 int TX_CATBUF1 ; 
 int TX_CATBUF2 ; 
 int dma_map_single (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,scalar_t__,int) ; 

__attribute__((used)) static void meth_tx_2page_prepare(struct meth_private *priv,
				  struct sk_buff *skb)
{
	tx_packet *desc = &priv->tx_ring[priv->tx_write];
	void *buffer1_data = (void *)(((unsigned long)skb->data + 7) & ~7);
	void *buffer2_data = (void *)PAGE_ALIGN((unsigned long)skb->data);
	int unaligned_len = (int)((unsigned long)buffer1_data - (unsigned long)skb->data);
	int buffer1_len = (int)((unsigned long)buffer2_data - (unsigned long)buffer1_data);
	int buffer2_len = skb->len - buffer1_len - unaligned_len;
	dma_addr_t catbuf1, catbuf2;

	desc->header.raw = METH_TX_CMD_INT_EN | TX_CATBUF1 | TX_CATBUF2| (skb->len - 1);
	/* unaligned part */
	if (unaligned_len){
		skb_copy_from_linear_data(skb, desc->data.dt + (120 - unaligned_len),
			      unaligned_len);
		desc->header.raw |= (128 - unaligned_len) << 16;
	}

	/* first page */
	catbuf1 = dma_map_single(NULL, buffer1_data, buffer1_len,
				 DMA_TO_DEVICE);
	desc->data.cat_buf[0].form.start_addr = catbuf1 >> 3;
	desc->data.cat_buf[0].form.len = buffer1_len - 1;
	/* second page */
	catbuf2 = dma_map_single(NULL, buffer2_data, buffer2_len,
				 DMA_TO_DEVICE);
	desc->data.cat_buf[1].form.start_addr = catbuf2 >> 3;
	desc->data.cat_buf[1].form.len = buffer2_len - 1;
}