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
struct cmipci {int chip_version; int can_ac3_sw; int can_ac3_hw; int max_channels; int can_96k; int can_multi_ch; int /*<<< orphan*/  do_soft_ac3; } ;

/* Variables and functions */
#define  CM_CHIP_037 128 
 unsigned int CM_CHIP_039 ; 
 unsigned int CM_CHIP_039_6CH ; 
 unsigned int CM_CHIP_8768 ; 
 unsigned int CM_CHIP_MASK1 ; 
 unsigned int CM_CHIP_MASK2 ; 
 int /*<<< orphan*/  CM_REG_CHFORMAT ; 
 int /*<<< orphan*/  CM_REG_INT_HLDCLR ; 
 unsigned int snd_cmipci_read (struct cmipci*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void query_chip(struct cmipci *cm)
{
	unsigned int detect;

	/* check reg 0Ch, bit 24-31 */
	detect = snd_cmipci_read(cm, CM_REG_INT_HLDCLR) & CM_CHIP_MASK2;
	if (! detect) {
		/* check reg 08h, bit 24-28 */
		detect = snd_cmipci_read(cm, CM_REG_CHFORMAT) & CM_CHIP_MASK1;
		switch (detect) {
		case 0:
			cm->chip_version = 33;
			if (cm->do_soft_ac3)
				cm->can_ac3_sw = 1;
			else
				cm->can_ac3_hw = 1;
			break;
		case CM_CHIP_037:
			cm->chip_version = 37;
			cm->can_ac3_hw = 1;
			break;
		default:
			cm->chip_version = 39;
			cm->can_ac3_hw = 1;
			break;
		}
		cm->max_channels = 2;
	} else {
		if (detect & CM_CHIP_039) {
			cm->chip_version = 39;
			if (detect & CM_CHIP_039_6CH) /* 4 or 6 channels */
				cm->max_channels = 6;
			else
				cm->max_channels = 4;
		} else if (detect & CM_CHIP_8768) {
			cm->chip_version = 68;
			cm->max_channels = 8;
			cm->can_96k = 1;
		} else {
			cm->chip_version = 55;
			cm->max_channels = 6;
			cm->can_96k = 1;
		}
		cm->can_ac3_hw = 1;
		cm->can_multi_ch = 1;
	}
}