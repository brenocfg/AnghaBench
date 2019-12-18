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
struct net {int /*<<< orphan*/  netns_ids; } ;

/* Variables and functions */
 struct net* idr_find (int /*<<< orphan*/ *,int) ; 
 struct net* maybe_get_net (struct net*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct net *get_net_ns_by_id(struct net *net, int id)
{
	struct net *peer;

	if (id < 0)
		return NULL;

	rcu_read_lock();
	peer = idr_find(&net->netns_ids, id);
	if (peer)
		peer = maybe_get_net(peer);
	rcu_read_unlock();

	return peer;
}