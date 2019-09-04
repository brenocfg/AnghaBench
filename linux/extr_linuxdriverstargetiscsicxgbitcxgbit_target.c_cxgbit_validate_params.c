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
typedef  scalar_t__ u32 ;
struct iscsi_param {int /*<<< orphan*/  value; } ;
struct iscsi_conn {int /*<<< orphan*/  param_list; struct cxgbit_sock* context; } ;
struct TYPE_2__ {struct cxgbit_device* cdev; } ;
struct cxgbit_sock {TYPE_1__ com; } ;
struct cxgbit_device {scalar_t__ mdsl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXXMITDATASEGMENTLENGTH ; 
 scalar_t__ iscsi_change_param_sprintf (struct iscsi_conn*,char*,scalar_t__) ; 
 struct iscsi_param* iscsi_find_param_from_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtou32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

int cxgbit_validate_params(struct iscsi_conn *conn)
{
	struct cxgbit_sock *csk = conn->context;
	struct cxgbit_device *cdev = csk->com.cdev;
	struct iscsi_param *param;
	u32 max_xmitdsl;

	param = iscsi_find_param_from_key(MAXXMITDATASEGMENTLENGTH,
					  conn->param_list);
	if (!param)
		return -1;

	if (kstrtou32(param->value, 0, &max_xmitdsl) < 0)
		return -1;

	if (max_xmitdsl > cdev->mdsl) {
		if (iscsi_change_param_sprintf(
			conn, "MaxXmitDataSegmentLength=%u", cdev->mdsl))
			return -1;
	}

	return 0;
}