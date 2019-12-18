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
struct net {int /*<<< orphan*/  nsid_lock; int /*<<< orphan*/  count; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int NETNSA_NSID_NOT_ASSIGNED ; 
 int /*<<< orphan*/  RTM_NEWNSID ; 
 int __peernet2id_alloc (struct net*,struct net*,int*) ; 
 scalar_t__ maybe_get_net (struct net*) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 
 scalar_t__ refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_net_notifyid (struct net*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int peernet2id_alloc(struct net *net, struct net *peer, gfp_t gfp)
{
	bool alloc = false, alive = false;
	int id;

	if (refcount_read(&net->count) == 0)
		return NETNSA_NSID_NOT_ASSIGNED;
	spin_lock_bh(&net->nsid_lock);
	/*
	 * When peer is obtained from RCU lists, we may race with
	 * its cleanup. Check whether it's alive, and this guarantees
	 * we never hash a peer back to net->netns_ids, after it has
	 * just been idr_remove()'d from there in cleanup_net().
	 */
	if (maybe_get_net(peer))
		alive = alloc = true;
	id = __peernet2id_alloc(net, peer, &alloc);
	spin_unlock_bh(&net->nsid_lock);
	if (alloc && id >= 0)
		rtnl_net_notifyid(net, RTM_NEWNSID, id, 0, NULL, gfp);
	if (alive)
		put_net(peer);
	return id;
}