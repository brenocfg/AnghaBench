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
typedef  int /*<<< orphan*/  u64 ;
struct se_portal_group {int dummy; } ;
struct se_node_acl {int dummy; } ;
struct se_lun {int /*<<< orphan*/  unpacked_lun; } ;
struct se_device {int dev_reservation_flags; } ;

/* Variables and functions */
 int DRF_SPC2_RESERVATIONS ; 
 int __core_scsi3_check_aptpl_registration (struct se_device*,struct se_portal_group*,struct se_lun*,int /*<<< orphan*/ ,struct se_node_acl*,int /*<<< orphan*/ ) ; 

int core_scsi3_check_aptpl_registration(
	struct se_device *dev,
	struct se_portal_group *tpg,
	struct se_lun *lun,
	struct se_node_acl *nacl,
	u64 mapped_lun)
{
	if (dev->dev_reservation_flags & DRF_SPC2_RESERVATIONS)
		return 0;

	return __core_scsi3_check_aptpl_registration(dev, tpg, lun,
						     lun->unpacked_lun, nacl,
						     mapped_lun);
}