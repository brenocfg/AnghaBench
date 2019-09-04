#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ nents; } ;
struct scsi_data_buffer {TYPE_5__ table; } ;
struct TYPE_7__ {TYPE_5__ table; } ;
struct scsi_cmnd {TYPE_1__* prot_sdb; TYPE_4__* request; TYPE_2__ sdb; } ;
struct TYPE_9__ {TYPE_3__* next_rq; } ;
struct TYPE_8__ {struct scsi_data_buffer* special; } ;
struct TYPE_6__ {TYPE_5__ table; } ;

/* Variables and functions */
 scalar_t__ scsi_prot_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sg_free_table_chained (TYPE_5__*,int) ; 

__attribute__((used)) static void scsi_mq_free_sgtables(struct scsi_cmnd *cmd)
{
	struct scsi_data_buffer *sdb;

	if (cmd->sdb.table.nents)
		sg_free_table_chained(&cmd->sdb.table, true);
	if (cmd->request->next_rq) {
		sdb = cmd->request->next_rq->special;
		if (sdb)
			sg_free_table_chained(&sdb->table, true);
	}
	if (scsi_prot_sg_count(cmd))
		sg_free_table_chained(&cmd->prot_sdb->table, true);
}