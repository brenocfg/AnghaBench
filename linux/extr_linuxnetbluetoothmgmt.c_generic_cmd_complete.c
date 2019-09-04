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
typedef  int /*<<< orphan*/  u8 ;
struct mgmt_pending_cmd {int /*<<< orphan*/  param_len; int /*<<< orphan*/  param; int /*<<< orphan*/  opcode; int /*<<< orphan*/  index; int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int mgmt_cmd_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int generic_cmd_complete(struct mgmt_pending_cmd *cmd, u8 status)
{
	return mgmt_cmd_complete(cmd->sk, cmd->index, cmd->opcode, status,
				 cmd->param, cmd->param_len);
}