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

/* Variables and functions */
 int /*<<< orphan*/  CODEC2 ; 
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  HIFREQ ; 
 int /*<<< orphan*/  LOFREQ ; 
 int /*<<< orphan*/  VX_DATA_CODEC_MASK ; 
 int /*<<< orphan*/  vx_inb (struct vx_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vx_outb (struct vx_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vxp_write_codec_reg(struct vx_core *chip, int codec, unsigned int data)
{
	int i;

	/* Activate access to the corresponding codec register */
	if (! codec)
		vx_inb(chip, LOFREQ);
	else
		vx_inb(chip, CODEC2);
		
	/* We have to send 24 bits (3 x 8 bits). Start with most signif. Bit */
	for (i = 0; i < 24; i++, data <<= 1)
		vx_outb(chip, DATA, ((data & 0x800000) ? VX_DATA_CODEC_MASK : 0));
	
	/* Terminate access to codec registers */
	vx_inb(chip, HIFREQ);
}