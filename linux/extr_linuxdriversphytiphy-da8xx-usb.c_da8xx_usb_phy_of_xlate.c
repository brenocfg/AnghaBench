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
struct phy {int dummy; } ;
struct of_phandle_args {int* args; } ;
struct device {int dummy; } ;
struct da8xx_usb_phy {struct phy* usb11_phy; struct phy* usb20_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct da8xx_usb_phy* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static struct phy *da8xx_usb_phy_of_xlate(struct device *dev,
					 struct of_phandle_args *args)
{
	struct da8xx_usb_phy *d_phy = dev_get_drvdata(dev);

	if (!d_phy)
		return ERR_PTR(-ENODEV);

	switch (args->args[0]) {
	case 0:
		return d_phy->usb20_phy;
	case 1:
		return d_phy->usb11_phy;
	default:
		return ERR_PTR(-EINVAL);
	}
}