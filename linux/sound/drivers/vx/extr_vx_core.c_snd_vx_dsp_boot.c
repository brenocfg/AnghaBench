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
struct vx_core {int chip_status; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int VX_STAT_DEVICE_INIT ; 
 int /*<<< orphan*/  msleep (int) ; 
 int snd_vx_load_boot_image (struct vx_core*,struct firmware const*) ; 
 int /*<<< orphan*/  vx_reset_board (struct vx_core*,int) ; 
 int /*<<< orphan*/  vx_validate_irq (struct vx_core*,int /*<<< orphan*/ ) ; 

int snd_vx_dsp_boot(struct vx_core *chip, const struct firmware *boot)
{
	int err;
	int cold_reset = !(chip->chip_status & VX_STAT_DEVICE_INIT);

	vx_reset_board(chip, cold_reset);
	vx_validate_irq(chip, 0);

	if ((err = snd_vx_load_boot_image(chip, boot)) < 0)
		return err;
	msleep(10);

	return 0;
}