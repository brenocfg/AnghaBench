#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcxhr {int chip_idx; int audio_capture_source; TYPE_2__* mgr; } ;
struct pcxhr_rmh {int* cmd; int cmd_len; } ;
struct TYPE_5__ {int capture_chips; TYPE_1__** chip; scalar_t__ board_aes_in_192k; } ;
struct TYPE_4__ {int audio_capture_source; } ;

/* Variables and functions */
 int CHIP_SIG_AND_MAP_SPI ; 
 int /*<<< orphan*/  CMD_ACCESS_IO_WRITE ; 
 int /*<<< orphan*/  CMD_RESYNC_AUDIO_INPUTS ; 
 unsigned int CS8420_01_CS ; 
 unsigned int CS8420_23_CS ; 
 unsigned int CS8420_45_CS ; 
 unsigned int CS8420_67_CS ; 
 int CS8420_CLOCK_SRC_CTL ; 
 int CS8420_DATA_FLOW_CTL ; 
 int EINVAL ; 
 int IO_NUM_REG_CONFIG_SRC ; 
 unsigned int IO_NUM_UER_CHIP_REG ; 
 unsigned int PCXHR_SOURCE_AUDIO01_UER ; 
 unsigned int PCXHR_SOURCE_AUDIO23_UER ; 
 unsigned int PCXHR_SOURCE_AUDIO45_UER ; 
 unsigned int PCXHR_SOURCE_AUDIO67_UER ; 
 int /*<<< orphan*/  pcxhr_init_rmh (struct pcxhr_rmh*,int /*<<< orphan*/ ) ; 
 int pcxhr_send_msg (TYPE_2__*,struct pcxhr_rmh*) ; 
 int /*<<< orphan*/  pcxhr_write_io_num_reg_cont (TYPE_2__*,unsigned int,unsigned int,int*) ; 

__attribute__((used)) static int pcxhr_set_audio_source(struct snd_pcxhr* chip)
{
	struct pcxhr_rmh rmh;
	unsigned int mask, reg;
	unsigned int codec;
	int err, changed;

	switch (chip->chip_idx) {
	case 0 : mask = PCXHR_SOURCE_AUDIO01_UER; codec = CS8420_01_CS; break;
	case 1 : mask = PCXHR_SOURCE_AUDIO23_UER; codec = CS8420_23_CS; break;
	case 2 : mask = PCXHR_SOURCE_AUDIO45_UER; codec = CS8420_45_CS; break;
	case 3 : mask = PCXHR_SOURCE_AUDIO67_UER; codec = CS8420_67_CS; break;
	default: return -EINVAL;
	}
	if (chip->audio_capture_source != 0) {
		reg = mask;	/* audio source from digital plug */
	} else {
		reg = 0;	/* audio source from analog plug */
	}
	/* set the input source */
	pcxhr_write_io_num_reg_cont(chip->mgr, mask, reg, &changed);
	/* resync them (otherwise channel inversion possible) */
	if (changed) {
		pcxhr_init_rmh(&rmh, CMD_RESYNC_AUDIO_INPUTS);
		rmh.cmd[0] |= (1 << chip->chip_idx);
		err = pcxhr_send_msg(chip->mgr, &rmh);
		if (err)
			return err;
	}
	if (chip->mgr->board_aes_in_192k) {
		int i;
		unsigned int src_config = 0xC0;
		/* update all src configs with one call */
		for (i = 0; (i < 4) && (i < chip->mgr->capture_chips); i++) {
			if (chip->mgr->chip[i]->audio_capture_source == 2)
				src_config |= (1 << (3 - i));
		}
		/* set codec SRC on off */
		pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_WRITE);
		rmh.cmd_len = 2;
		rmh.cmd[0] |= IO_NUM_REG_CONFIG_SRC;
		rmh.cmd[1] = src_config;
		err = pcxhr_send_msg(chip->mgr, &rmh);
	} else {
		int use_src = 0;
		if (chip->audio_capture_source == 2)
			use_src = 1;
		/* set codec SRC on off */
		pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_WRITE);
		rmh.cmd_len = 3;
		rmh.cmd[0] |= IO_NUM_UER_CHIP_REG;
		rmh.cmd[1] = codec;
		rmh.cmd[2] = ((CS8420_DATA_FLOW_CTL & CHIP_SIG_AND_MAP_SPI) |
			      (use_src ? 0x41 : 0x54));
		err = pcxhr_send_msg(chip->mgr, &rmh);
		if (err)
			return err;
		rmh.cmd[2] = ((CS8420_CLOCK_SRC_CTL & CHIP_SIG_AND_MAP_SPI) |
			      (use_src ? 0x41 : 0x49));
		err = pcxhr_send_msg(chip->mgr, &rmh);
	}
	return err;
}