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
struct sta_info {int flags; TYPE_1__* local; int /*<<< orphan*/  ap; int /*<<< orphan*/  list; } ;
struct prism2_hostapd_param {int /*<<< orphan*/  sta_addr; } ;
struct ap_data {int /*<<< orphan*/  sta_table_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOENT ; 
 int WLAN_STA_ASSOC ; 
 int /*<<< orphan*/  ap_free_sta (struct ap_data*,struct sta_info*) ; 
 struct sta_info* ap_get_sta (struct ap_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap_sta_hash_del (struct ap_data*,struct sta_info*) ; 
 int /*<<< orphan*/  hostap_event_expired_sta (int /*<<< orphan*/ ,struct sta_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int prism2_hostapd_remove_sta(struct ap_data *ap,
				     struct prism2_hostapd_param *param)
{
	struct sta_info *sta;

	spin_lock_bh(&ap->sta_table_lock);
	sta = ap_get_sta(ap, param->sta_addr);
	if (sta) {
		ap_sta_hash_del(ap, sta);
		list_del(&sta->list);
	}
	spin_unlock_bh(&ap->sta_table_lock);

	if (!sta)
		return -ENOENT;

	if ((sta->flags & WLAN_STA_ASSOC) && !sta->ap && sta->local)
		hostap_event_expired_sta(sta->local->dev, sta);
	ap_free_sta(ap, sta);

	return 0;
}