#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct qla_hw_data {int /*<<< orphan*/  vport_slock; int /*<<< orphan*/  loop_id_map; } ;
struct TYPE_8__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
struct TYPE_7__ {int /*<<< orphan*/  b24; } ;
struct TYPE_9__ {scalar_t__ loop_id; TYPE_1__ d_id; int /*<<< orphan*/  vha; } ;
typedef  TYPE_3__ fc_port_t ;

/* Variables and functions */
 scalar_t__ FC_NO_LOOP_ID ; 
 scalar_t__ LOOPID_MAP_SIZE ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 scalar_t__ find_first_zero_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 scalar_t__ qla2x00_is_reserved_id (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
qla2x00_find_new_loop_id(scsi_qla_host_t *vha, fc_port_t *dev)
{
	int	rval;
	struct qla_hw_data *ha = vha->hw;
	unsigned long flags = 0;

	rval = QLA_SUCCESS;

	spin_lock_irqsave(&ha->vport_slock, flags);

	dev->loop_id = find_first_zero_bit(ha->loop_id_map,
	    LOOPID_MAP_SIZE);
	if (dev->loop_id >= LOOPID_MAP_SIZE ||
	    qla2x00_is_reserved_id(vha, dev->loop_id)) {
		dev->loop_id = FC_NO_LOOP_ID;
		rval = QLA_FUNCTION_FAILED;
	} else
		set_bit(dev->loop_id, ha->loop_id_map);

	spin_unlock_irqrestore(&ha->vport_slock, flags);

	if (rval == QLA_SUCCESS)
		ql_dbg(ql_dbg_disc, dev->vha, 0x2086,
		    "Assigning new loopid=%x, portid=%x.\n",
		    dev->loop_id, dev->d_id.b24);
	else
		ql_log(ql_log_warn, dev->vha, 0x2087,
		    "No loop_id's available, portid=%x.\n",
		    dev->d_id.b24);

	return (rval);
}