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
typedef  int /*<<< orphan*/  u32 ;
struct ath10k_vif_iter {struct ath10k_vif* arvif; int /*<<< orphan*/  vdev_id; } ;
struct ath10k_vif {int dummy; } ;
struct ath10k {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
 int /*<<< orphan*/  ath10k_get_arvif_iter ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ath10k_vif_iter*) ; 
 int /*<<< orphan*/  memset (struct ath10k_vif_iter*,int /*<<< orphan*/ ,int) ; 

struct ath10k_vif *ath10k_get_arvif(struct ath10k *ar, u32 vdev_id)
{
	struct ath10k_vif_iter arvif_iter;
	u32 flags;

	memset(&arvif_iter, 0, sizeof(struct ath10k_vif_iter));
	arvif_iter.vdev_id = vdev_id;

	flags = IEEE80211_IFACE_ITER_RESUME_ALL;
	ieee80211_iterate_active_interfaces_atomic(ar->hw,
						   flags,
						   ath10k_get_arvif_iter,
						   &arvif_iter);
	if (!arvif_iter.arvif) {
		ath10k_warn(ar, "No VIF found for vdev %d\n", vdev_id);
		return NULL;
	}

	return arvif_iter.arvif;
}