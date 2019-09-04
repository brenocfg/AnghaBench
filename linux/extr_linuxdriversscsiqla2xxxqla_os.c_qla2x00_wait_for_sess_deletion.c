#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  fcport_waitQ; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  qla2x00_mark_all_devices_lost (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_fcport_count (TYPE_1__*) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
qla2x00_wait_for_sess_deletion(scsi_qla_host_t *vha)
{
	qla2x00_mark_all_devices_lost(vha, 0);

	wait_event_timeout(vha->fcport_waitQ, test_fcport_count(vha), 10*HZ);
}