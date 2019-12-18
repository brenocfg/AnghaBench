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
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct sta_info {TYPE_2__* mesh; TYPE_1__ sta; int /*<<< orphan*/  sdata; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  enum nl80211_mesh_power_mode { ____Placeholder_nl80211_mesh_power_mode } nl80211_mesh_power_mode ;
struct TYPE_4__ {int nonpeer_pm; } ;

/* Variables and functions */
 int NL80211_MESH_POWER_ACTIVE ; 
 int NL80211_MESH_POWER_DEEP_SLEEP ; 
 scalar_t__ ieee80211_has_pm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_mps_sta_status_update (struct sta_info*) ; 
 int /*<<< orphan*/  mps_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mps_set_sta_nonpeer_pm(struct sta_info *sta,
				   struct ieee80211_hdr *hdr)
{
	enum nl80211_mesh_power_mode pm;

	if (ieee80211_has_pm(hdr->frame_control))
		pm = NL80211_MESH_POWER_DEEP_SLEEP;
	else
		pm = NL80211_MESH_POWER_ACTIVE;

	if (sta->mesh->nonpeer_pm == pm)
		return;

	mps_dbg(sta->sdata, "STA %pM sets non-peer mode to %d\n",
		sta->sta.addr, pm);

	sta->mesh->nonpeer_pm = pm;

	ieee80211_mps_sta_status_update(sta);
}