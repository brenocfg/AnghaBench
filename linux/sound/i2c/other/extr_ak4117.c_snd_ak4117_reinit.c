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
struct ak4117 {unsigned char* regmap; int init; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 unsigned char AK4117_PWN ; 
 size_t AK4117_REG_PWRDN ; 
 unsigned char AK4117_RST ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  reg_write (struct ak4117*,size_t,unsigned char) ; 
 int /*<<< orphan*/  udelay (int) ; 

void snd_ak4117_reinit(struct ak4117 *chip)
{
	unsigned char old = chip->regmap[AK4117_REG_PWRDN], reg;

	del_timer(&chip->timer);
	chip->init = 1;
	/* bring the chip to reset state and powerdown state */
	reg_write(chip, AK4117_REG_PWRDN, 0);
	udelay(200);
	/* release reset, but leave powerdown */
	reg_write(chip, AK4117_REG_PWRDN, (old | AK4117_RST) & ~AK4117_PWN);
	udelay(200);
	for (reg = 1; reg < 5; reg++)
		reg_write(chip, reg, chip->regmap[reg]);
	/* release powerdown, everything is initialized now */
	reg_write(chip, AK4117_REG_PWRDN, old | AK4117_RST | AK4117_PWN);
	chip->init = 0;
	mod_timer(&chip->timer, 1 + jiffies);
}