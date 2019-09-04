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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int is_lu_power_on_wp; scalar_t__ f_power_on_wp_en; } ;
struct ufs_hba {TYPE_1__ dev_info; } ;
struct scsi_device {int /*<<< orphan*/  lun; } ;

/* Variables and functions */
 scalar_t__ UFS_LU_POWER_ON_WP ; 
 int /*<<< orphan*/  ufshcd_get_lu_wp (struct ufs_hba*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ufshcd_scsi_to_upiu_lun (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ufshcd_get_lu_power_on_wp_status(struct ufs_hba *hba,
						    struct scsi_device *sdev)
{
	if (hba->dev_info.f_power_on_wp_en &&
	    !hba->dev_info.is_lu_power_on_wp) {
		u8 b_lu_write_protect;

		if (!ufshcd_get_lu_wp(hba, ufshcd_scsi_to_upiu_lun(sdev->lun),
				      &b_lu_write_protect) &&
		    (b_lu_write_protect == UFS_LU_POWER_ON_WP))
			hba->dev_info.is_lu_power_on_wp = true;
	}
}