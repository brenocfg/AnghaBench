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
struct scsi_device {struct Scsi_Host* host; } ;
struct scsi_cmnd {int dummy; } ;
struct request_queue {int /*<<< orphan*/  initialize_rq_fn; int /*<<< orphan*/  exit_rq_fn; int /*<<< orphan*/  init_rq_fn; int /*<<< orphan*/  request_fn; struct Scsi_Host* rq_alloc_data; scalar_t__ cmd_size; } ;
struct Scsi_Host {TYPE_1__* hostt; } ;
struct TYPE_2__ {scalar_t__ cmd_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int /*<<< orphan*/  QUEUE_FLAG_SCSI_PASSTHROUGH ; 
 int /*<<< orphan*/  __scsi_init_queue (struct Scsi_Host*,struct request_queue*) ; 
 struct request_queue* blk_alloc_queue_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_cleanup_queue (struct request_queue*) ; 
 scalar_t__ blk_init_allocated_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_lld_busy (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_prep_rq (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_rq_timed_out (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_softirq_done (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_unprep_rq (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_initialize_rq ; 
 int /*<<< orphan*/  scsi_lld_busy ; 
 int /*<<< orphan*/  scsi_old_exit_rq ; 
 int /*<<< orphan*/  scsi_old_init_rq ; 
 int /*<<< orphan*/  scsi_prep_fn ; 
 int /*<<< orphan*/  scsi_request_fn ; 
 int /*<<< orphan*/  scsi_softirq_done ; 
 int /*<<< orphan*/  scsi_times_out ; 
 int /*<<< orphan*/  scsi_unprep_fn ; 

struct request_queue *scsi_old_alloc_queue(struct scsi_device *sdev)
{
	struct Scsi_Host *shost = sdev->host;
	struct request_queue *q;

	q = blk_alloc_queue_node(GFP_KERNEL, NUMA_NO_NODE, NULL);
	if (!q)
		return NULL;
	q->cmd_size = sizeof(struct scsi_cmnd) + shost->hostt->cmd_size;
	q->rq_alloc_data = shost;
	q->request_fn = scsi_request_fn;
	q->init_rq_fn = scsi_old_init_rq;
	q->exit_rq_fn = scsi_old_exit_rq;
	q->initialize_rq_fn = scsi_initialize_rq;

	if (blk_init_allocated_queue(q) < 0) {
		blk_cleanup_queue(q);
		return NULL;
	}

	__scsi_init_queue(shost, q);
	blk_queue_flag_set(QUEUE_FLAG_SCSI_PASSTHROUGH, q);
	blk_queue_prep_rq(q, scsi_prep_fn);
	blk_queue_unprep_rq(q, scsi_unprep_fn);
	blk_queue_softirq_done(q, scsi_softirq_done);
	blk_queue_rq_timed_out(q, scsi_times_out);
	blk_queue_lld_busy(q, scsi_lld_busy);
	return q;
}