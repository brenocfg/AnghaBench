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
typedef  int u32 ;
struct lpc18xx_eeprom_dev {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  LPC18XX_EEPROM_INTSTAT ; 
 int /*<<< orphan*/  LPC18XX_EEPROM_INTSTATCLR ; 
 int /*<<< orphan*/  LPC18XX_EEPROM_INTSTATCLR_PROG_CLR_ST ; 
 int LPC18XX_EEPROM_INTSTAT_END_OF_PROG ; 
 int LPC18XX_EEPROM_PROGRAM_TIME ; 
 int USEC_PER_MSEC ; 
 unsigned long jiffies ; 
 int lpc18xx_eeprom_readl (struct lpc18xx_eeprom_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpc18xx_eeprom_writel (struct lpc18xx_eeprom_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ time_is_after_jiffies (unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int lpc18xx_eeprom_busywait_until_prog(struct lpc18xx_eeprom_dev *eeprom)
{
	unsigned long end;
	u32 val;

	/* Wait until EEPROM program operation has finished */
	end = jiffies + msecs_to_jiffies(LPC18XX_EEPROM_PROGRAM_TIME * 10);

	while (time_is_after_jiffies(end)) {
		val = lpc18xx_eeprom_readl(eeprom, LPC18XX_EEPROM_INTSTAT);

		if (val & LPC18XX_EEPROM_INTSTAT_END_OF_PROG) {
			lpc18xx_eeprom_writel(eeprom, LPC18XX_EEPROM_INTSTATCLR,
					LPC18XX_EEPROM_INTSTATCLR_PROG_CLR_ST);
			return 0;
		}

		usleep_range(LPC18XX_EEPROM_PROGRAM_TIME * USEC_PER_MSEC,
			     (LPC18XX_EEPROM_PROGRAM_TIME + 1) * USEC_PER_MSEC);
	}

	return -ETIMEDOUT;
}