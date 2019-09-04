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
typedef  int u8 ;
struct fusb302_chip {scalar_t__ cc_polarity; int pull_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSB_REG_SWITCHES0 ; 
 int FUSB_REG_SWITCHES0_CC1_PD_EN ; 
 int FUSB_REG_SWITCHES0_CC1_PU_EN ; 
 int FUSB_REG_SWITCHES0_CC2_PD_EN ; 
 int FUSB_REG_SWITCHES0_CC2_PU_EN ; 
 scalar_t__ TYPEC_POLARITY_CC1 ; 
 int fusb302_i2c_mask_write (struct fusb302_chip*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int fusb302_set_cc_pull(struct fusb302_chip *chip,
			       bool pull_up, bool pull_down)
{
	int ret = 0;
	u8 data = 0x00;
	u8 mask = FUSB_REG_SWITCHES0_CC1_PU_EN |
		  FUSB_REG_SWITCHES0_CC2_PU_EN |
		  FUSB_REG_SWITCHES0_CC1_PD_EN |
		  FUSB_REG_SWITCHES0_CC2_PD_EN;

	if (pull_up)
		data |= (chip->cc_polarity == TYPEC_POLARITY_CC1) ?
			FUSB_REG_SWITCHES0_CC1_PU_EN :
			FUSB_REG_SWITCHES0_CC2_PU_EN;
	if (pull_down)
		data |= FUSB_REG_SWITCHES0_CC1_PD_EN |
			FUSB_REG_SWITCHES0_CC2_PD_EN;
	ret = fusb302_i2c_mask_write(chip, FUSB_REG_SWITCHES0,
				     mask, data);
	if (ret < 0)
		return ret;
	chip->pull_up = pull_up;

	return ret;
}