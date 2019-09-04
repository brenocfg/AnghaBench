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
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  HIFREQ ; 
 int /*<<< orphan*/  RUER ; 
 int /*<<< orphan*/  VX_DATA_CODEC_MASK ; 
 int /*<<< orphan*/  vx_inl (struct vx_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vx_outl (struct vx_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vx2_old_write_codec_bit(struct vx_core *chip, int codec, unsigned int data)
{
	int i;

	/* activate access to codec registers */
	vx_inl(chip, HIFREQ);

	for (i = 0; i < 24; i++, data <<= 1)
		vx_outl(chip, DATA, ((data & 0x800000) ? VX_DATA_CODEC_MASK : 0));

	/* Terminate access to codec registers */
	vx_inl(chip, RUER);
}