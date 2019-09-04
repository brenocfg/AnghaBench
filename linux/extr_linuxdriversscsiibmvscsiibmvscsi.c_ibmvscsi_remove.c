#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vio_dev {int /*<<< orphan*/  dev; } ;
struct ibmvscsi_host_data {TYPE_1__* host; int /*<<< orphan*/  host_list; int /*<<< orphan*/  work_thread; int /*<<< orphan*/  queue; int /*<<< orphan*/  pool; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_ERROR ; 
 struct ibmvscsi_host_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibmvscsi_driver_lock ; 
 int /*<<< orphan*/  ibmvscsi_release_crq_queue (int /*<<< orphan*/ *,struct ibmvscsi_host_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max_events ; 
 int /*<<< orphan*/  purge_requests (struct ibmvscsi_host_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_event_pool (int /*<<< orphan*/ *,struct ibmvscsi_host_data*) ; 
 int /*<<< orphan*/  scsi_host_put (TYPE_1__*) ; 
 int /*<<< orphan*/  scsi_remove_host (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  srp_remove_host (TYPE_1__*) ; 
 int /*<<< orphan*/  unmap_persist_bufs (struct ibmvscsi_host_data*) ; 

__attribute__((used)) static int ibmvscsi_remove(struct vio_dev *vdev)
{
	struct ibmvscsi_host_data *hostdata = dev_get_drvdata(&vdev->dev);
	unsigned long flags;

	srp_remove_host(hostdata->host);
	scsi_remove_host(hostdata->host);

	purge_requests(hostdata, DID_ERROR);

	spin_lock_irqsave(hostdata->host->host_lock, flags);
	release_event_pool(&hostdata->pool, hostdata);
	spin_unlock_irqrestore(hostdata->host->host_lock, flags);

	ibmvscsi_release_crq_queue(&hostdata->queue, hostdata,
					max_events);

	kthread_stop(hostdata->work_thread);
	unmap_persist_bufs(hostdata);

	spin_lock(&ibmvscsi_driver_lock);
	list_del(&hostdata->host_list);
	spin_unlock(&ibmvscsi_driver_lock);

	scsi_host_put(hostdata->host);

	return 0;
}