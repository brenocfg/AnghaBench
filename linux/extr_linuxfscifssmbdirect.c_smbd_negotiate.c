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
struct TYPE_2__ {int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct smbd_response {TYPE_1__ sge; int /*<<< orphan*/  type; } ;
struct smbd_connection {int negotiate_done; int /*<<< orphan*/  negotiate_completion; } ;

/* Variables and functions */
 int EINTR ; 
 int ENOTCONN ; 
 int ERESTARTSYS ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  SMBD_NEGOTIATE_RESP ; 
 int SMBD_NEGOTIATE_TIMEOUT ; 
 struct smbd_response* get_receive_buffer (struct smbd_connection*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_rdma_event (int /*<<< orphan*/ ,char*,int,...) ; 
 int smbd_post_recv (struct smbd_connection*,struct smbd_response*) ; 
 int smbd_post_send_negotiate_req (struct smbd_connection*) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int smbd_negotiate(struct smbd_connection *info)
{
	int rc;
	struct smbd_response *response = get_receive_buffer(info);

	response->type = SMBD_NEGOTIATE_RESP;
	rc = smbd_post_recv(info, response);
	log_rdma_event(INFO,
		"smbd_post_recv rc=%d iov.addr=%llx iov.length=%x "
		"iov.lkey=%x\n",
		rc, response->sge.addr,
		response->sge.length, response->sge.lkey);
	if (rc)
		return rc;

	init_completion(&info->negotiate_completion);
	info->negotiate_done = false;
	rc = smbd_post_send_negotiate_req(info);
	if (rc)
		return rc;

	rc = wait_for_completion_interruptible_timeout(
		&info->negotiate_completion, SMBD_NEGOTIATE_TIMEOUT * HZ);
	log_rdma_event(INFO, "wait_for_completion_timeout rc=%d\n", rc);

	if (info->negotiate_done)
		return 0;

	if (rc == 0)
		rc = -ETIMEDOUT;
	else if (rc == -ERESTARTSYS)
		rc = -EINTR;
	else
		rc = -ENOTCONN;

	return rc;
}