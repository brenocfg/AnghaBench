#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sta_info {int flags; int /*<<< orphan*/  users; } ;
struct net_device {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr2; } ;
typedef  int /*<<< orphan*/  reason ;
struct TYPE_4__ {TYPE_3__* ap; struct net_device* dev; } ;
typedef  TYPE_1__ local_info_t ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_5__ {int /*<<< orphan*/  sta_table_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_AP ; 
 int IEEE80211_FTYPE_MGMT ; 
 int IEEE80211_STYPE_DEAUTH ; 
 int IEEE80211_STYPE_DISASSOC ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WLAN_REASON_CLASS3_FRAME_FROM_NONASSOC_STA ; 
 int WLAN_STA_ASSOC ; 
 struct sta_info* ap_get_sta (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prism2_send_mgmt (struct net_device*,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ap_handle_dropped_data(local_info_t *local,
				   struct ieee80211_hdr *hdr)
{
	struct net_device *dev = local->dev;
	struct sta_info *sta;
	__le16 reason;

	spin_lock_bh(&local->ap->sta_table_lock);
	sta = ap_get_sta(local->ap, hdr->addr2);
	if (sta)
		atomic_inc(&sta->users);
	spin_unlock_bh(&local->ap->sta_table_lock);

	if (sta != NULL && (sta->flags & WLAN_STA_ASSOC)) {
		PDEBUG(DEBUG_AP, "ap_handle_dropped_data: STA is now okay?\n");
		atomic_dec(&sta->users);
		return;
	}

	reason = cpu_to_le16(WLAN_REASON_CLASS3_FRAME_FROM_NONASSOC_STA);
	prism2_send_mgmt(dev, IEEE80211_FTYPE_MGMT |
			 ((sta == NULL || !(sta->flags & WLAN_STA_ASSOC)) ?
			  IEEE80211_STYPE_DEAUTH : IEEE80211_STYPE_DISASSOC),
			 (char *) &reason, sizeof(reason), hdr->addr2, 0);

	if (sta)
		atomic_dec(&sta->users);
}