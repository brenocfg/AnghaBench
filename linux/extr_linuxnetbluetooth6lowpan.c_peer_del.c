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
struct lowpan_peer {int /*<<< orphan*/  list; } ;
struct lowpan_btle_dev {int /*<<< orphan*/  peer_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct lowpan_peer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 

__attribute__((used)) static inline bool peer_del(struct lowpan_btle_dev *dev,
			    struct lowpan_peer *peer)
{
	list_del_rcu(&peer->list);
	kfree_rcu(peer, rcu);

	module_put(THIS_MODULE);

	if (atomic_dec_and_test(&dev->peer_count)) {
		BT_DBG("last peer");
		return true;
	}

	return false;
}