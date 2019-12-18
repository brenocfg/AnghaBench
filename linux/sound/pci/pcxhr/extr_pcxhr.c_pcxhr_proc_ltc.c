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
struct snd_pcxhr {struct pcxhr_mgr* mgr; } ;
struct snd_info_entry {struct snd_pcxhr* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct pcxhr_rmh {int* stat; int /*<<< orphan*/ * cmd; } ;
struct pcxhr_mgr {int dsp_loaded; int capture_ltc; scalar_t__ is_hr_stereo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GET_TIME_CODE ; 
 int /*<<< orphan*/  CMD_MANAGE_SIGNAL ; 
 int /*<<< orphan*/  MANAGE_SIGNAL_TIME_CODE ; 
 int PCXHR_FIRMWARE_DSP_MAIN_INDEX ; 
 int /*<<< orphan*/  REG_CONT_VALSMPTE ; 
 int TIME_CODE_VALID_MASK ; 
 int /*<<< orphan*/  hr222_manage_timecode (struct pcxhr_mgr*,int) ; 
 int /*<<< orphan*/  pcxhr_init_rmh (struct pcxhr_rmh*,int /*<<< orphan*/ ) ; 
 int pcxhr_send_msg (struct pcxhr_mgr*,struct pcxhr_rmh*) ; 
 int /*<<< orphan*/  pcxhr_write_io_num_reg_cont (struct pcxhr_mgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void pcxhr_proc_ltc(struct snd_info_entry *entry,
			   struct snd_info_buffer *buffer)
{
	struct snd_pcxhr *chip = entry->private_data;
	struct pcxhr_mgr *mgr = chip->mgr;
	struct pcxhr_rmh rmh;
	unsigned int ltcHrs, ltcMin, ltcSec, ltcFrm;
	int err;
	/* commands available when embedded DSP is running */
	if (!(mgr->dsp_loaded & (1 << PCXHR_FIRMWARE_DSP_MAIN_INDEX))) {
		snd_iprintf(buffer, "no firmware loaded\n");
		return;
	}
	if (!mgr->capture_ltc) {
		pcxhr_init_rmh(&rmh, CMD_MANAGE_SIGNAL);
		rmh.cmd[0] |= MANAGE_SIGNAL_TIME_CODE;
		err = pcxhr_send_msg(mgr, &rmh);
		if (err) {
			snd_iprintf(buffer, "ltc not activated (%d)\n", err);
			return;
		}
		if (mgr->is_hr_stereo)
			hr222_manage_timecode(mgr, 1);
		else
			pcxhr_write_io_num_reg_cont(mgr, REG_CONT_VALSMPTE,
						    REG_CONT_VALSMPTE, NULL);
		mgr->capture_ltc = 1;
	}
	pcxhr_init_rmh(&rmh, CMD_GET_TIME_CODE);
	err = pcxhr_send_msg(mgr, &rmh);
	if (err) {
		snd_iprintf(buffer, "ltc read error (err=%d)\n", err);
		return ;
	}
	ltcHrs = 10*((rmh.stat[0] >> 8) & 0x3) + (rmh.stat[0] & 0xf);
	ltcMin = 10*((rmh.stat[1] >> 16) & 0x7) + ((rmh.stat[1] >> 8) & 0xf);
	ltcSec = 10*(rmh.stat[1] & 0x7) + ((rmh.stat[2] >> 16) & 0xf);
	ltcFrm = 10*((rmh.stat[2] >> 8) & 0x3) + (rmh.stat[2] & 0xf);

	snd_iprintf(buffer, "timecode: %02u:%02u:%02u-%02u\n",
			    ltcHrs, ltcMin, ltcSec, ltcFrm);
	snd_iprintf(buffer, "raw: 0x%04x%06x%06x\n", rmh.stat[0] & 0x00ffff,
			    rmh.stat[1] & 0xffffff, rmh.stat[2] & 0xffffff);
	/*snd_iprintf(buffer, "dsp ref time: 0x%06x%06x\n",
			    rmh.stat[3] & 0xffffff, rmh.stat[4] & 0xffffff);*/
	if (!(rmh.stat[0] & TIME_CODE_VALID_MASK)) {
		snd_iprintf(buffer, "warning: linear timecode not valid\n");
	}
}