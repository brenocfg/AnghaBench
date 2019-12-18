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
struct vx_rmh {int* Cmd; } ;
struct vx_core {int chip_status; } ;
struct vx_audio_level {int level; scalar_t__ monitor_mute; scalar_t__ has_monitor_mute; scalar_t__ mute; scalar_t__ has_mute; scalar_t__ monitor_level; scalar_t__ has_monitor_level; scalar_t__ has_level; } ;

/* Variables and functions */
 unsigned int AUDIO_IO_HAS_MUTE_LEVEL ; 
 int AUDIO_IO_HAS_MUTE_MONITORING_1 ; 
 int /*<<< orphan*/  CMD_AUDIO_LEVEL_ADJUST ; 
 int COMMAND_RECORD_MASK ; 
 int EBUSY ; 
 int VALID_AUDIO_IO_DIGITAL_LEVEL ; 
 int VALID_AUDIO_IO_MONITORING_LEVEL ; 
 unsigned int VALID_AUDIO_IO_MUTE_LEVEL ; 
 int VALID_AUDIO_IO_MUTE_MONITORING_1 ; 
 int VALID_AUDIO_IO_MUTE_MONITORING_2 ; 
 int VX_STAT_IS_STALE ; 
 int /*<<< orphan*/  vx_init_rmh (struct vx_rmh*,int /*<<< orphan*/ ) ; 
 int vx_send_msg (struct vx_core*,struct vx_rmh*) ; 

__attribute__((used)) static int vx_adjust_audio_level(struct vx_core *chip, int audio, int capture,
				 struct vx_audio_level *info)
{
	struct vx_rmh rmh;

	if (chip->chip_status & VX_STAT_IS_STALE)
		return -EBUSY;

        vx_init_rmh(&rmh, CMD_AUDIO_LEVEL_ADJUST);
	if (capture)
		rmh.Cmd[0] |= COMMAND_RECORD_MASK;
	/* Add Audio IO mask */
	rmh.Cmd[1] = 1 << audio;
	rmh.Cmd[2] = 0;
	if (info->has_level) {
		rmh.Cmd[0] |=  VALID_AUDIO_IO_DIGITAL_LEVEL;
		rmh.Cmd[2] |= info->level;
        }
	if (info->has_monitor_level) {
		rmh.Cmd[0] |=  VALID_AUDIO_IO_MONITORING_LEVEL;
		rmh.Cmd[2] |= ((unsigned int)info->monitor_level << 10);
        }
	if (info->has_mute) { 
		rmh.Cmd[0] |= VALID_AUDIO_IO_MUTE_LEVEL;
		if (info->mute)
			rmh.Cmd[2] |= AUDIO_IO_HAS_MUTE_LEVEL;
	}
	if (info->has_monitor_mute) {
		/* validate flag for M2 at least to unmute it */ 
		rmh.Cmd[0] |=  VALID_AUDIO_IO_MUTE_MONITORING_1 | VALID_AUDIO_IO_MUTE_MONITORING_2;
		if (info->monitor_mute)
			rmh.Cmd[2] |= AUDIO_IO_HAS_MUTE_MONITORING_1;
	}

	return vx_send_msg(chip, &rmh);
}