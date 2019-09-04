#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mesh_path {int flags; int /*<<< orphan*/  frame_queue; TYPE_1__* sdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  local; } ;

/* Variables and functions */
 int MESH_PATH_ACTIVE ; 
 int /*<<< orphan*/  ieee80211_add_pending_skbs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mesh_path_tx_pending(struct mesh_path *mpath)
{
	if (mpath->flags & MESH_PATH_ACTIVE)
		ieee80211_add_pending_skbs(mpath->sdata->local,
				&mpath->frame_queue);
}