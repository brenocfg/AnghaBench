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
struct snd_vx222 {int /*<<< orphan*/  regCFG; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG ; 
 int INTERNAL_QUARTZ ; 
 int /*<<< orphan*/  VX_CFG_CLOCKIN_SEL_MASK ; 
 struct snd_vx222* to_vx222 (struct vx_core*) ; 
 int /*<<< orphan*/  vx_outl (struct snd_vx222*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vx2_set_clock_source(struct vx_core *_chip, int source)
{
	struct snd_vx222 *chip = to_vx222(_chip);

	if (source == INTERNAL_QUARTZ)
		chip->regCFG &= ~VX_CFG_CLOCKIN_SEL_MASK;
	else
		chip->regCFG |= VX_CFG_CLOCKIN_SEL_MASK;
	vx_outl(chip, CFG, chip->regCFG);
}