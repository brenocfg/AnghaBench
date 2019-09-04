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
struct ath10k {int filter_flags; int /*<<< orphan*/  dev_flags; TYPE_2__* running_fw; scalar_t__ monitor; scalar_t__ monitor_arvif; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fw_features; } ;
struct TYPE_4__ {TYPE_1__ fw_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_CAC_RUNNING ; 
 int /*<<< orphan*/  ATH10K_FW_FEATURE_ALLOWS_MESH_BCAST ; 
 int FIF_OTHER_BSS ; 
 int ath10k_mac_num_chanctxs (struct ath10k*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ath10k_mac_monitor_vdev_is_needed(struct ath10k *ar)
{
	int num_ctx;

	/* At least one chanctx is required to derive a channel to start
	 * monitor vdev on.
	 */
	num_ctx = ath10k_mac_num_chanctxs(ar);
	if (num_ctx == 0)
		return false;

	/* If there's already an existing special monitor interface then don't
	 * bother creating another monitor vdev.
	 */
	if (ar->monitor_arvif)
		return false;

	return ar->monitor ||
	       (!test_bit(ATH10K_FW_FEATURE_ALLOWS_MESH_BCAST,
			  ar->running_fw->fw_file.fw_features) &&
		(ar->filter_flags & FIF_OTHER_BSS)) ||
	       test_bit(ATH10K_CAC_RUNNING, &ar->dev_flags);
}