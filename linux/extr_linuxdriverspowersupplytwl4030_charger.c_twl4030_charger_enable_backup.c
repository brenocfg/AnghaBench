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

/* Variables and functions */
 int TWL4030_BBCHEN ; 
 int TWL4030_BBISEL_1000uA ; 
 int TWL4030_BBISEL_150uA ; 
 int TWL4030_BBISEL_25uA ; 
 int TWL4030_BBISEL_500uA ; 
 int TWL4030_BBISEL_MASK ; 
 int TWL4030_BBSEL_2V5 ; 
 int TWL4030_BBSEL_3V0 ; 
 int TWL4030_BBSEL_3V1 ; 
 int TWL4030_BBSEL_3V2 ; 
 int TWL4030_BBSEL_MASK ; 
 int /*<<< orphan*/  TWL4030_BB_CFG ; 
 int /*<<< orphan*/  TWL_MODULE_PM_RECEIVER ; 
 int twl4030_clear_set (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_charger_enable_backup(int uvolt, int uamp)
{
	int ret;
	u8 flags;

	if (uvolt < 2500000 ||
	    uamp < 25) {
		/* disable charging of backup battery */
		ret = twl4030_clear_set(TWL_MODULE_PM_RECEIVER,
					TWL4030_BBCHEN, 0, TWL4030_BB_CFG);
		return ret;
	}

	flags = TWL4030_BBCHEN;
	if (uvolt >= 3200000)
		flags |= TWL4030_BBSEL_3V2;
	else if (uvolt >= 3100000)
		flags |= TWL4030_BBSEL_3V1;
	else if (uvolt >= 3000000)
		flags |= TWL4030_BBSEL_3V0;
	else
		flags |= TWL4030_BBSEL_2V5;

	if (uamp >= 1000)
		flags |= TWL4030_BBISEL_1000uA;
	else if (uamp >= 500)
		flags |= TWL4030_BBISEL_500uA;
	else if (uamp >= 150)
		flags |= TWL4030_BBISEL_150uA;
	else
		flags |= TWL4030_BBISEL_25uA;

	ret = twl4030_clear_set(TWL_MODULE_PM_RECEIVER,
				TWL4030_BBSEL_MASK | TWL4030_BBISEL_MASK,
				flags,
				TWL4030_BB_CFG);

	return ret;
}