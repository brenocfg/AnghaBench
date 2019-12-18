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
typedef  int /*<<< orphan*/  u8 ;
struct mesh_table {int /*<<< orphan*/  walk_lock; int /*<<< orphan*/  rhead; } ;
struct mesh_path {int dummy; } ;
struct ieee80211_sub_if_data {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  __mesh_path_del (struct mesh_table*,struct mesh_path*) ; 
 int /*<<< orphan*/  mesh_rht_params ; 
 struct mesh_path* rhashtable_lookup_fast (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int table_path_del(struct mesh_table *tbl,
			  struct ieee80211_sub_if_data *sdata,
			  const u8 *addr)
{
	struct mesh_path *mpath;

	spin_lock_bh(&tbl->walk_lock);
	mpath = rhashtable_lookup_fast(&tbl->rhead, addr, mesh_rht_params);
	if (!mpath) {
		spin_unlock_bh(&tbl->walk_lock);
		return -ENXIO;
	}

	__mesh_path_del(tbl, mpath);
	spin_unlock_bh(&tbl->walk_lock);
	return 0;
}