#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct scsi_cmnd {int flags; int /*<<< orphan*/  sense_buffer; scalar_t__ prot_sdb; } ;
struct request_queue {int dummy; } ;
struct request {int dummy; } ;

/* Variables and functions */
 int SCMD_UNCHECKED_ISA_DMA ; 
 struct scsi_cmnd* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  scsi_free_sense_buffer (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_sdb_cache ; 

__attribute__((used)) static void scsi_old_exit_rq(struct request_queue *q, struct request *rq)
{
	struct scsi_cmnd *cmd = blk_mq_rq_to_pdu(rq);

	if (cmd->prot_sdb)
		kmem_cache_free(scsi_sdb_cache, cmd->prot_sdb);
	scsi_free_sense_buffer(cmd->flags & SCMD_UNCHECKED_ISA_DMA,
			       cmd->sense_buffer);
}