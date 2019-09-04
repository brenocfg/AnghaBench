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
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ len; } ;
struct net_device {int hard_header_len; } ;
struct neighbour {struct net_device* dev; } ;
struct dn_skb_cb {int rt_flags; int hops; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct dn_long_packet {int msgflg; int visit_ct; scalar_t__ pt; scalar_t__ s_class; scalar_t__ nl2; int /*<<< orphan*/  s_id; scalar_t__ s_subarea; scalar_t__ s_area; int /*<<< orphan*/  d_id; scalar_t__ d_subarea; scalar_t__ d_area; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int DN_RT_F_IE ; 
 int DN_RT_F_PF ; 
 int DN_RT_F_RQR ; 
 int DN_RT_F_RTS ; 
 int DN_RT_PKT_LONG ; 
 struct dn_skb_cb* DN_SKB_CB (struct sk_buff*) ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  NFPROTO_DECNET ; 
 int /*<<< orphan*/  NF_DN_POST_ROUTING ; 
 int NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sock*,struct sk_buff*,int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  dn_dn2eth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_neigh_output_packet ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  net_crit_ratelimited (char*) ; 
 int /*<<< orphan*/  net_info_ratelimited (char*) ; 
 int skb_headroom (struct sk_buff*) ; 
 unsigned char* skb_push (struct sk_buff*,int) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

__attribute__((used)) static int dn_long_output(struct neighbour *neigh, struct sock *sk,
			  struct sk_buff *skb)
{
	struct net_device *dev = neigh->dev;
	int headroom = dev->hard_header_len + sizeof(struct dn_long_packet) + 3;
	unsigned char *data;
	struct dn_long_packet *lp;
	struct dn_skb_cb *cb = DN_SKB_CB(skb);


	if (skb_headroom(skb) < headroom) {
		struct sk_buff *skb2 = skb_realloc_headroom(skb, headroom);
		if (skb2 == NULL) {
			net_crit_ratelimited("dn_long_output: no memory\n");
			kfree_skb(skb);
			return -ENOBUFS;
		}
		consume_skb(skb);
		skb = skb2;
		net_info_ratelimited("dn_long_output: Increasing headroom\n");
	}

	data = skb_push(skb, sizeof(struct dn_long_packet) + 3);
	lp = (struct dn_long_packet *)(data+3);

	*((__le16 *)data) = cpu_to_le16(skb->len - 2);
	*(data + 2) = 1 | DN_RT_F_PF; /* Padding */

	lp->msgflg   = DN_RT_PKT_LONG|(cb->rt_flags&(DN_RT_F_IE|DN_RT_F_RQR|DN_RT_F_RTS));
	lp->d_area   = lp->d_subarea = 0;
	dn_dn2eth(lp->d_id, cb->dst);
	lp->s_area   = lp->s_subarea = 0;
	dn_dn2eth(lp->s_id, cb->src);
	lp->nl2      = 0;
	lp->visit_ct = cb->hops & 0x3f;
	lp->s_class  = 0;
	lp->pt       = 0;

	skb_reset_network_header(skb);

	return NF_HOOK(NFPROTO_DECNET, NF_DN_POST_ROUTING,
		       &init_net, sk, skb, NULL, neigh->dev,
		       dn_neigh_output_packet);
}