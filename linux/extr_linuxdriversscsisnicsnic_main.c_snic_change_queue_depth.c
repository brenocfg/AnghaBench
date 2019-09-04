#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  last_qsz; int /*<<< orphan*/  qsz_rampup; int /*<<< orphan*/  qsz_rampdown; } ;
struct TYPE_4__ {TYPE_1__ misc; } ;
struct snic {TYPE_2__ s_stats; } ;
struct scsi_device {int queue_depth; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNIC_MAX_QUEUE_DEPTH ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int) ; 
 int min_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_change_queue_depth (struct scsi_device*,int) ; 
 struct snic* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static int
snic_change_queue_depth(struct scsi_device *sdev, int qdepth)
{
	struct snic *snic = shost_priv(sdev->host);
	int qsz = 0;

	qsz = min_t(u32, qdepth, SNIC_MAX_QUEUE_DEPTH);
	if (qsz < sdev->queue_depth)
		atomic64_inc(&snic->s_stats.misc.qsz_rampdown);
	else if (qsz > sdev->queue_depth)
		atomic64_inc(&snic->s_stats.misc.qsz_rampup);

	atomic64_set(&snic->s_stats.misc.last_qsz, sdev->queue_depth);

	scsi_change_queue_depth(sdev, qsz);

	return sdev->queue_depth;
}