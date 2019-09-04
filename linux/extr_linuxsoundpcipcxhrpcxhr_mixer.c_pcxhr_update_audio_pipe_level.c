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
struct pcxhr_pipe {int first_audio; } ;
struct snd_pcxhr {int* digital_capture_volume; int* monitoring_volume; scalar_t__* monitoring_active; int /*<<< orphan*/  chip_idx; TYPE_1__* card; int /*<<< orphan*/  mgr; struct pcxhr_pipe playback_pipe; struct pcxhr_pipe* capture_pipe; } ;
struct pcxhr_rmh {int* cmd; int cmd_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AUDIO_IO_HAS_MUTE_MONITOR_1 ; 
 int /*<<< orphan*/  CMD_AUDIO_LEVEL_ADJUST ; 
 int EINVAL ; 
 int VALID_AUDIO_IO_DIGITAL_LEVEL ; 
 int VALID_AUDIO_IO_MONITOR_LEVEL ; 
 int VALID_AUDIO_IO_MUTE_MONITOR_1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcxhr_init_rmh (struct pcxhr_rmh*,int /*<<< orphan*/ ) ; 
 int pcxhr_send_msg (int /*<<< orphan*/ ,struct pcxhr_rmh*) ; 
 int /*<<< orphan*/  pcxhr_set_pipe_cmd_params (struct pcxhr_rmh*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pcxhr_update_audio_pipe_level(struct snd_pcxhr *chip,
					 int capture, int channel)
{
	int err;
	struct pcxhr_rmh rmh;
	struct pcxhr_pipe *pipe;

	if (capture)
		pipe = &chip->capture_pipe[0];
	else
		pipe = &chip->playback_pipe;

	pcxhr_init_rmh(&rmh, CMD_AUDIO_LEVEL_ADJUST);
	/* add channel mask */
	pcxhr_set_pipe_cmd_params(&rmh, capture, 0, 0,
				  1 << (channel + pipe->first_audio));
	/* TODO : if mask (3 << pipe->first_audio) is used, left and right
	 * channel will be programmed to the same params */
	if (capture) {
		rmh.cmd[0] |= VALID_AUDIO_IO_DIGITAL_LEVEL;
		/* VALID_AUDIO_IO_MUTE_LEVEL not yet handled
		 * (capture pipe level) */
		rmh.cmd[2] = chip->digital_capture_volume[channel];
	} else {
		rmh.cmd[0] |=	VALID_AUDIO_IO_MONITOR_LEVEL |
				VALID_AUDIO_IO_MUTE_MONITOR_1;
		/* VALID_AUDIO_IO_DIGITAL_LEVEL and VALID_AUDIO_IO_MUTE_LEVEL
		 * not yet handled (playback pipe level)
		 */
		rmh.cmd[2] = chip->monitoring_volume[channel] << 10;
		if (chip->monitoring_active[channel] == 0)
			rmh.cmd[2] |= AUDIO_IO_HAS_MUTE_MONITOR_1;
	}
	rmh.cmd_len = 3;

	err = pcxhr_send_msg(chip->mgr, &rmh);
	if (err < 0) {
		dev_dbg(chip->card->dev,
			"error update_audio_level(%d) err=%x\n",
			   chip->chip_idx, err);
		return -EINVAL;
	}
	return 0;
}