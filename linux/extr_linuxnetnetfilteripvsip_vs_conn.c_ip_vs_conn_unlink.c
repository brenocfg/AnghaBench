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
struct ip_vs_conn {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  c_list; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int IP_VS_CONN_F_HASHED ; 
 int IP_VS_CONN_F_ONE_PACKET ; 
 int /*<<< orphan*/  ct_write_lock_bh (unsigned int) ; 
 int /*<<< orphan*/  ct_write_unlock_bh (unsigned int) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 unsigned int ip_vs_conn_hashkey_conn (struct ip_vs_conn*) ; 
 int refcount_dec_if_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool ip_vs_conn_unlink(struct ip_vs_conn *cp)
{
	unsigned int hash;
	bool ret = false;

	if (cp->flags & IP_VS_CONN_F_ONE_PACKET)
		return refcount_dec_if_one(&cp->refcnt);

	hash = ip_vs_conn_hashkey_conn(cp);

	ct_write_lock_bh(hash);
	spin_lock(&cp->lock);

	if (cp->flags & IP_VS_CONN_F_HASHED) {
		/* Decrease refcnt and unlink conn only if we are last user */
		if (refcount_dec_if_one(&cp->refcnt)) {
			hlist_del_rcu(&cp->c_list);
			cp->flags &= ~IP_VS_CONN_F_HASHED;
			ret = true;
		}
	}

	spin_unlock(&cp->lock);
	ct_write_unlock_bh(hash);

	return ret;
}