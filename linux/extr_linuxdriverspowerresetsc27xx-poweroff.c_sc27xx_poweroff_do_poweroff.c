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

/* Variables and functions */
 int /*<<< orphan*/  SC27XX_PWR_OFF_EN ; 
 int /*<<< orphan*/  SC27XX_PWR_PD_HW ; 
 int /*<<< orphan*/  regmap ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sc27xx_poweroff_do_poweroff(void)
{
	regmap_write(regmap, SC27XX_PWR_PD_HW, SC27XX_PWR_OFF_EN);
}