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
struct sk_buff {unsigned char* data; int /*<<< orphan*/  pkt_type; } ;
struct dn_skb_cb {int rt_flags; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int DN_RT_F_RQR ; 
 int DN_RT_F_RTS ; 
 struct dn_skb_cb* DN_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 int /*<<< orphan*/  PACKET_OUTGOING ; 
 int /*<<< orphan*/  dn_rt_finish_output (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,unsigned char*) ; 
 struct sk_buff* skb_unshare (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dn_return_short(struct sk_buff *skb)
{
	struct dn_skb_cb *cb;
	unsigned char *ptr;
	__le16 *src;
	__le16 *dst;

	/* Add back headers */
	skb_push(skb, skb->data - skb_network_header(skb));

	if ((skb = skb_unshare(skb, GFP_ATOMIC)) == NULL)
		return NET_RX_DROP;

	cb = DN_SKB_CB(skb);
	/* Skip packet length and point to flags */
	ptr = skb->data + 2;
	*ptr++ = (cb->rt_flags & ~DN_RT_F_RQR) | DN_RT_F_RTS;

	dst = (__le16 *)ptr;
	ptr += 2;
	src = (__le16 *)ptr;
	ptr += 2;
	*ptr = 0; /* Zero hop count */

	swap(*src, *dst);

	skb->pkt_type = PACKET_OUTGOING;
	dn_rt_finish_output(skb, NULL, NULL);
	return NET_RX_SUCCESS;
}