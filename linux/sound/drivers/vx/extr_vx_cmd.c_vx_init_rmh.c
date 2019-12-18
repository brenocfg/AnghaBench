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
struct vx_rmh {int /*<<< orphan*/ * Cmd; int /*<<< orphan*/  DspStat; int /*<<< orphan*/  LgStat; int /*<<< orphan*/  LgCmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  opcode; int /*<<< orphan*/  st_type; int /*<<< orphan*/  st_length; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 unsigned int CMD_LAST_INDEX ; 
 scalar_t__ snd_BUG_ON (int) ; 
 TYPE_1__* vx_dsp_cmds ; 

void vx_init_rmh(struct vx_rmh *rmh, unsigned int cmd)
{
	if (snd_BUG_ON(cmd >= CMD_LAST_INDEX))
		return;
	rmh->LgCmd = vx_dsp_cmds[cmd].length;
	rmh->LgStat = vx_dsp_cmds[cmd].st_length;
	rmh->DspStat = vx_dsp_cmds[cmd].st_type;
	rmh->Cmd[0] = vx_dsp_cmds[cmd].opcode;
}