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
struct sk_buff {scalar_t__ data_len; int /*<<< orphan*/  len; struct net_device* dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RCVPOST_BUF_SIZE ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *alloc_rcv_buf(struct net_device *netdev)
{
	struct sk_buff *skb;

	/* NOTE: the first fragment in each rcv buffer is pointed to by
	 * rcvskb->data. For now all rcv buffers will be RCVPOST_BUF_SIZE
	 * in length, so the first frag is large enough to hold 1514.
	 */
	skb = alloc_skb(RCVPOST_BUF_SIZE, GFP_ATOMIC);
	if (!skb)
		return NULL;
	skb->dev = netdev;
	/* current value of mtu doesn't come into play here; large
	 * packets will just end up using multiple rcv buffers all of
	 * same size.
	 */
	skb->len = RCVPOST_BUF_SIZE;
	/* alloc_skb already zeroes it out for clarification. */
	skb->data_len = 0;
	return skb;
}