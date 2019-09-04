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
struct se_session {scalar_t__ se_node_acl; scalar_t__ sess_bin_isid; } ;
struct se_device {scalar_t__ dev_reserved_node_acl; int dev_reservation_flags; scalar_t__ dev_res_bin_isid; } ;
struct se_cmd {int* t_task_cdb; struct se_session* se_sess; struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
 int DRF_SPC2_RESERVATIONS_WITH_ISID ; 
#define  INQUIRY 130 
#define  RELEASE 129 
#define  RELEASE_10 128 
 int /*<<< orphan*/  TCM_RESERVATION_CONFLICT ; 

__attribute__((used)) static sense_reason_t
target_scsi2_reservation_check(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;
	struct se_session *sess = cmd->se_sess;

	switch (cmd->t_task_cdb[0]) {
	case INQUIRY:
	case RELEASE:
	case RELEASE_10:
		return 0;
	default:
		break;
	}

	if (!dev->dev_reserved_node_acl || !sess)
		return 0;

	if (dev->dev_reserved_node_acl != sess->se_node_acl)
		return TCM_RESERVATION_CONFLICT;

	if (dev->dev_reservation_flags & DRF_SPC2_RESERVATIONS_WITH_ISID) {
		if (dev->dev_res_bin_isid != sess->sess_bin_isid)
			return TCM_RESERVATION_CONFLICT;
	}

	return 0;
}