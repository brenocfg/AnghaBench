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
struct dfs_cache_entry {int /*<<< orphan*/  ce_rcu; int /*<<< orphan*/  ce_path; int /*<<< orphan*/  ce_hlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfs_cache_count ; 
 int /*<<< orphan*/  free_cache_entry ; 
 int /*<<< orphan*/  free_tgts (struct dfs_cache_entry*) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void flush_cache_ent(struct dfs_cache_entry *ce)
{
	if (hlist_unhashed(&ce->ce_hlist))
		return;

	hlist_del_init_rcu(&ce->ce_hlist);
	kfree_const(ce->ce_path);
	free_tgts(ce);
	dfs_cache_count--;
	call_rcu(&ce->ce_rcu, free_cache_entry);
}