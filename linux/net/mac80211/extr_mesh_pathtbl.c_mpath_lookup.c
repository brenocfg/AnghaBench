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
struct mesh_table {int /*<<< orphan*/  rhead; } ;
struct mesh_path {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  flags; } ;
struct ieee80211_sub_if_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESH_PATH_ACTIVE ; 
 int /*<<< orphan*/  mesh_rht_params ; 
 scalar_t__ mpath_expired (struct mesh_path*) ; 
 struct mesh_path* rhashtable_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mesh_path *mpath_lookup(struct mesh_table *tbl, const u8 *dst,
				      struct ieee80211_sub_if_data *sdata)
{
	struct mesh_path *mpath;

	mpath = rhashtable_lookup(&tbl->rhead, dst, mesh_rht_params);

	if (mpath && mpath_expired(mpath)) {
		spin_lock_bh(&mpath->state_lock);
		mpath->flags &= ~MESH_PATH_ACTIVE;
		spin_unlock_bh(&mpath->state_lock);
	}
	return mpath;
}