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
struct sk_buff {int dummy; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_len; int /*<<< orphan*/  nlmsg_type; } ;
struct nlmsgerr {int /*<<< orphan*/  error; } ;
struct net {int dummy; } ;
struct mr_table {int /*<<< orphan*/  cache_resolve_queue_len; int /*<<< orphan*/  net; } ;
struct TYPE_6__ {int /*<<< orphan*/  unresolved; } ;
struct TYPE_7__ {TYPE_1__ unres; } ;
struct TYPE_8__ {TYPE_2__ mfc_un; } ;
struct mfc6_cache {TYPE_3__ _c; } ;
struct ipv6hdr {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  portid; } ;
struct TYPE_9__ {scalar_t__ version; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 TYPE_5__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLMSG_ERROR ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip6mr_cache_free (struct mfc6_cache*) ; 
 TYPE_4__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_msg_size (int) ; 
 struct net* read_pnet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_unicast (struct sk_buff*,struct net*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 struct nlmsghdr* skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ip6mr_destroy_unres(struct mr_table *mrt, struct mfc6_cache *c)
{
	struct net *net = read_pnet(&mrt->net);
	struct sk_buff *skb;

	atomic_dec(&mrt->cache_resolve_queue_len);

	while ((skb = skb_dequeue(&c->_c.mfc_un.unres.unresolved)) != NULL) {
		if (ipv6_hdr(skb)->version == 0) {
			struct nlmsghdr *nlh = skb_pull(skb,
							sizeof(struct ipv6hdr));
			nlh->nlmsg_type = NLMSG_ERROR;
			nlh->nlmsg_len = nlmsg_msg_size(sizeof(struct nlmsgerr));
			skb_trim(skb, nlh->nlmsg_len);
			((struct nlmsgerr *)nlmsg_data(nlh))->error = -ETIMEDOUT;
			rtnl_unicast(skb, net, NETLINK_CB(skb).portid);
		} else
			kfree_skb(skb);
	}

	ip6mr_cache_free(c);
}