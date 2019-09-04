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
struct sdebug_queued_cmd {struct scsi_cmnd* a_cmnd; } ;
struct sdebug_queue {int /*<<< orphan*/  qc_lock; int /*<<< orphan*/  in_use_bm; struct sdebug_queued_cmd* qc_arr; } ;
struct sdebug_dev_info {int /*<<< orphan*/  num_in_q; } ;
struct sdebug_defer {int aborted; int qc_idx; int sqa_idx; scalar_t__ issuing_cpu; int /*<<< orphan*/  defer_t; } ;
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;TYPE_1__* device; } ;
struct TYPE_2__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int SDEBUG_CANQUEUE ; 
 int /*<<< orphan*/  SDEB_DEFER_NONE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int find_last_bit (int /*<<< orphan*/ ,int) ; 
 scalar_t__ likely (struct sdebug_dev_info*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ raw_smp_processor_id () ; 
 int /*<<< orphan*/  retired_max_queue ; 
 int /*<<< orphan*/  sdebug_completions ; 
 int sdebug_max_queue ; 
 int /*<<< orphan*/  sdebug_miss_cpus ; 
 struct sdebug_queue* sdebug_q_arr ; 
 scalar_t__ sdebug_statistics ; 
 scalar_t__ sdebug_verbose ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void sdebug_q_cmd_complete(struct sdebug_defer *sd_dp)
{
	bool aborted = sd_dp->aborted;
	int qc_idx;
	int retiring = 0;
	unsigned long iflags;
	struct sdebug_queue *sqp;
	struct sdebug_queued_cmd *sqcp;
	struct scsi_cmnd *scp;
	struct sdebug_dev_info *devip;

	sd_dp->defer_t = SDEB_DEFER_NONE;
	if (unlikely(aborted))
		sd_dp->aborted = false;
	qc_idx = sd_dp->qc_idx;
	sqp = sdebug_q_arr + sd_dp->sqa_idx;
	if (sdebug_statistics) {
		atomic_inc(&sdebug_completions);
		if (raw_smp_processor_id() != sd_dp->issuing_cpu)
			atomic_inc(&sdebug_miss_cpus);
	}
	if (unlikely((qc_idx < 0) || (qc_idx >= SDEBUG_CANQUEUE))) {
		pr_err("wild qc_idx=%d\n", qc_idx);
		return;
	}
	spin_lock_irqsave(&sqp->qc_lock, iflags);
	sqcp = &sqp->qc_arr[qc_idx];
	scp = sqcp->a_cmnd;
	if (unlikely(scp == NULL)) {
		spin_unlock_irqrestore(&sqp->qc_lock, iflags);
		pr_err("scp is NULL, sqa_idx=%d, qc_idx=%d\n",
		       sd_dp->sqa_idx, qc_idx);
		return;
	}
	devip = (struct sdebug_dev_info *)scp->device->hostdata;
	if (likely(devip))
		atomic_dec(&devip->num_in_q);
	else
		pr_err("devip=NULL\n");
	if (unlikely(atomic_read(&retired_max_queue) > 0))
		retiring = 1;

	sqcp->a_cmnd = NULL;
	if (unlikely(!test_and_clear_bit(qc_idx, sqp->in_use_bm))) {
		spin_unlock_irqrestore(&sqp->qc_lock, iflags);
		pr_err("Unexpected completion\n");
		return;
	}

	if (unlikely(retiring)) {	/* user has reduced max_queue */
		int k, retval;

		retval = atomic_read(&retired_max_queue);
		if (qc_idx >= retval) {
			spin_unlock_irqrestore(&sqp->qc_lock, iflags);
			pr_err("index %d too large\n", retval);
			return;
		}
		k = find_last_bit(sqp->in_use_bm, retval);
		if ((k < sdebug_max_queue) || (k == retval))
			atomic_set(&retired_max_queue, 0);
		else
			atomic_set(&retired_max_queue, k + 1);
	}
	spin_unlock_irqrestore(&sqp->qc_lock, iflags);
	if (unlikely(aborted)) {
		if (sdebug_verbose)
			pr_info("bypassing scsi_done() due to aborted cmd\n");
		return;
	}
	scp->scsi_done(scp); /* callback to mid level */
}