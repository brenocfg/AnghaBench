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
struct mesh_table {int /*<<< orphan*/  rhead; } ;
struct mesh_path {int /*<<< orphan*/  rhash; int /*<<< orphan*/  walk_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mesh_path_free_rcu (struct mesh_table*,struct mesh_path*) ; 
 int /*<<< orphan*/  mesh_rht_params ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __mesh_path_del(struct mesh_table *tbl, struct mesh_path *mpath)
{
	hlist_del_rcu(&mpath->walk_list);
	rhashtable_remove_fast(&tbl->rhead, &mpath->rhash, mesh_rht_params);
	mesh_path_free_rcu(tbl, mpath);
}