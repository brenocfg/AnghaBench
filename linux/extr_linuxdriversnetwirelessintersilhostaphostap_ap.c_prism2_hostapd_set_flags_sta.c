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
struct sta_info {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags_and; int /*<<< orphan*/  flags_or; } ;
struct TYPE_3__ {TYPE_2__ set_flags_sta; } ;
struct prism2_hostapd_param {TYPE_1__ u; int /*<<< orphan*/  sta_addr; } ;
struct ap_data {int /*<<< orphan*/  sta_table_lock; } ;

/* Variables and functions */
 int ENOENT ; 
 struct sta_info* ap_get_sta (struct ap_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int prism2_hostapd_set_flags_sta(struct ap_data *ap,
					struct prism2_hostapd_param *param)
{
	struct sta_info *sta;

	spin_lock_bh(&ap->sta_table_lock);
	sta = ap_get_sta(ap, param->sta_addr);
	if (sta) {
		sta->flags |= param->u.set_flags_sta.flags_or;
		sta->flags &= param->u.set_flags_sta.flags_and;
	}
	spin_unlock_bh(&ap->sta_table_lock);

	if (!sta)
		return -ENOENT;

	return 0;
}