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
struct virtnet_info {unsigned int hdr_len; } ;
struct skb_shared_info {int dummy; } ;
struct page_frag {int offset; int /*<<< orphan*/  page; } ;
struct receive_queue {int /*<<< orphan*/  sg; int /*<<< orphan*/  vq; struct page_frag alloc_frag; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int GOOD_PACKET_LEN ; 
 int SKB_DATA_ALIGN (int) ; 
 int VIRTNET_RX_PAD ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  skb_page_frag_refill (int,struct page_frag*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  virt_to_head_page (char*) ; 
 unsigned int virtnet_get_headroom (struct virtnet_info*) ; 
 int virtqueue_add_inbuf_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_recvbuf_small(struct virtnet_info *vi, struct receive_queue *rq,
			     gfp_t gfp)
{
	struct page_frag *alloc_frag = &rq->alloc_frag;
	char *buf;
	unsigned int xdp_headroom = virtnet_get_headroom(vi);
	void *ctx = (void *)(unsigned long)xdp_headroom;
	int len = vi->hdr_len + VIRTNET_RX_PAD + GOOD_PACKET_LEN + xdp_headroom;
	int err;

	len = SKB_DATA_ALIGN(len) +
	      SKB_DATA_ALIGN(sizeof(struct skb_shared_info));
	if (unlikely(!skb_page_frag_refill(len, alloc_frag, gfp)))
		return -ENOMEM;

	buf = (char *)page_address(alloc_frag->page) + alloc_frag->offset;
	get_page(alloc_frag->page);
	alloc_frag->offset += len;
	sg_init_one(rq->sg, buf + VIRTNET_RX_PAD + xdp_headroom,
		    vi->hdr_len + GOOD_PACKET_LEN);
	err = virtqueue_add_inbuf_ctx(rq->vq, rq->sg, 1, buf, ctx, gfp);
	if (err < 0)
		put_page(virt_to_head_page(buf));
	return err;
}