#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ marker_needed; TYPE_3__* req; } ;
typedef  TYPE_1__ scsi_qla_host_t ;
struct TYPE_8__ {int /*<<< orphan*/  rsp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MK_SYNC_ALL ; 
 int QLA_FUNCTION_FAILED ; 
 scalar_t__ QLA_SUCCESS ; 
 scalar_t__ __qla2x00_marker (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qla2x00_marker (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qla2x00_issue_marker(scsi_qla_host_t *vha, int ha_locked)
{
	if (ha_locked) {
		if (__qla2x00_marker(vha, vha->req, vha->req->rsp, 0, 0,
					MK_SYNC_ALL) != QLA_SUCCESS)
			return QLA_FUNCTION_FAILED;
	} else {
		if (qla2x00_marker(vha, vha->req, vha->req->rsp, 0, 0,
					MK_SYNC_ALL) != QLA_SUCCESS)
			return QLA_FUNCTION_FAILED;
	}
	vha->marker_needed = 0;

	return QLA_SUCCESS;
}