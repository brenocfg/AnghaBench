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
struct clusterip_net {int /*<<< orphan*/  mutex; scalar_t__ procdir; int /*<<< orphan*/  lock; } ;
struct clusterip_config {int /*<<< orphan*/  pde; int /*<<< orphan*/  list; int /*<<< orphan*/  entries; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 struct clusterip_net* clusterip_pernet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_remove (int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
clusterip_config_entry_put(struct clusterip_config *c)
{
	struct clusterip_net *cn = clusterip_pernet(c->net);

	local_bh_disable();
	if (refcount_dec_and_lock(&c->entries, &cn->lock)) {
		list_del_rcu(&c->list);
		spin_unlock(&cn->lock);
		local_bh_enable();
		/* In case anyone still accesses the file, the open/close
		 * functions are also incrementing the refcount on their own,
		 * so it's safe to remove the entry even if it's in use. */
#ifdef CONFIG_PROC_FS
		mutex_lock(&cn->mutex);
		if (cn->procdir)
			proc_remove(c->pde);
		mutex_unlock(&cn->mutex);
#endif
		return;
	}
	local_bh_enable();
}