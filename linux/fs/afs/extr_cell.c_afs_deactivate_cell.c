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
struct afs_net {int /*<<< orphan*/  proc_cells_lock; } ;
struct afs_cell {int /*<<< orphan*/ * cache; int /*<<< orphan*/  proc_link; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_dynroot_rmdir (struct afs_net*,struct afs_cell*) ; 
 int /*<<< orphan*/  afs_proc_cell_remove (struct afs_cell*) ; 
 int /*<<< orphan*/  fscache_relinquish_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void afs_deactivate_cell(struct afs_net *net, struct afs_cell *cell)
{
	_enter("%s", cell->name);

	afs_proc_cell_remove(cell);

	mutex_lock(&net->proc_cells_lock);
	hlist_del_rcu(&cell->proc_link);
	afs_dynroot_rmdir(net, cell);
	mutex_unlock(&net->proc_cells_lock);

#ifdef CONFIG_AFS_FSCACHE
	fscache_relinquish_cookie(cell->cache, NULL, false);
	cell->cache = NULL;
#endif

	_leave("");
}