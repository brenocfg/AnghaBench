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
struct seq_file {struct scsi_qla_host* private; } ;
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_act_qpairs; } ;
struct qla_hw_data {TYPE_1__ tgt; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla_dfs_naqp_show(struct seq_file *s, void *unused)
{
	struct scsi_qla_host *vha = s->private;
	struct qla_hw_data *ha = vha->hw;

	seq_printf(s, "%d\n", ha->tgt.num_act_qpairs);
	return 0;
}