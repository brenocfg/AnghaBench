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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;
struct brcm_usb_phy_data {TYPE_1__ ini; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * brcm_dr_mode_to_name ; 
 struct brcm_usb_phy_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 char* value_to_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t dr_mode_show(struct device *dev,
			    struct device_attribute *attr,
			    char *buf)
{
	struct brcm_usb_phy_data *priv = dev_get_drvdata(dev);

	return sprintf(buf, "%s\n",
		value_to_name(&brcm_dr_mode_to_name[0],
			      ARRAY_SIZE(brcm_dr_mode_to_name),
			      priv->ini.mode));
}