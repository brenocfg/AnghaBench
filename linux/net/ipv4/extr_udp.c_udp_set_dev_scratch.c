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
struct udp_dev_scratch {int csum_unnecessary; int is_linear; int /*<<< orphan*/  _tsize_state; int /*<<< orphan*/  len; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  truesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  UDP_SKB_IS_STATELESS ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  skb_csum_unnecessary (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_nonlinear (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_sec_path (struct sk_buff*) ; 
 struct udp_dev_scratch* udp_skb_scratch (struct sk_buff*) ; 

__attribute__((used)) static void udp_set_dev_scratch(struct sk_buff *skb)
{
	struct udp_dev_scratch *scratch = udp_skb_scratch(skb);

	BUILD_BUG_ON(sizeof(struct udp_dev_scratch) > sizeof(long));
	scratch->_tsize_state = skb->truesize;
#if BITS_PER_LONG == 64
	scratch->len = skb->len;
	scratch->csum_unnecessary = !!skb_csum_unnecessary(skb);
	scratch->is_linear = !skb_is_nonlinear(skb);
#endif
	/* all head states execept sp (dst, sk, nf) are always cleared by
	 * udp_rcv() and we need to preserve secpath, if present, to eventually
	 * process IP_CMSG_PASSSEC at recvmsg() time
	 */
	if (likely(!skb_sec_path(skb)))
		scratch->_tsize_state |= UDP_SKB_IS_STATELESS;
}