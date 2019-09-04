#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mesh_path {int flags; int /*<<< orphan*/  state_lock; } ;
struct TYPE_10__ {int /*<<< orphan*/  dropped_frames_no_route; int /*<<< orphan*/  fwded_frames; int /*<<< orphan*/  fwded_unicast; int /*<<< orphan*/  dropped_frames_ttl; } ;
struct TYPE_8__ {int /*<<< orphan*/  dot11MeshForwarding; } ;
struct ieee80211_if_mesh {TYPE_4__ mshstats; TYPE_2__ mshcfg; } ;
struct TYPE_11__ {struct ieee80211_if_mesh mesh; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct ieee80211_sub_if_data {TYPE_5__ u; TYPE_1__ vif; } ;
struct ieee80211_mgmt {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  addr; } ;
struct TYPE_12__ {TYPE_3__ sta; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int MESH_PATH_ACTIVE ; 
 int /*<<< orphan*/  MPATH_PREP ; 
 int PREP_IE_FLAGS (int const*) ; 
 int PREP_IE_HOPCOUNT (int const*) ; 
 int /*<<< orphan*/  PREP_IE_LIFETIME (int const*) ; 
 int* PREP_IE_ORIG_ADDR (int const*) ; 
 int /*<<< orphan*/  PREP_IE_ORIG_SN (int const*) ; 
 int* PREP_IE_TARGET_ADDR (int const*) ; 
 int /*<<< orphan*/  PREP_IE_TARGET_SN (int const*) ; 
 int PREP_IE_TTL (int const*) ; 
 scalar_t__ ether_addr_equal (int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 struct mesh_path* mesh_path_lookup (struct ieee80211_sub_if_data*,int const*) ; 
 int /*<<< orphan*/  mesh_path_sel_frame_tx (int /*<<< orphan*/ ,int,int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*,int /*<<< orphan*/ ,int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  mhwmp_dbg (struct ieee80211_sub_if_data*,char*,int*) ; 
 TYPE_6__* next_hop_deref_protected (struct mesh_path*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hwmp_prep_frame_process(struct ieee80211_sub_if_data *sdata,
				    struct ieee80211_mgmt *mgmt,
				    const u8 *prep_elem, u32 metric)
{
	struct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	struct mesh_path *mpath;
	const u8 *target_addr, *orig_addr;
	u8 ttl, hopcount, flags;
	u8 next_hop[ETH_ALEN];
	u32 target_sn, orig_sn, lifetime;

	mhwmp_dbg(sdata, "received PREP from %pM\n",
		  PREP_IE_TARGET_ADDR(prep_elem));

	orig_addr = PREP_IE_ORIG_ADDR(prep_elem);
	if (ether_addr_equal(orig_addr, sdata->vif.addr))
		/* destination, no forwarding required */
		return;

	if (!ifmsh->mshcfg.dot11MeshForwarding)
		return;

	ttl = PREP_IE_TTL(prep_elem);
	if (ttl <= 1) {
		sdata->u.mesh.mshstats.dropped_frames_ttl++;
		return;
	}

	rcu_read_lock();
	mpath = mesh_path_lookup(sdata, orig_addr);
	if (mpath)
		spin_lock_bh(&mpath->state_lock);
	else
		goto fail;
	if (!(mpath->flags & MESH_PATH_ACTIVE)) {
		spin_unlock_bh(&mpath->state_lock);
		goto fail;
	}
	memcpy(next_hop, next_hop_deref_protected(mpath)->sta.addr, ETH_ALEN);
	spin_unlock_bh(&mpath->state_lock);
	--ttl;
	flags = PREP_IE_FLAGS(prep_elem);
	lifetime = PREP_IE_LIFETIME(prep_elem);
	hopcount = PREP_IE_HOPCOUNT(prep_elem) + 1;
	target_addr = PREP_IE_TARGET_ADDR(prep_elem);
	target_sn = PREP_IE_TARGET_SN(prep_elem);
	orig_sn = PREP_IE_ORIG_SN(prep_elem);

	mesh_path_sel_frame_tx(MPATH_PREP, flags, orig_addr, orig_sn, 0,
			       target_addr, target_sn, next_hop, hopcount,
			       ttl, lifetime, metric, 0, sdata);
	rcu_read_unlock();

	sdata->u.mesh.mshstats.fwded_unicast++;
	sdata->u.mesh.mshstats.fwded_frames++;
	return;

fail:
	rcu_read_unlock();
	sdata->u.mesh.mshstats.dropped_frames_no_route++;
}