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
struct scsi_host_template {int dummy; } ;
struct iscsi_host {int /*<<< orphan*/  session_removal_wq; scalar_t__ num_sessions; int /*<<< orphan*/  state; int /*<<< orphan*/  lock; int /*<<< orphan*/  workq; int /*<<< orphan*/  workq_name; } ;
struct Scsi_Host {int host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_HOST_SETUP ; 
 int /*<<< orphan*/  create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct Scsi_Host* scsi_host_alloc (struct scsi_host_template*,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 struct iscsi_host* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct Scsi_Host *iscsi_host_alloc(struct scsi_host_template *sht,
				   int dd_data_size, bool xmit_can_sleep)
{
	struct Scsi_Host *shost;
	struct iscsi_host *ihost;

	shost = scsi_host_alloc(sht, sizeof(struct iscsi_host) + dd_data_size);
	if (!shost)
		return NULL;
	ihost = shost_priv(shost);

	if (xmit_can_sleep) {
		snprintf(ihost->workq_name, sizeof(ihost->workq_name),
			"iscsi_q_%d", shost->host_no);
		ihost->workq = create_singlethread_workqueue(ihost->workq_name);
		if (!ihost->workq)
			goto free_host;
	}

	spin_lock_init(&ihost->lock);
	ihost->state = ISCSI_HOST_SETUP;
	ihost->num_sessions = 0;
	init_waitqueue_head(&ihost->session_removal_wq);
	return shost;

free_host:
	scsi_host_put(shost);
	return NULL;
}