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
 int NETNSA_NSID_NOT_ASSIGNED ; 
 int NET_ID_ZERO ; 
 int alloc_netid (struct net*,struct net*,int) ; 
 int idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct net*) ; 
 int /*<<< orphan*/  net_eq_idr ; 

__attribute__((used)) static int __peernet2id_alloc(struct net *net, struct net *peer, bool *alloc)
{
	int id = idr_for_each(&net->netns_ids, net_eq_idr, peer);
	bool alloc_it = *alloc;

	*alloc = false;

	/* Magic value for id 0. */
	if (id == NET_ID_ZERO)
		return 0;
	if (id > 0)
		return id;

	if (alloc_it) {
		id = alloc_netid(net, peer, -1);
		*alloc = true;
		return id >= 0 ? id : NETNSA_NSID_NOT_ASSIGNED;
	}

	return NETNSA_NSID_NOT_ASSIGNED;
}