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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOVERFLOW ; 
 int INT_MAX ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,char const*,int) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char const*,int*) ; 

__attribute__((used)) static int ramoops_parse_dt_size(struct platform_device *pdev,
				 const char *propname, u32 *value)
{
	u32 val32 = 0;
	int ret;

	ret = of_property_read_u32(pdev->dev.of_node, propname, &val32);
	if (ret < 0 && ret != -EINVAL) {
		dev_err(&pdev->dev, "failed to parse property %s: %d\n",
			propname, ret);
		return ret;
	}

	if (val32 > INT_MAX) {
		dev_err(&pdev->dev, "%s %u > INT_MAX\n", propname, val32);
		return -EOVERFLOW;
	}

	*value = val32;
	return 0;
}