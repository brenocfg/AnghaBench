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
struct regmap {int dummy; } ;

/* Variables and functions */
 int SEC_TO_WDTTIMSET_PRD (unsigned int) ; 
 int /*<<< orphan*/  WDTCTRL ; 
 int WDTCTRL_CLEAR ; 
 int WDTCTRL_ENABLE ; 
 unsigned int WDTCTRL_STATUS ; 
 int /*<<< orphan*/  WDTST_TIMEOUT ; 
 int /*<<< orphan*/  WDTTIMSET ; 
 int regmap_read_poll_timeout (struct regmap*,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __uniphier_watchdog_start(struct regmap *regmap, unsigned int sec)
{
	unsigned int val;
	int ret;

	ret = regmap_read_poll_timeout(regmap, WDTCTRL, val,
				       !(val & WDTCTRL_STATUS),
				       0, WDTST_TIMEOUT);
	if (ret)
		return ret;

	/* Setup period */
	ret = regmap_write(regmap, WDTTIMSET,
			   SEC_TO_WDTTIMSET_PRD(sec));
	if (ret)
		return ret;

	/* Enable and clear watchdog */
	ret = regmap_write(regmap, WDTCTRL, WDTCTRL_ENABLE | WDTCTRL_CLEAR);
	if (!ret)
		/*
		 * As SoC specification, after clear counter,
		 * it needs to wait until counter status is 1.
		 */
		ret = regmap_read_poll_timeout(regmap, WDTCTRL, val,
					       (val & WDTCTRL_STATUS),
					       0, WDTST_TIMEOUT);

	return ret;
}