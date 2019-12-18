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
struct mgmt_pending_cmd {struct mgmt_pending_cmd* param; int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mgmt_pending_cmd*) ; 
 int /*<<< orphan*/  sock_put (int /*<<< orphan*/ ) ; 

void mgmt_pending_free(struct mgmt_pending_cmd *cmd)
{
	sock_put(cmd->sk);
	kfree(cmd->param);
	kfree(cmd);
}