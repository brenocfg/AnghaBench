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
struct mountpoint {int /*<<< orphan*/  m_hash; int /*<<< orphan*/  m_list; struct dentry* m_dentry; int /*<<< orphan*/  m_count; } ;
struct list_head {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DCACHE_MOUNTED ; 
 int /*<<< orphan*/  dput_to_list (struct dentry*,struct list_head*) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mountpoint*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __put_mountpoint(struct mountpoint *mp, struct list_head *list)
{
	if (!--mp->m_count) {
		struct dentry *dentry = mp->m_dentry;
		BUG_ON(!hlist_empty(&mp->m_list));
		spin_lock(&dentry->d_lock);
		dentry->d_flags &= ~DCACHE_MOUNTED;
		spin_unlock(&dentry->d_lock);
		dput_to_list(dentry, list);
		hlist_del(&mp->m_hash);
		kfree(mp);
	}
}