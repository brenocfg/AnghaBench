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
struct mesh_path {int /*<<< orphan*/  walk_list; int /*<<< orphan*/  rhash; int /*<<< orphan*/  mpp; } ;
struct TYPE_5__ {int /*<<< orphan*/  mpp_paths_generation; struct mesh_table* mpp_paths; } ;
struct TYPE_6__ {TYPE_2__ mesh; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct ieee80211_sub_if_data {TYPE_3__ u; TYPE_1__ vif; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  kfree (struct mesh_path*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct mesh_path* mesh_path_new (struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mesh_rht_params ; 
 int rhashtable_lookup_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int mpp_path_add(struct ieee80211_sub_if_data *sdata,
		 const u8 *dst, const u8 *mpp)
{
	struct mesh_table *tbl;
	struct mesh_path *new_mpath;
	int ret;

	if (ether_addr_equal(dst, sdata->vif.addr))
		/* never add ourselves as neighbours */
		return -ENOTSUPP;

	if (is_multicast_ether_addr(dst))
		return -ENOTSUPP;

	new_mpath = mesh_path_new(sdata, dst, GFP_ATOMIC);

	if (!new_mpath)
		return -ENOMEM;

	memcpy(new_mpath->mpp, mpp, ETH_ALEN);
	tbl = sdata->u.mesh.mpp_paths;

	spin_lock_bh(&tbl->walk_lock);
	ret = rhashtable_lookup_insert_fast(&tbl->rhead,
					    &new_mpath->rhash,
					    mesh_rht_params);
	if (!ret)
		hlist_add_head_rcu(&new_mpath->walk_list, &tbl->walk_head);
	spin_unlock_bh(&tbl->walk_lock);

	if (ret)
		kfree(new_mpath);

	sdata->u.mesh.mpp_paths_generation++;
	return ret;
}