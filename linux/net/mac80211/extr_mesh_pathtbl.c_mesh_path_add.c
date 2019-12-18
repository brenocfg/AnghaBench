#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mesh_table {int /*<<< orphan*/  walk_lock; int /*<<< orphan*/  walk_head; int /*<<< orphan*/  rhead; } ;
struct mesh_path {int /*<<< orphan*/  walk_list; int /*<<< orphan*/  rhash; } ;
struct TYPE_5__ {int /*<<< orphan*/  mesh_paths_generation; struct mesh_table* mesh_paths; int /*<<< orphan*/  mpaths; } ;
struct TYPE_6__ {TYPE_2__ mesh; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct ieee80211_sub_if_data {TYPE_3__ u; TYPE_1__ vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  ENOTSUPP ; 
 struct mesh_path* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (struct mesh_path*) ; 
 int /*<<< orphan*/  MESH_MAX_MPATHS ; 
 scalar_t__ atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  kfree (struct mesh_path*) ; 
 struct mesh_path* mesh_path_new (struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mesh_rht_params ; 
 struct mesh_path* rhashtable_lookup_get_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

struct mesh_path *mesh_path_add(struct ieee80211_sub_if_data *sdata,
				const u8 *dst)
{
	struct mesh_table *tbl;
	struct mesh_path *mpath, *new_mpath;

	if (ether_addr_equal(dst, sdata->vif.addr))
		/* never add ourselves as neighbours */
		return ERR_PTR(-ENOTSUPP);

	if (is_multicast_ether_addr(dst))
		return ERR_PTR(-ENOTSUPP);

	if (atomic_add_unless(&sdata->u.mesh.mpaths, 1, MESH_MAX_MPATHS) == 0)
		return ERR_PTR(-ENOSPC);

	new_mpath = mesh_path_new(sdata, dst, GFP_ATOMIC);
	if (!new_mpath)
		return ERR_PTR(-ENOMEM);

	tbl = sdata->u.mesh.mesh_paths;
	spin_lock_bh(&tbl->walk_lock);
	mpath = rhashtable_lookup_get_insert_fast(&tbl->rhead,
						  &new_mpath->rhash,
						  mesh_rht_params);
	if (!mpath)
		hlist_add_head(&new_mpath->walk_list, &tbl->walk_head);
	spin_unlock_bh(&tbl->walk_lock);

	if (mpath) {
		kfree(new_mpath);

		if (IS_ERR(mpath))
			return mpath;

		new_mpath = mpath;
	}

	sdata->u.mesh.mesh_paths_generation++;
	return new_mpath;
}