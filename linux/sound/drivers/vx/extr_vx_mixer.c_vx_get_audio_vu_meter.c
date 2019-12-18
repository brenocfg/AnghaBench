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
struct vx_vu_meter {int saturated; int vu_level; int peak_level; } ;
struct vx_rmh {int LgStat; int* Cmd; int* Stat; } ;
struct vx_core {int chip_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_AUDIO_VU_PIC_METER ; 
 int COMMAND_RECORD_MASK ; 
 int EBUSY ; 
 int VU_METER_CHANNELS ; 
 int VX_STAT_IS_STALE ; 
 int /*<<< orphan*/  vx_init_rmh (struct vx_rmh*,int /*<<< orphan*/ ) ; 
 int vx_send_msg (struct vx_core*,struct vx_rmh*) ; 

__attribute__((used)) static int vx_get_audio_vu_meter(struct vx_core *chip, int audio, int capture, struct vx_vu_meter *info)
{
	struct vx_rmh rmh;
	int i, err;

	if (chip->chip_status & VX_STAT_IS_STALE)
		return -EBUSY;

	vx_init_rmh(&rmh, CMD_AUDIO_VU_PIC_METER);
	rmh.LgStat += 2 * VU_METER_CHANNELS;
	if (capture)
		rmh.Cmd[0] |= COMMAND_RECORD_MASK;
    
        /* Add Audio IO mask */
	rmh.Cmd[1] = 0;
	for (i = 0; i < VU_METER_CHANNELS; i++)
		rmh.Cmd[1] |= 1 << (audio + i);
	err = vx_send_msg(chip, &rmh);
	if (err < 0)
		return err;
	/* Read response */
	for (i = 0; i < 2 * VU_METER_CHANNELS; i +=2) {
		info->saturated = (rmh.Stat[0] & (1 << (audio + i))) ? 1 : 0;
		info->vu_level = rmh.Stat[i + 1];
		info->peak_level = rmh.Stat[i + 2];
		info++;
	}
	return 0;
}