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
struct scsi_device {int dummy; } ;
struct alua_queue_data {int /*<<< orphan*/  entry; } ;
struct alua_port_group {int flags; int /*<<< orphan*/  kref; int /*<<< orphan*/  rtpg_work; int /*<<< orphan*/  lock; struct scsi_device* rtpg_sdev; scalar_t__ interval; int /*<<< orphan*/  rtpg_list; } ;

/* Variables and functions */
 int ALUA_PG_RUNNING ; 
 int ALUA_PG_RUN_RTPG ; 
 int ALUA_PG_RUN_STPG ; 
 int /*<<< orphan*/  ALUA_RTPG_DELAY_MSECS ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  kaluad_wq ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_port_group ; 
 scalar_t__ scsi_device_get (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_device_put (struct scsi_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool alua_rtpg_queue(struct alua_port_group *pg,
			    struct scsi_device *sdev,
			    struct alua_queue_data *qdata, bool force)
{
	int start_queue = 0;
	unsigned long flags;
	if (WARN_ON_ONCE(!pg) || scsi_device_get(sdev))
		return false;

	spin_lock_irqsave(&pg->lock, flags);
	if (qdata) {
		list_add_tail(&qdata->entry, &pg->rtpg_list);
		pg->flags |= ALUA_PG_RUN_STPG;
		force = true;
	}
	if (pg->rtpg_sdev == NULL) {
		pg->interval = 0;
		pg->flags |= ALUA_PG_RUN_RTPG;
		kref_get(&pg->kref);
		pg->rtpg_sdev = sdev;
		start_queue = 1;
	} else if (!(pg->flags & ALUA_PG_RUN_RTPG) && force) {
		pg->flags |= ALUA_PG_RUN_RTPG;
		/* Do not queue if the worker is already running */
		if (!(pg->flags & ALUA_PG_RUNNING)) {
			kref_get(&pg->kref);
			start_queue = 1;
		}
	}

	spin_unlock_irqrestore(&pg->lock, flags);

	if (start_queue) {
		if (queue_delayed_work(kaluad_wq, &pg->rtpg_work,
				msecs_to_jiffies(ALUA_RTPG_DELAY_MSECS)))
			sdev = NULL;
		else
			kref_put(&pg->kref, release_port_group);
	}
	if (sdev)
		scsi_device_put(sdev);

	return true;
}