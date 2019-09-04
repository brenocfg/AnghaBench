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
struct smbd_connection {scalar_t__ transport_status; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  wait_destroy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 scalar_t__ SMBD_DESTROYED ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct smbd_connection*) ; 
 int /*<<< orphan*/  log_rdma_event (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  smbd_disconnect_rdma_connection (struct smbd_connection*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void smbd_destroy(struct smbd_connection *info)
{
	log_rdma_event(INFO, "destroying rdma session\n");

	/* Kick off the disconnection process */
	smbd_disconnect_rdma_connection(info);

	log_rdma_event(INFO, "wait for transport being destroyed\n");
	wait_event(info->wait_destroy,
		info->transport_status == SMBD_DESTROYED);

	destroy_workqueue(info->workqueue);
	kfree(info);
}