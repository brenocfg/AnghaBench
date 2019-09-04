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
struct TYPE_2__ {scalar_t__ sense; } ;
struct scsi_cmnd {scalar_t__ sense_buffer; int /*<<< orphan*/  prot_sdb; TYPE_1__ req; int /*<<< orphan*/  flags; } ;
struct request_queue {struct Scsi_Host* rq_alloc_data; } ;
struct request {int dummy; } ;
struct Scsi_Host {int unchecked_isa_dma; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int /*<<< orphan*/  SCMD_UNCHECKED_ISA_DMA ; 
 scalar_t__ SHOST_DIX_TYPE0_PROTECTION ; 
 struct scsi_cmnd* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct scsi_cmnd*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ scsi_alloc_sense_buffer (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_free_sense_buffer (int const,scalar_t__) ; 
 scalar_t__ scsi_host_get_prot (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_sdb_cache ; 

__attribute__((used)) static int scsi_old_init_rq(struct request_queue *q, struct request *rq,
			    gfp_t gfp)
{
	struct Scsi_Host *shost = q->rq_alloc_data;
	const bool unchecked_isa_dma = shost->unchecked_isa_dma;
	struct scsi_cmnd *cmd = blk_mq_rq_to_pdu(rq);

	memset(cmd, 0, sizeof(*cmd));

	if (unchecked_isa_dma)
		cmd->flags |= SCMD_UNCHECKED_ISA_DMA;
	cmd->sense_buffer = scsi_alloc_sense_buffer(unchecked_isa_dma, gfp,
						    NUMA_NO_NODE);
	if (!cmd->sense_buffer)
		goto fail;
	cmd->req.sense = cmd->sense_buffer;

	if (scsi_host_get_prot(shost) >= SHOST_DIX_TYPE0_PROTECTION) {
		cmd->prot_sdb = kmem_cache_zalloc(scsi_sdb_cache, gfp);
		if (!cmd->prot_sdb)
			goto fail_free_sense;
	}

	return 0;

fail_free_sense:
	scsi_free_sense_buffer(unchecked_isa_dma, cmd->sense_buffer);
fail:
	return -ENOMEM;
}