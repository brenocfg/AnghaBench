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
struct pcxhr_rmh {int /*<<< orphan*/ * cmd; } ;
struct pcxhr_mgr {TYPE_1__* pci; int /*<<< orphan*/  granularity; int /*<<< orphan*/  dsp_time_last; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SET_TIMER_INTERRUPT ; 
 int /*<<< orphan*/  PCXHR_DSP_TIME_INVALID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pcxhr_init_rmh (struct pcxhr_rmh*,int /*<<< orphan*/ ) ; 
 int pcxhr_send_msg (struct pcxhr_mgr*,struct pcxhr_rmh*) ; 

__attribute__((used)) static int pcxhr_hardware_timer(struct pcxhr_mgr *mgr, int start)
{
	struct pcxhr_rmh rmh;
	int err;

	pcxhr_init_rmh(&rmh, CMD_SET_TIMER_INTERRUPT);
	if (start) {
		/* last dsp time invalid */
		mgr->dsp_time_last = PCXHR_DSP_TIME_INVALID;
		rmh.cmd[0] |= mgr->granularity;
	}
	err = pcxhr_send_msg(mgr, &rmh);
	if (err < 0)
		dev_err(&mgr->pci->dev, "error pcxhr_hardware_timer err(%x)\n",
			   err);
	return err;
}