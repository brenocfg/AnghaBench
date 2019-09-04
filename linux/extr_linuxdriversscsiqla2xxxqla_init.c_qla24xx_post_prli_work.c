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
struct scsi_qla_host {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fcport; } ;
struct TYPE_4__ {TYPE_1__ fcport; } ;
struct qla_work_evt {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  fc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA_EVT_PRLI ; 
 int QLA_FUNCTION_FAILED ; 
 struct qla_work_evt* qla2x00_alloc_work (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int qla2x00_post_work (struct scsi_qla_host*,struct qla_work_evt*) ; 

__attribute__((used)) static int qla24xx_post_prli_work(struct scsi_qla_host *vha, fc_port_t *fcport)
{
	struct qla_work_evt *e;

	e = qla2x00_alloc_work(vha, QLA_EVT_PRLI);
	if (!e)
		return QLA_FUNCTION_FAILED;

	e->u.fcport.fcport = fcport;

	return qla2x00_post_work(vha, e);
}