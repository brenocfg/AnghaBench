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
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int PHY_INTERFACE_MODE_MAX ; 
 int of_property_read_string (struct device_node*,char*,char const**) ; 
 int /*<<< orphan*/  phy_modes (int) ; 
 int /*<<< orphan*/  strcasecmp (char const*,int /*<<< orphan*/ ) ; 

int of_get_phy_mode(struct device_node *np)
{
	const char *pm;
	int err, i;

	err = of_property_read_string(np, "phy-mode", &pm);
	if (err < 0)
		err = of_property_read_string(np, "phy-connection-type", &pm);
	if (err < 0)
		return err;

	for (i = 0; i < PHY_INTERFACE_MODE_MAX; i++)
		if (!strcasecmp(pm, phy_modes(i)))
			return i;

	return -ENODEV;
}