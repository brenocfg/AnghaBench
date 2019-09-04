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
struct virtnet_info {int dummy; } ;
struct skb_shared_info {int dummy; } ;
struct page_frag {int offset; unsigned int size; int /*<<< orphan*/  page; } ;
struct receive_queue {int /*<<< orphan*/  sg; int /*<<< orphan*/  vq; int /*<<< orphan*/  mrg_avg_pkt_len; struct page_frag alloc_frag; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int SKB_DATA_ALIGN (unsigned int) ; 
 unsigned int get_mergeable_buf_len (struct receive_queue*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 void* mergeable_len_to_ctx (unsigned int,unsigned int) ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  skb_page_frag_refill (unsigned int,struct page_frag*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  virt_to_head_page (char*) ; 
 unsigned int virtnet_get_headroom (struct virtnet_info*) ; 
 int virtqueue_add_inbuf_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_recvbuf_mergeable(struct virtnet_info *vi,
				 struct receive_queue *rq, gfp_t gfp)
{
	struct page_frag *alloc_frag = &rq->alloc_frag;
	unsigned int headroom = virtnet_get_headroom(vi);
	unsigned int tailroom = headroom ? sizeof(struct skb_shared_info) : 0;
	unsigned int room = SKB_DATA_ALIGN(headroom + tailroom);
	char *buf;
	void *ctx;
	int err;
	unsigned int len, hole;

	/* Extra tailroom is needed to satisfy XDP's assumption. This
	 * means rx frags coalescing won't work, but consider we've
	 * disabled GSO for XDP, it won't be a big issue.
	 */
	len = get_mergeable_buf_len(rq, &rq->mrg_avg_pkt_len, room);
	if (unlikely(!skb_page_frag_refill(len + room, alloc_frag, gfp)))
		return -ENOMEM;

	buf = (char *)page_address(alloc_frag->page) + alloc_frag->offset;
	buf += headroom; /* advance address leaving hole at front of pkt */
	get_page(alloc_frag->page);
	alloc_frag->offset += len + room;
	hole = alloc_frag->size - alloc_frag->offset;
	if (hole < len + room) {
		/* To avoid internal fragmentation, if there is very likely not
		 * enough space for another buffer, add the remaining space to
		 * the current buffer.
		 */
		len += hole;
		alloc_frag->offset += hole;
	}

	sg_init_one(rq->sg, buf, len);
	ctx = mergeable_len_to_ctx(len, headroom);
	err = virtqueue_add_inbuf_ctx(rq->vq, rq->sg, 1, buf, ctx, gfp);
	if (err < 0)
		put_page(virt_to_head_page(buf));

	return err;
}