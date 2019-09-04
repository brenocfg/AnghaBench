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
typedef  size_t u32 ;
struct netlbl_unlhsh_iface {int ifindex; int valid; int /*<<< orphan*/  list; int /*<<< orphan*/  addr6_list; int /*<<< orphan*/  addr4_list; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct netlbl_unlhsh_iface*) ; 
 struct netlbl_unlhsh_iface* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netlbl_unlhsh ; 
 int /*<<< orphan*/  netlbl_unlhsh_def ; 
 size_t netlbl_unlhsh_hash (int) ; 
 int /*<<< orphan*/  netlbl_unlhsh_lock ; 
 TYPE_1__* netlbl_unlhsh_rcu_deref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * netlbl_unlhsh_search_iface (int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct netlbl_unlhsh_iface*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct netlbl_unlhsh_iface *netlbl_unlhsh_add_iface(int ifindex)
{
	u32 bkt;
	struct netlbl_unlhsh_iface *iface;

	iface = kzalloc(sizeof(*iface), GFP_ATOMIC);
	if (iface == NULL)
		return NULL;

	iface->ifindex = ifindex;
	INIT_LIST_HEAD(&iface->addr4_list);
	INIT_LIST_HEAD(&iface->addr6_list);
	iface->valid = 1;

	spin_lock(&netlbl_unlhsh_lock);
	if (ifindex > 0) {
		bkt = netlbl_unlhsh_hash(ifindex);
		if (netlbl_unlhsh_search_iface(ifindex) != NULL)
			goto add_iface_failure;
		list_add_tail_rcu(&iface->list,
			     &netlbl_unlhsh_rcu_deref(netlbl_unlhsh)->tbl[bkt]);
	} else {
		INIT_LIST_HEAD(&iface->list);
		if (netlbl_unlhsh_rcu_deref(netlbl_unlhsh_def) != NULL)
			goto add_iface_failure;
		rcu_assign_pointer(netlbl_unlhsh_def, iface);
	}
	spin_unlock(&netlbl_unlhsh_lock);

	return iface;

add_iface_failure:
	spin_unlock(&netlbl_unlhsh_lock);
	kfree(iface);
	return NULL;
}