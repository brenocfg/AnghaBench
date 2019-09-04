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
struct TYPE_4__ {int /*<<< orphan*/  locator_match; } ;
struct ila_xlat_params {TYPE_2__ ip; } ;
struct TYPE_3__ {int hooks_registered; int /*<<< orphan*/  rhash_table; } ;
struct ila_net {TYPE_1__ xlat; } ;
struct ila_map {int /*<<< orphan*/  node; int /*<<< orphan*/  next; struct ila_xlat_params xp; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct ila_map*) ; 
 int /*<<< orphan*/  ila_cmp_params (struct ila_map*,struct ila_xlat_params*) ; 
 int /*<<< orphan*/ * ila_get_lock (struct ila_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ila_init_saved_csum (TYPE_2__*) ; 
 int /*<<< orphan*/  ila_net_id ; 
 int /*<<< orphan*/  ila_nf_hook_ops ; 
 int ila_order (struct ila_map*) ; 
 int /*<<< orphan*/  kfree (struct ila_map*) ; 
 struct ila_map* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct ila_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int nf_register_net_hooks (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ila_map*) ; 
 struct ila_map* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ila_map* rhashtable_lookup_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rhashtable_lookup_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rhashtable_replace_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rht_params ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ila_add_mapping(struct net *net, struct ila_xlat_params *xp)
{
	struct ila_net *ilan = net_generic(net, ila_net_id);
	struct ila_map *ila, *head;
	spinlock_t *lock = ila_get_lock(ilan, xp->ip.locator_match);
	int err = 0, order;

	if (!ilan->xlat.hooks_registered) {
		/* We defer registering net hooks in the namespace until the
		 * first mapping is added.
		 */
		err = nf_register_net_hooks(net, ila_nf_hook_ops,
					    ARRAY_SIZE(ila_nf_hook_ops));
		if (err)
			return err;

		ilan->xlat.hooks_registered = true;
	}

	ila = kzalloc(sizeof(*ila), GFP_KERNEL);
	if (!ila)
		return -ENOMEM;

	ila_init_saved_csum(&xp->ip);

	ila->xp = *xp;

	order = ila_order(ila);

	spin_lock(lock);

	head = rhashtable_lookup_fast(&ilan->xlat.rhash_table,
				      &xp->ip.locator_match,
				      rht_params);
	if (!head) {
		/* New entry for the rhash_table */
		err = rhashtable_lookup_insert_fast(&ilan->xlat.rhash_table,
						    &ila->node, rht_params);
	} else {
		struct ila_map *tila = head, *prev = NULL;

		do {
			if (!ila_cmp_params(tila, xp)) {
				err = -EEXIST;
				goto out;
			}

			if (order > ila_order(tila))
				break;

			prev = tila;
			tila = rcu_dereference_protected(tila->next,
				lockdep_is_held(lock));
		} while (tila);

		if (prev) {
			/* Insert in sub list of head */
			RCU_INIT_POINTER(ila->next, tila);
			rcu_assign_pointer(prev->next, ila);
		} else {
			/* Make this ila new head */
			RCU_INIT_POINTER(ila->next, head);
			err = rhashtable_replace_fast(&ilan->xlat.rhash_table,
						      &head->node,
						      &ila->node, rht_params);
			if (err)
				goto out;
		}
	}

out:
	spin_unlock(lock);

	if (err)
		kfree(ila);

	return err;
}