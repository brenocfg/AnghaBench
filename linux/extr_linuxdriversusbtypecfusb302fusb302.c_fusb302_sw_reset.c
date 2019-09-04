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
struct fusb302_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSB_REG_RESET ; 
 int /*<<< orphan*/  FUSB_REG_RESET_SW_RESET ; 
 int fusb302_i2c_write (struct fusb302_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fusb302_log (struct fusb302_chip*,char*,...) ; 

__attribute__((used)) static int fusb302_sw_reset(struct fusb302_chip *chip)
{
	int ret = 0;

	ret = fusb302_i2c_write(chip, FUSB_REG_RESET,
				FUSB_REG_RESET_SW_RESET);
	if (ret < 0)
		fusb302_log(chip, "cannot sw reset the chip, ret=%d", ret);
	else
		fusb302_log(chip, "sw reset");

	return ret;
}