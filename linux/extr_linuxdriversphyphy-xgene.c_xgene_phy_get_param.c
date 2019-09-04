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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_property_read_u32_array (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void xgene_phy_get_param(struct platform_device *pdev,
				const char *name, u32 *buffer,
				int count, u32 *default_val,
				u32 conv_factor)
{
	int i;

	if (!of_property_read_u32_array(pdev->dev.of_node, name, buffer,
					count)) {
		for (i = 0; i < count; i++)
			buffer[i] /= conv_factor;
		return;
	}
	/* Does not exist, load default */
	for (i = 0; i < count; i++)
		buffer[i] = default_val[i % 3];
}