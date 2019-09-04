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
#define  VX_AUDIO_SRC_DIGITAL 128 
 int /*<<< orphan*/  VX_CFG_DATAIN_SEL_MASK ; 
 struct snd_vx222* to_vx222 (struct vx_core*) ; 
 int /*<<< orphan*/  vx_outl (struct snd_vx222*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vx2_change_audio_source(struct vx_core *_chip, int src)
{
	struct snd_vx222 *chip = to_vx222(_chip);

	switch (src) {
	case VX_AUDIO_SRC_DIGITAL:
		chip->regCFG |= VX_CFG_DATAIN_SEL_MASK;
		break;
	default:
		chip->regCFG &= ~VX_CFG_DATAIN_SEL_MASK;
		break;
	}
	vx_outl(chip, CFG, chip->regCFG);
}