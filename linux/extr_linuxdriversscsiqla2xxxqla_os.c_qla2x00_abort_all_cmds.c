#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qla_hw_data {int max_qpairs; int /*<<< orphan*/ * queue_pair_map; int /*<<< orphan*/  base_qpair; } ;
struct TYPE_3__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  __qla2x00_abort_all_cmds (int /*<<< orphan*/ ,int) ; 

void
qla2x00_abort_all_cmds(scsi_qla_host_t *vha, int res)
{
	int que;
	struct qla_hw_data *ha = vha->hw;

	__qla2x00_abort_all_cmds(ha->base_qpair, res);

	for (que = 0; que < ha->max_qpairs; que++) {
		if (!ha->queue_pair_map[que])
			continue;

		__qla2x00_abort_all_cmds(ha->queue_pair_map[que], res);
	}
}