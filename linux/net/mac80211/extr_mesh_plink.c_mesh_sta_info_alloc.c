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
struct sta_info {int dummy; } ;
struct ieee802_11_elems {int /*<<< orphan*/  total_len; int /*<<< orphan*/  ie_start; } ;
struct TYPE_5__ {int security; scalar_t__ user_mpm; } ;
struct TYPE_6__ {TYPE_2__ mesh; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  dev; TYPE_1__* local; TYPE_3__ u; } ;
struct ieee80211_rx_status {int signal; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_MESH_SEC_AUTHED ; 
 int /*<<< orphan*/  SIGNAL_DBM ; 
 struct sta_info* __mesh_sta_info_alloc (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfg80211_notify_new_peer_candidate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_hw_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mesh_peer_accepts_plinks (struct ieee802_11_elems*) ; 
 scalar_t__ mesh_plink_availables (struct ieee80211_sub_if_data*) ; 

__attribute__((used)) static struct sta_info *
mesh_sta_info_alloc(struct ieee80211_sub_if_data *sdata, u8 *addr,
		    struct ieee802_11_elems *elems,
		    struct ieee80211_rx_status *rx_status)
{
	struct sta_info *sta = NULL;

	/* Userspace handles station allocation */
	if (sdata->u.mesh.user_mpm ||
	    sdata->u.mesh.security & IEEE80211_MESH_SEC_AUTHED) {
		if (mesh_peer_accepts_plinks(elems) &&
		    mesh_plink_availables(sdata)) {
			int sig = 0;

			if (ieee80211_hw_check(&sdata->local->hw, SIGNAL_DBM))
				sig = rx_status->signal;

			cfg80211_notify_new_peer_candidate(sdata->dev, addr,
							   elems->ie_start,
							   elems->total_len,
							   sig, GFP_KERNEL);
		}
	} else
		sta = __mesh_sta_info_alloc(sdata, addr);

	return sta;
}