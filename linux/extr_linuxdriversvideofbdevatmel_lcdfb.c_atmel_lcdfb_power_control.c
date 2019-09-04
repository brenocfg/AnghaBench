#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct atmel_lcdfb_pdata {int /*<<< orphan*/  (* atmel_lcdfb_power_control ) (struct atmel_lcdfb_pdata*,int) ;} ;
struct atmel_lcdfb_info {TYPE_1__* pdev; scalar_t__ reg_lcd; struct atmel_lcdfb_pdata pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int regulator_disable (scalar_t__) ; 
 int regulator_enable (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct atmel_lcdfb_pdata*,int) ; 

__attribute__((used)) static inline void atmel_lcdfb_power_control(struct atmel_lcdfb_info *sinfo, int on)
{
	int ret;
	struct atmel_lcdfb_pdata *pdata = &sinfo->pdata;

	if (pdata->atmel_lcdfb_power_control)
		pdata->atmel_lcdfb_power_control(pdata, on);
	else if (sinfo->reg_lcd) {
		if (on) {
			ret = regulator_enable(sinfo->reg_lcd);
			if (ret)
				dev_err(&sinfo->pdev->dev,
					"lcd regulator enable failed:	%d\n", ret);
		} else {
			ret = regulator_disable(sinfo->reg_lcd);
			if (ret)
				dev_err(&sinfo->pdev->dev,
					"lcd regulator disable failed: %d\n", ret);
		}
	}
}