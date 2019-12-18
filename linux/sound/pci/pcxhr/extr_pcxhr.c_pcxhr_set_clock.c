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
struct pcxhr_mgr {scalar_t__ is_hr_stereo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_MODIFY_CLOCK ; 
 unsigned int PCXHR_IRQ_TIMER_FREQ ; 
 int PCXHR_IRQ_TIMER_PERIOD ; 
 int PCXHR_MODIFY_CLOCK_S_BIT ; 
 int hr222_sub_set_clock (struct pcxhr_mgr*,unsigned int,int*) ; 
 int /*<<< orphan*/  pcxhr_init_rmh (struct pcxhr_rmh*,int /*<<< orphan*/ ) ; 
 int pcxhr_send_msg (struct pcxhr_mgr*,struct pcxhr_rmh*) ; 
 int pcxhr_sub_set_clock (struct pcxhr_mgr*,unsigned int,int*) ; 

int pcxhr_set_clock(struct pcxhr_mgr *mgr, unsigned int rate)
{
	struct pcxhr_rmh rmh;
	int err, changed;

	if (rate == 0)
		return 0; /* nothing to do */

	if (mgr->is_hr_stereo)
		err = hr222_sub_set_clock(mgr, rate, &changed);
	else
		err = pcxhr_sub_set_clock(mgr, rate, &changed);

	if (err)
		return err;

	if (changed) {
		pcxhr_init_rmh(&rmh, CMD_MODIFY_CLOCK);
		rmh.cmd[0] |= PCXHR_MODIFY_CLOCK_S_BIT; /* resync fifos  */
		if (rate < PCXHR_IRQ_TIMER_FREQ)
			rmh.cmd[1] = PCXHR_IRQ_TIMER_PERIOD;
		else
			rmh.cmd[1] = PCXHR_IRQ_TIMER_PERIOD * 2;
		rmh.cmd[2] = rate;
		rmh.cmd_len = 3;
		err = pcxhr_send_msg(mgr, &rmh);
		if (err)
			return err;
	}
	return 0;
}