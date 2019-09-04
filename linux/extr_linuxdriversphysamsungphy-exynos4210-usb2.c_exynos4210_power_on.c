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
struct samsung_usb2_phy_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  exynos4210_isol (struct samsung_usb2_phy_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos4210_phy_pwr (struct samsung_usb2_phy_instance*,int) ; 

__attribute__((used)) static int exynos4210_power_on(struct samsung_usb2_phy_instance *inst)
{
	/* Order of initialisation is important - first power then isolation */
	exynos4210_phy_pwr(inst, 1);
	exynos4210_isol(inst, 0);

	return 0;
}