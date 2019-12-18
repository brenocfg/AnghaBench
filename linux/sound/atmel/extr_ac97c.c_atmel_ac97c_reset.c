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
struct atmel_ac97c {int /*<<< orphan*/  reset_pin; } ;

/* Variables and functions */
 int AC97C_MR_ENA ; 
 int AC97C_MR_WRST ; 
 int /*<<< orphan*/  CAMR ; 
 int /*<<< orphan*/  COMR ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MR ; 
 int /*<<< orphan*/  ac97c_writel (struct atmel_ac97c*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void atmel_ac97c_reset(struct atmel_ac97c *chip)
{
	ac97c_writel(chip, MR,   0);
	ac97c_writel(chip, MR,   AC97C_MR_ENA);
	ac97c_writel(chip, CAMR, 0);
	ac97c_writel(chip, COMR, 0);

	if (!IS_ERR(chip->reset_pin)) {
		gpiod_set_value(chip->reset_pin, 0);
		/* AC97 v2.2 specifications says minimum 1 us. */
		udelay(2);
		gpiod_set_value(chip->reset_pin, 1);
	} else {
		ac97c_writel(chip, MR, AC97C_MR_WRST | AC97C_MR_ENA);
		udelay(2);
		ac97c_writel(chip, MR, AC97C_MR_ENA);
	}
}