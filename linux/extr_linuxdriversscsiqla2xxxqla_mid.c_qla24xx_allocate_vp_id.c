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
typedef  scalar_t__ uint32_t ;
struct qla_hw_data {scalar_t__ max_npiv_vports; int /*<<< orphan*/  vport_lock; int /*<<< orphan*/  hardware_lock; int /*<<< orphan*/  vport_slock; int /*<<< orphan*/  vp_list; int /*<<< orphan*/  num_vhosts; int /*<<< orphan*/  vp_idx_map; } ;
struct TYPE_5__ {int /*<<< orphan*/  list; scalar_t__ vp_idx; struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  SET_VP_IDX ; 
 scalar_t__ find_first_zero_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_1__*,int,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ql_dbg_vport ; 
 int /*<<< orphan*/  qlt_update_vp_map (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static uint32_t
qla24xx_allocate_vp_id(scsi_qla_host_t *vha)
{
	uint32_t vp_id;
	struct qla_hw_data *ha = vha->hw;
	unsigned long flags;

	/* Find an empty slot and assign an vp_id */
	mutex_lock(&ha->vport_lock);
	vp_id = find_first_zero_bit(ha->vp_idx_map, ha->max_npiv_vports + 1);
	if (vp_id > ha->max_npiv_vports) {
		ql_dbg(ql_dbg_vport, vha, 0xa000,
		    "vp_id %d is bigger than max-supported %d.\n",
		    vp_id, ha->max_npiv_vports);
		mutex_unlock(&ha->vport_lock);
		return vp_id;
	}

	set_bit(vp_id, ha->vp_idx_map);
	ha->num_vhosts++;
	vha->vp_idx = vp_id;

	spin_lock_irqsave(&ha->vport_slock, flags);
	list_add_tail(&vha->list, &ha->vp_list);
	spin_unlock_irqrestore(&ha->vport_slock, flags);

	spin_lock_irqsave(&ha->hardware_lock, flags);
	qlt_update_vp_map(vha, SET_VP_IDX);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	mutex_unlock(&ha->vport_lock);
	return vp_id;
}