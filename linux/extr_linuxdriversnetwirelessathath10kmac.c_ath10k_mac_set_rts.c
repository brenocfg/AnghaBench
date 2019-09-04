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
struct ath10k_vif {int /*<<< orphan*/  vdev_id; struct ath10k* ar; } ;
struct TYPE_4__ {TYPE_1__* vdev_param; } ;
struct ath10k {TYPE_2__ wmi; } ;
struct TYPE_3__ {int /*<<< orphan*/  rts_threshold; } ;

/* Variables and functions */
 int ath10k_wmi_vdev_set_param (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_mac_set_rts(struct ath10k_vif *arvif, u32 value)
{
	struct ath10k *ar = arvif->ar;
	u32 vdev_param;

	vdev_param = ar->wmi.vdev_param->rts_threshold;
	return ath10k_wmi_vdev_set_param(ar, arvif->vdev_id, vdev_param, value);
}