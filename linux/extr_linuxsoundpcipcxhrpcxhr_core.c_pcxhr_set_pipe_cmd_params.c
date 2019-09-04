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
struct pcxhr_rmh {int* cmd; int cmd_len; } ;

/* Variables and functions */
 unsigned int FIELD_SIZE ; 
 unsigned int MASK_DSP_WORD ; 
 unsigned int MASK_FIRST_FIELD ; 
 int /*<<< orphan*/  snd_BUG_ON (int) ; 

void pcxhr_set_pipe_cmd_params(struct pcxhr_rmh *rmh, int capture,
			       unsigned int param1, unsigned int param2,
			       unsigned int param3)
{
	snd_BUG_ON(param1 > MASK_FIRST_FIELD);
	if (capture)
		rmh->cmd[0] |= 0x800;		/* COMMAND_RECORD_MASK */
	if (param1)
		rmh->cmd[0] |= (param1 << FIELD_SIZE);
	if (param2) {
		snd_BUG_ON(param2 > MASK_FIRST_FIELD);
		rmh->cmd[0] |= param2;
	}
	if(param3) {
		snd_BUG_ON(param3 > MASK_DSP_WORD);
		rmh->cmd[1] = param3;
		rmh->cmd_len = 2;
	}
}