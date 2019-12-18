#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nf_conntrack_zone {int dummy; } ;
struct nf_conntrack_tuple_hash {int dummy; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  use; } ;
struct nf_conn {TYPE_1__ ct_general; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct nf_conntrack_tuple_hash* ____nf_conntrack_find (struct net*,struct nf_conntrack_zone const*,struct nf_conntrack_tuple const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_key_equal (struct nf_conntrack_tuple_hash*,struct nf_conntrack_tuple const*,struct nf_conntrack_zone const*,struct net*) ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conn*) ; 
 struct nf_conn* nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static struct nf_conntrack_tuple_hash *
__nf_conntrack_find_get(struct net *net, const struct nf_conntrack_zone *zone,
			const struct nf_conntrack_tuple *tuple, u32 hash)
{
	struct nf_conntrack_tuple_hash *h;
	struct nf_conn *ct;

	rcu_read_lock();

	h = ____nf_conntrack_find(net, zone, tuple, hash);
	if (h) {
		/* We have a candidate that matches the tuple we're interested
		 * in, try to obtain a reference and re-check tuple
		 */
		ct = nf_ct_tuplehash_to_ctrack(h);
		if (likely(atomic_inc_not_zero(&ct->ct_general.use))) {
			if (likely(nf_ct_key_equal(h, tuple, zone, net)))
				goto found;

			/* TYPESAFE_BY_RCU recycled the candidate */
			nf_ct_put(ct);
		}

		h = NULL;
	}
found:
	rcu_read_unlock();

	return h;
}