#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xdp_frame {scalar_t__ len; } ;
struct sk_buff {scalar_t__ len; } ;
struct TYPE_2__ {unsigned int bytes; unsigned int packets; int /*<<< orphan*/  syncp; } ;
struct send_queue {TYPE_1__ stats; int /*<<< orphan*/  vq; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_xdp_frame (void*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  napi_consume_skb (struct sk_buff*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,struct sk_buff*) ; 
 struct xdp_frame* ptr_to_xdp (void*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 void* virtqueue_get_buf (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  xdp_return_frame (struct xdp_frame*) ; 

__attribute__((used)) static void free_old_xmit_skbs(struct send_queue *sq, bool in_napi)
{
	unsigned int len;
	unsigned int packets = 0;
	unsigned int bytes = 0;
	void *ptr;

	while ((ptr = virtqueue_get_buf(sq->vq, &len)) != NULL) {
		if (likely(!is_xdp_frame(ptr))) {
			struct sk_buff *skb = ptr;

			pr_debug("Sent skb %p\n", skb);

			bytes += skb->len;
			napi_consume_skb(skb, in_napi);
		} else {
			struct xdp_frame *frame = ptr_to_xdp(ptr);

			bytes += frame->len;
			xdp_return_frame(frame);
		}
		packets++;
	}

	/* Avoid overhead when no packets have been processed
	 * happens when called speculatively from start_xmit.
	 */
	if (!packets)
		return;

	u64_stats_update_begin(&sq->stats.syncp);
	sq->stats.bytes += bytes;
	sq->stats.packets += packets;
	u64_stats_update_end(&sq->stats.syncp);
}