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
struct ip_vs_conn {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  c_list; } ;

/* Variables and functions */
 int IP_VS_CONN_F_HASHED ; 
 int /*<<< orphan*/  ct_write_lock_bh (unsigned int) ; 
 int /*<<< orphan*/  ct_write_unlock_bh (unsigned int) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 unsigned int ip_vs_conn_hashkey_conn (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ip_vs_conn_unhash(struct ip_vs_conn *cp)
{
	unsigned int hash;
	int ret;

	/* unhash it and decrease its reference counter */
	hash = ip_vs_conn_hashkey_conn(cp);

	ct_write_lock_bh(hash);
	spin_lock(&cp->lock);

	if (cp->flags & IP_VS_CONN_F_HASHED) {
		hlist_del_rcu(&cp->c_list);
		cp->flags &= ~IP_VS_CONN_F_HASHED;
		refcount_dec(&cp->refcnt);
		ret = 1;
	} else
		ret = 0;

	spin_unlock(&cp->lock);
	ct_write_unlock_bh(hash);

	return ret;
}