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

/* Variables and functions */
 int /*<<< orphan*/  CMD_BUFLEN ; 
#define  CTRL_N 129 
#define  CTRL_P 128 
 scalar_t__ KDB_CMD_HISTORY_COUNT ; 
 int /*<<< orphan*/  cmd_cur ; 
 scalar_t__ cmd_head ; 
 int /*<<< orphan*/ * cmd_hist ; 
 scalar_t__ cmd_tail ; 
 scalar_t__ cmdptr ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_ctrl_cmd(char *cmd)
{
#define CTRL_P	16
#define CTRL_N	14

	/* initial situation */
	if (cmd_head == cmd_tail)
		return 0;
	switch (*cmd) {
	case CTRL_P:
		if (cmdptr != cmd_tail)
			cmdptr = (cmdptr-1) % KDB_CMD_HISTORY_COUNT;
		strncpy(cmd_cur, cmd_hist[cmdptr], CMD_BUFLEN);
		return 1;
	case CTRL_N:
		if (cmdptr != cmd_head)
			cmdptr = (cmdptr+1) % KDB_CMD_HISTORY_COUNT;
		strncpy(cmd_cur, cmd_hist[cmdptr], CMD_BUFLEN);
		return 1;
	}
	return 0;
}