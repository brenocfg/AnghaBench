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
struct ibmvfc_host {scalar_t__ action; int delay_init; scalar_t__ init_retries; int /*<<< orphan*/  work_wait_q; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBMVFC_HOST_ACTION_INIT ; 
 scalar_t__ IBMVFC_HOST_ACTION_INIT_WAIT ; 
 int /*<<< orphan*/  IBMVFC_HOST_OFFLINE ; 
 scalar_t__ IBMVFC_MAX_HOST_INIT_RETRIES ; 
 int /*<<< orphan*/  __ibmvfc_reset_host (struct ibmvfc_host*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ibmvfc_link_down (struct ibmvfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_set_host_action (struct ibmvfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ibmvfc_retry_host_init(struct ibmvfc_host *vhost)
{
	int retry = 0;

	if (vhost->action == IBMVFC_HOST_ACTION_INIT_WAIT) {
		vhost->delay_init = 1;
		if (++vhost->init_retries > IBMVFC_MAX_HOST_INIT_RETRIES) {
			dev_err(vhost->dev,
				"Host initialization retries exceeded. Taking adapter offline\n");
			ibmvfc_link_down(vhost, IBMVFC_HOST_OFFLINE);
		} else if (vhost->init_retries == IBMVFC_MAX_HOST_INIT_RETRIES)
			__ibmvfc_reset_host(vhost);
		else {
			ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_INIT);
			retry = 1;
		}
	}

	wake_up(&vhost->work_wait_q);
	return retry;
}