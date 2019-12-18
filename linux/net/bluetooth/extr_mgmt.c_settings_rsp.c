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
struct mgmt_pending_cmd {int /*<<< orphan*/ * sk; int /*<<< orphan*/  list; int /*<<< orphan*/  opcode; } ;
struct cmd_lookup {int /*<<< orphan*/ * sk; int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgmt_pending_free (struct mgmt_pending_cmd*) ; 
 int /*<<< orphan*/  send_settings_rsp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_hold (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void settings_rsp(struct mgmt_pending_cmd *cmd, void *data)
{
	struct cmd_lookup *match = data;

	send_settings_rsp(cmd->sk, cmd->opcode, match->hdev);

	list_del(&cmd->list);

	if (match->sk == NULL) {
		match->sk = cmd->sk;
		sock_hold(match->sk);
	}

	mgmt_pending_free(cmd);
}