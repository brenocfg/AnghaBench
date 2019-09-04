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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,char const*,int) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char const*,scalar_t__*) ; 

__attribute__((used)) static int read_utmi_param(struct platform_device *pdev, const char *param,
			   u8 *dest)
{
	u32 value;
	int err = of_property_read_u32(pdev->dev.of_node, param, &value);
	*dest = (u8)value;
	if (err < 0)
		dev_err(&pdev->dev,
			"Failed to read USB UTMI parameter %s: %d\n",
			param, err);
	return err;
}