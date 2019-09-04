#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sess_lock; } ;
struct qla_hw_data {TYPE_1__ tgt; } ;
struct TYPE_7__ {scalar_t__ fcport_count; struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_2__*,int,char*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  ql_dbg_init ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int test_fcport_count(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;
	unsigned long flags;
	int res;

	spin_lock_irqsave(&ha->tgt.sess_lock, flags);
	ql_dbg(ql_dbg_init, vha, 0x00ec,
	    "tgt %p, fcport_count=%d\n",
	    vha, vha->fcport_count);
	res = (vha->fcport_count == 0);
	spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);

	return res;
}