#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  locator_match; } ;
struct ila_xlat_params {TYPE_1__ ip; } ;
struct TYPE_4__ {int /*<<< orphan*/  rhash_table; } ;
struct ila_net {TYPE_2__ xlat; } ;
struct ila_map {int /*<<< orphan*/  node; int /*<<< orphan*/  next; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ ila_cmp_params (struct ila_map*,struct ila_xlat_params*) ; 
 int /*<<< orphan*/ * ila_get_lock (struct ila_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ila_net_id ; 
 int /*<<< orphan*/  ila_release (struct ila_map*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct ila_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ila_map* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ila_map* rhashtable_lookup_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rhashtable_replace_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rht_params ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ila_del_mapping(struct net *net, struct ila_xlat_params *xp)
{
	struct ila_net *ilan = net_generic(net, ila_net_id);
	struct ila_map *ila, *head, *prev;
	spinlock_t *lock = ila_get_lock(ilan, xp->ip.locator_match);
	int err = -ENOENT;

	spin_lock(lock);

	head = rhashtable_lookup_fast(&ilan->xlat.rhash_table,
				      &xp->ip.locator_match, rht_params);
	ila = head;

	prev = NULL;

	while (ila) {
		if (ila_cmp_params(ila, xp)) {
			prev = ila;
			ila = rcu_dereference_protected(ila->next,
							lockdep_is_held(lock));
			continue;
		}

		err = 0;

		if (prev) {
			/* Not head, just delete from list */
			rcu_assign_pointer(prev->next, ila->next);
		} else {
			/* It is the head. If there is something in the
			 * sublist we need to make a new head.
			 */
			head = rcu_dereference_protected(ila->next,
							 lockdep_is_held(lock));
			if (head) {
				/* Put first entry in the sublist into the
				 * table
				 */
				err = rhashtable_replace_fast(
					&ilan->xlat.rhash_table, &ila->node,
					&head->node, rht_params);
				if (err)
					goto out;
			} else {
				/* Entry no longer used */
				err = rhashtable_remove_fast(
						&ilan->xlat.rhash_table,
						&ila->node, rht_params);
			}
		}

		ila_release(ila);

		break;
	}

out:
	spin_unlock(lock);

	return err;
}