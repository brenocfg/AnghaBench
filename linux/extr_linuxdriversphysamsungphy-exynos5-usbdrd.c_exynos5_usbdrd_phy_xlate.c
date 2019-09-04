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
struct phy {int dummy; } ;
struct of_phandle_args {size_t* args; } ;
struct exynos5_usbdrd_phy {TYPE_1__* phys; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct phy* phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 size_t EXYNOS5_DRDPHYS_NUM ; 
 scalar_t__ WARN_ON (int) ; 
 struct exynos5_usbdrd_phy* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static struct phy *exynos5_usbdrd_phy_xlate(struct device *dev,
					struct of_phandle_args *args)
{
	struct exynos5_usbdrd_phy *phy_drd = dev_get_drvdata(dev);

	if (WARN_ON(args->args[0] >= EXYNOS5_DRDPHYS_NUM))
		return ERR_PTR(-ENODEV);

	return phy_drd->phys[args->args[0]].phy;
}