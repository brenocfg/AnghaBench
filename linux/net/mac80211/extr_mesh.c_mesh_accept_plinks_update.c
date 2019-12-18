#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int accepting_plinks; } ;
struct TYPE_4__ {TYPE_1__ mesh; } ;
struct ieee80211_sub_if_data {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_CHANGED_BEACON ; 
 int mesh_plink_availables (struct ieee80211_sub_if_data*) ; 

u32 mesh_accept_plinks_update(struct ieee80211_sub_if_data *sdata)
{
	bool free_plinks;
	u32 changed = 0;

	/* In case mesh_plink_free_count > 0 and mesh_plinktbl_capacity == 0,
	 * the mesh interface might be able to establish plinks with peers that
	 * are already on the table but are not on PLINK_ESTAB state. However,
	 * in general the mesh interface is not accepting peer link requests
	 * from new peers, and that must be reflected in the beacon
	 */
	free_plinks = mesh_plink_availables(sdata);

	if (free_plinks != sdata->u.mesh.accepting_plinks) {
		sdata->u.mesh.accepting_plinks = free_plinks;
		changed = BSS_CHANGED_BEACON;
	}

	return changed;
}