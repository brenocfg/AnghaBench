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
struct ufs_hba {int dummy; } ;

/* Variables and functions */
 scalar_t__ UFS_UNIPRO_VER_1_6 ; 
 scalar_t__ ufshcd_get_local_unipro_ver (struct ufs_hba*) ; 

__attribute__((used)) static bool ufshcd_is_unipro_pa_params_tuning_req(struct ufs_hba *hba)
{
	/*
	 * If both host and device support UniPro ver1.6 or later, PA layer
	 * parameters tuning happens during link startup itself.
	 *
	 * We can manually tune PA layer parameters if either host or device
	 * doesn't support UniPro ver 1.6 or later. But to keep manual tuning
	 * logic simple, we will only do manual tuning if local unipro version
	 * doesn't support ver1.6 or later.
	 */
	if (ufshcd_get_local_unipro_ver(hba) < UFS_UNIPRO_VER_1_6)
		return true;
	else
		return false;
}