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
struct snd_pcxhr {int* analog_capture_volume; int* analog_playback_volume; int chip_idx; TYPE_1__* card; int /*<<< orphan*/  mgr; scalar_t__* analog_playback_active; } ;
struct pcxhr_rmh {int* cmd; int cmd_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ACCESS_IO_WRITE ; 
 int EINVAL ; 
 int IO_NUM_REG_IN_ANA_LEVEL ; 
 int IO_NUM_REG_OUT_ANA_LEVEL ; 
 int PCXHR_LINE_PLAYBACK_LEVEL_MAX ; 
 int PCXHR_LINE_PLAYBACK_LEVEL_MIN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  pcxhr_init_rmh (struct pcxhr_rmh*,int /*<<< orphan*/ ) ; 
 int pcxhr_send_msg (int /*<<< orphan*/ ,struct pcxhr_rmh*) ; 

__attribute__((used)) static int pcxhr_update_analog_audio_level(struct snd_pcxhr *chip,
					   int is_capture, int channel)
{
	int err, vol;
	struct pcxhr_rmh rmh;

	pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_WRITE);
	if (is_capture) {
		rmh.cmd[0] |= IO_NUM_REG_IN_ANA_LEVEL;
		rmh.cmd[2] = chip->analog_capture_volume[channel];
	} else {
		rmh.cmd[0] |= IO_NUM_REG_OUT_ANA_LEVEL;
		if (chip->analog_playback_active[channel])
			vol = chip->analog_playback_volume[channel];
		else
			vol = PCXHR_LINE_PLAYBACK_LEVEL_MIN;
		/* playback analog levels are inversed */
		rmh.cmd[2] = PCXHR_LINE_PLAYBACK_LEVEL_MAX - vol;
	}
	rmh.cmd[1]  = 1 << ((2 * chip->chip_idx) + channel);	/* audio mask */
	rmh.cmd_len = 3;
	err = pcxhr_send_msg(chip->mgr, &rmh);
	if (err < 0) {
		dev_dbg(chip->card->dev,
			"error update_analog_audio_level card(%d)"
			   " is_capture(%d) err(%x)\n",
			   chip->chip_idx, is_capture, err);
		return -EINVAL;
	}
	return 0;
}