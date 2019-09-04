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
typedef  int u32 ;
struct fusb302_chip {int /*<<< orphan*/ * snk_pdo; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_FIXED (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PDO_FIXED_FLAGS ; 
 int /*<<< orphan*/  PDO_VAR (int,int,int) ; 
 scalar_t__ device_property_read_u32 (struct device*,char*,int*) ; 

__attribute__((used)) static int fusb302_composite_snk_pdo_array(struct fusb302_chip *chip)
{
	struct device *dev = chip->dev;
	u32 max_uv, max_ua;

	chip->snk_pdo[0] = PDO_FIXED(5000, 400, PDO_FIXED_FLAGS);

	/*
	 * As max_snk_ma/mv/mw is not needed for tcpc_config,
	 * those settings should be passed in via sink PDO, so
	 * "fcs, max-sink-*" properties will be deprecated, to
	 * perserve compatibility with existing users of them,
	 * we read those properties to convert them to be a var
	 * PDO.
	 */
	if (device_property_read_u32(dev, "fcs,max-sink-microvolt", &max_uv) ||
		device_property_read_u32(dev, "fcs,max-sink-microamp", &max_ua))
		return 1;

	chip->snk_pdo[1] = PDO_VAR(5000, max_uv / 1000, max_ua / 1000);
	return 2;
}