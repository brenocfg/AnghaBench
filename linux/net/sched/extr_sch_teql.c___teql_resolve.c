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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct neighbour {int /*<<< orphan*/  primary_key; int /*<<< orphan*/  tbl; } ;
struct dst_entry {struct net_device* dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct neighbour*) ; 
 int MAX_ADDR_LEN ; 
 int PTR_ERR (struct neighbour*) ; 
 struct neighbour* __neigh_lookup_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int dev_hard_header (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct neighbour* dst_neigh_lookup_skb (struct dst_entry*,struct sk_buff*) ; 
 scalar_t__ neigh_event_send (struct neighbour*,struct sk_buff*) ; 
 int /*<<< orphan*/  neigh_ha_snapshot (char*,struct neighbour*,struct net_device*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_skb_protocol (struct sk_buff*) ; 

__attribute__((used)) static int
__teql_resolve(struct sk_buff *skb, struct sk_buff *skb_res,
	       struct net_device *dev, struct netdev_queue *txq,
	       struct dst_entry *dst)
{
	struct neighbour *n;
	int err = 0;

	n = dst_neigh_lookup_skb(dst, skb);
	if (!n)
		return -ENOENT;

	if (dst->dev != dev) {
		struct neighbour *mn;

		mn = __neigh_lookup_errno(n->tbl, n->primary_key, dev);
		neigh_release(n);
		if (IS_ERR(mn))
			return PTR_ERR(mn);
		n = mn;
	}

	if (neigh_event_send(n, skb_res) == 0) {
		int err;
		char haddr[MAX_ADDR_LEN];

		neigh_ha_snapshot(haddr, n, dev);
		err = dev_hard_header(skb, dev, ntohs(tc_skb_protocol(skb)),
				      haddr, NULL, skb->len);

		if (err < 0)
			err = -EINVAL;
	} else {
		err = (skb_res == NULL) ? -EAGAIN : 1;
	}
	neigh_release(n);
	return err;
}