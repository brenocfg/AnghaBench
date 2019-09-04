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
struct pcxhr_rmh {int /*<<< orphan*/ * cmd; } ;
struct pcxhr_mgr {int dsp_loaded; int /*<<< orphan*/  is_hr_stereo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ACCESS_IO_WRITE ; 
 int /*<<< orphan*/  IO_NUM_REG_MUTE_OUT ; 
 int PCXHR_FIRMWARE_DSP_EPRM_INDEX ; 
 int PCXHR_FIRMWARE_DSP_MAIN_INDEX ; 
 int PCXHR_FIRMWARE_XLX_COM_INDEX ; 
 int /*<<< orphan*/  REG_CONT_UNMUTE_INPUTS ; 
 int /*<<< orphan*/  pcxhr_init_rmh (struct pcxhr_rmh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcxhr_reset_dsp (struct pcxhr_mgr*) ; 
 int /*<<< orphan*/  pcxhr_reset_xilinx_com (struct pcxhr_mgr*) ; 
 int /*<<< orphan*/  pcxhr_send_msg (struct pcxhr_mgr*,struct pcxhr_rmh*) ; 
 int /*<<< orphan*/  pcxhr_write_io_num_reg_cont (struct pcxhr_mgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void pcxhr_reset_board(struct pcxhr_mgr *mgr)
{
	struct pcxhr_rmh rmh;

	if (mgr->dsp_loaded & (1 << PCXHR_FIRMWARE_DSP_MAIN_INDEX)) {
		/* mute outputs */
	    if (!mgr->is_hr_stereo) {
		/* a read to IO_NUM_REG_MUTE_OUT register unmutes! */
		pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_WRITE);
		rmh.cmd[0] |= IO_NUM_REG_MUTE_OUT;
		pcxhr_send_msg(mgr, &rmh);
		/* mute inputs */
		pcxhr_write_io_num_reg_cont(mgr, REG_CONT_UNMUTE_INPUTS,
					    0, NULL);
	    }
		/* stereo cards mute with reset of dsp */
	}
	/* reset pcxhr dsp */
	if (mgr->dsp_loaded & (1 << PCXHR_FIRMWARE_DSP_EPRM_INDEX))
		pcxhr_reset_dsp(mgr);
	/* reset second xilinx */
	if (mgr->dsp_loaded & (1 << PCXHR_FIRMWARE_XLX_COM_INDEX)) {
		pcxhr_reset_xilinx_com(mgr);
		mgr->dsp_loaded = 1;
	}
	return;
}