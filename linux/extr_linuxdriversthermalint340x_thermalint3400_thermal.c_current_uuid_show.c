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
struct platform_device {int dummy; } ;
struct int3400_thermal_priv {int uuid_bitmap; int current_uuid_index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char** int3400_thermal_uuids ; 
 struct int3400_thermal_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static ssize_t current_uuid_show(struct device *dev,
				 struct device_attribute *devattr, char *buf)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct int3400_thermal_priv *priv = platform_get_drvdata(pdev);

	if (priv->uuid_bitmap & (1 << priv->current_uuid_index))
		return sprintf(buf, "%s\n",
			       int3400_thermal_uuids[priv->current_uuid_index]);
	else
		return sprintf(buf, "INVALID\n");
}