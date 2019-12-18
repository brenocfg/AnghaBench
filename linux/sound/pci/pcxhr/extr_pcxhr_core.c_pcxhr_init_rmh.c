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
struct pcxhr_rmh {int cmd_len; int cmd_idx; int /*<<< orphan*/  dsp_stat; int /*<<< orphan*/  stat_len; int /*<<< orphan*/ * cmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  st_type; int /*<<< orphan*/  st_length; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int CMD_LAST_INDEX ; 
 TYPE_1__* pcxhr_dsp_cmds ; 
 scalar_t__ snd_BUG_ON (int) ; 

void pcxhr_init_rmh(struct pcxhr_rmh *rmh, int cmd)
{
	if (snd_BUG_ON(cmd >= CMD_LAST_INDEX))
		return;
	rmh->cmd[0] = pcxhr_dsp_cmds[cmd].opcode;
	rmh->cmd_len = 1;
	rmh->stat_len = pcxhr_dsp_cmds[cmd].st_length;
	rmh->dsp_stat = pcxhr_dsp_cmds[cmd].st_type;
	rmh->cmd_idx = cmd;
}