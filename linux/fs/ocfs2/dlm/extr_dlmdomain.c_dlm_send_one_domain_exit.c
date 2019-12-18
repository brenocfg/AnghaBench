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
typedef  int /*<<< orphan*/  u32 ;
struct dlm_exit_domain {int /*<<< orphan*/  node_idx; } ;
struct dlm_ctxt {int /*<<< orphan*/  name; int /*<<< orphan*/  key; int /*<<< orphan*/  node_num; } ;
typedef  int /*<<< orphan*/  leave_msg ;

/* Variables and functions */
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  memset (struct dlm_exit_domain*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,unsigned int,...) ; 
 int o2net_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_exit_domain*,int,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlm_send_one_domain_exit(struct dlm_ctxt *dlm, u32 msg_type,
				    unsigned int node)
{
	int status;
	struct dlm_exit_domain leave_msg;

	mlog(0, "%s: Sending domain exit message %u to node %u\n", dlm->name,
	     msg_type, node);

	memset(&leave_msg, 0, sizeof(leave_msg));
	leave_msg.node_idx = dlm->node_num;

	status = o2net_send_message(msg_type, dlm->key, &leave_msg,
				    sizeof(leave_msg), node, NULL);
	if (status < 0)
		mlog(ML_ERROR, "Error %d sending domain exit message %u "
		     "to node %u on domain %s\n", status, msg_type, node,
		     dlm->name);

	return status;
}