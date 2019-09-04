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
struct ibmvscsi_host_data {int /*<<< orphan*/  host; int /*<<< orphan*/  dev; int /*<<< orphan*/  request_limit; scalar_t__ reenable_crq; int /*<<< orphan*/  queue; scalar_t__ reset_crq; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 int ibmvscsi_reenable_crq_queue (int /*<<< orphan*/ *,struct ibmvscsi_host_data*) ; 
 int ibmvscsi_reset_crq_queue (int /*<<< orphan*/ *,struct ibmvscsi_host_data*) ; 
 int ibmvscsi_send_crq (struct ibmvscsi_host_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_unblock_requests (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  to_vio_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vio_enable_interrupts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ibmvscsi_do_work(struct ibmvscsi_host_data *hostdata)
{
	int rc;
	char *action = "reset";

	if (hostdata->reset_crq) {
		smp_rmb();
		hostdata->reset_crq = 0;

		rc = ibmvscsi_reset_crq_queue(&hostdata->queue, hostdata);
		if (!rc)
			rc = ibmvscsi_send_crq(hostdata, 0xC001000000000000LL, 0);
		vio_enable_interrupts(to_vio_dev(hostdata->dev));
	} else if (hostdata->reenable_crq) {
		smp_rmb();
		action = "enable";
		rc = ibmvscsi_reenable_crq_queue(&hostdata->queue, hostdata);
		hostdata->reenable_crq = 0;
		if (!rc)
			rc = ibmvscsi_send_crq(hostdata, 0xC001000000000000LL, 0);
	} else
		return;

	if (rc) {
		atomic_set(&hostdata->request_limit, -1);
		dev_err(hostdata->dev, "error after %s\n", action);
	}

	scsi_unblock_requests(hostdata->host);
}