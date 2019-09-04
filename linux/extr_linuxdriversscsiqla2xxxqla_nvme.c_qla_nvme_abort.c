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
struct srb {int /*<<< orphan*/  (* done ) (struct srb*,int) ;} ;
struct TYPE_3__ {scalar_t__ fw_started; } ;
struct qla_hw_data {TYPE_2__* isp_ops; TYPE_1__ flags; } ;
struct TYPE_4__ {int (* abort_command ) (struct srb*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,struct srb*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla_nvme_wait_on_command (struct srb*) ; 
 int stub1 (struct srb*) ; 
 int /*<<< orphan*/  stub2 (struct srb*,int) ; 

void qla_nvme_abort(struct qla_hw_data *ha, struct srb *sp, int res)
{
	int rval;

	if (ha->flags.fw_started) {
		rval = ha->isp_ops->abort_command(sp);
		if (!rval && !qla_nvme_wait_on_command(sp))
			ql_log(ql_log_warn, NULL, 0x2112,
			    "timed out waiting on sp=%p\n", sp);
	} else {
		sp->done(sp, res);
	}
}