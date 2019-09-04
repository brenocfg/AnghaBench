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
struct scsi_qla_host {int dummy; } ;
struct TYPE_3__ {int code; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__ aen; } ;
struct qla_work_evt {TYPE_2__ u; } ;
typedef  enum fc_host_event_code { ____Placeholder_fc_host_event_code } fc_host_event_code ;

/* Variables and functions */
 int /*<<< orphan*/  QLA_EVT_AEN ; 
 int QLA_FUNCTION_FAILED ; 
 struct qla_work_evt* qla2x00_alloc_work (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int qla2x00_post_work (struct scsi_qla_host*,struct qla_work_evt*) ; 

int
qla2x00_post_aen_work(struct scsi_qla_host *vha, enum fc_host_event_code code,
    u32 data)
{
	struct qla_work_evt *e;

	e = qla2x00_alloc_work(vha, QLA_EVT_AEN);
	if (!e)
		return QLA_FUNCTION_FAILED;

	e->u.aen.code = code;
	e->u.aen.data = data;
	return qla2x00_post_work(vha, e);
}