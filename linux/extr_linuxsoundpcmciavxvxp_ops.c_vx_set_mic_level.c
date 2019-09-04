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
struct vx_core {int chip_status; int /*<<< orphan*/  lock; } ;
struct snd_vxpocket {int regCDSP; } ;

/* Variables and functions */
 int /*<<< orphan*/  MICRO ; 
 int VXP_CDSP_MIC_SEL_MASK ; 
 int VX_STAT_IS_STALE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_vxpocket* to_vxpocket (struct vx_core*) ; 
 int vx_compute_mic_level (int) ; 
 int /*<<< orphan*/  vx_outb (struct vx_core*,int /*<<< orphan*/ ,int) ; 

void vx_set_mic_level(struct vx_core *chip, int level)
{
	struct snd_vxpocket *pchip = to_vxpocket(chip);

	if (chip->chip_status & VX_STAT_IS_STALE)
		return;

	mutex_lock(&chip->lock);
	if (pchip->regCDSP & VXP_CDSP_MIC_SEL_MASK) {
		level = vx_compute_mic_level(level);
		vx_outb(chip, MICRO, level);
	}
	mutex_unlock(&chip->lock);
}