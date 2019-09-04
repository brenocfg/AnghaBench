#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {int /*<<< orphan*/  sdev_gendev; } ;
struct TYPE_5__ {int nents; int /*<<< orphan*/  sgl; } ;
struct scsi_data_buffer {TYPE_1__ table; } ;
struct scsi_cmnd {struct request* request; struct scsi_data_buffer* prot_sdb; struct scsi_data_buffer sdb; struct scsi_device* device; } ;
struct request {struct scsi_data_buffer* special; TYPE_2__* q; int /*<<< orphan*/  bio; struct request* next_rq; int /*<<< orphan*/ * mq_ctx; } ;
struct TYPE_6__ {int /*<<< orphan*/  mq_ops; } ;

/* Variables and functions */
 int BLKPREP_DEFER ; 
 int BLKPREP_KILL ; 
 int BLKPREP_OK ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ blk_bidi_rq (struct request*) ; 
 scalar_t__ blk_integrity_rq (struct request*) ; 
 int blk_rq_count_integrity_sg (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int blk_rq_map_integrity_sg (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_nr_phys_segments (struct request*) ; 
 struct scsi_data_buffer* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int queue_max_integrity_segments (TYPE_2__*) ; 
 int scsi_init_sgtable (struct request*,struct scsi_data_buffer*) ; 
 int /*<<< orphan*/  scsi_mq_free_sgtables (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_put_command (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_release_buffers (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sdb_cache ; 
 scalar_t__ sg_alloc_table_chained (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlikely (int) ; 

int scsi_init_io(struct scsi_cmnd *cmd)
{
	struct scsi_device *sdev = cmd->device;
	struct request *rq = cmd->request;
	bool is_mq = (rq->mq_ctx != NULL);
	int error = BLKPREP_KILL;

	if (WARN_ON_ONCE(!blk_rq_nr_phys_segments(rq)))
		goto err_exit;

	error = scsi_init_sgtable(rq, &cmd->sdb);
	if (error)
		goto err_exit;

	if (blk_bidi_rq(rq)) {
		if (!rq->q->mq_ops) {
			struct scsi_data_buffer *bidi_sdb =
				kmem_cache_zalloc(scsi_sdb_cache, GFP_ATOMIC);
			if (!bidi_sdb) {
				error = BLKPREP_DEFER;
				goto err_exit;
			}

			rq->next_rq->special = bidi_sdb;
		}

		error = scsi_init_sgtable(rq->next_rq, rq->next_rq->special);
		if (error)
			goto err_exit;
	}

	if (blk_integrity_rq(rq)) {
		struct scsi_data_buffer *prot_sdb = cmd->prot_sdb;
		int ivecs, count;

		if (prot_sdb == NULL) {
			/*
			 * This can happen if someone (e.g. multipath)
			 * queues a command to a device on an adapter
			 * that does not support DIX.
			 */
			WARN_ON_ONCE(1);
			error = BLKPREP_KILL;
			goto err_exit;
		}

		ivecs = blk_rq_count_integrity_sg(rq->q, rq->bio);

		if (sg_alloc_table_chained(&prot_sdb->table, ivecs,
				prot_sdb->table.sgl)) {
			error = BLKPREP_DEFER;
			goto err_exit;
		}

		count = blk_rq_map_integrity_sg(rq->q, rq->bio,
						prot_sdb->table.sgl);
		BUG_ON(unlikely(count > ivecs));
		BUG_ON(unlikely(count > queue_max_integrity_segments(rq->q)));

		cmd->prot_sdb = prot_sdb;
		cmd->prot_sdb->table.nents = count;
	}

	return BLKPREP_OK;
err_exit:
	if (is_mq) {
		scsi_mq_free_sgtables(cmd);
	} else {
		scsi_release_buffers(cmd);
		cmd->request->special = NULL;
		scsi_put_command(cmd);
		put_device(&sdev->sdev_gendev);
	}
	return error;
}