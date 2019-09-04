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
struct vx_core {int dummy; } ;
struct snd_vxpocket {int /*<<< orphan*/  regCDSP; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDSP ; 
 int INTERNAL_QUARTZ ; 
 int /*<<< orphan*/  VXP_CDSP_CLOCKIN_SEL_MASK ; 
 struct snd_vxpocket* to_vxpocket (struct vx_core*) ; 
 int /*<<< orphan*/  vx_outb (struct snd_vxpocket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vxp_set_clock_source(struct vx_core *_chip, int source)
{
	struct snd_vxpocket *chip = to_vxpocket(_chip);

	if (source == INTERNAL_QUARTZ)
		chip->regCDSP &= ~VXP_CDSP_CLOCKIN_SEL_MASK;
	else
		chip->regCDSP |= VXP_CDSP_CLOCKIN_SEL_MASK;
	vx_outb(chip, CDSP, chip->regCDSP);
}