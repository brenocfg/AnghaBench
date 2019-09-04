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
struct ath10k_vif {scalar_t__ use_cts_prot; int /*<<< orphan*/  vdev_id; struct ath10k* ar; } ;
struct TYPE_4__ {TYPE_1__* vdev_param; } ;
struct ath10k {TYPE_2__ wmi; int /*<<< orphan*/  conf_mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  protection_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_MAC ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int ath10k_wmi_vdev_set_param (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_mac_set_cts_prot(struct ath10k_vif *arvif)
{
	struct ath10k *ar = arvif->ar;
	u32 vdev_param;

	lockdep_assert_held(&ar->conf_mutex);

	vdev_param = ar->wmi.vdev_param->protection_mode;

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac vdev %d cts_protection %d\n",
		   arvif->vdev_id, arvif->use_cts_prot);

	return ath10k_wmi_vdev_set_param(ar, arvif->vdev_id, vdev_param,
					 arvif->use_cts_prot ? 1 : 0);
}