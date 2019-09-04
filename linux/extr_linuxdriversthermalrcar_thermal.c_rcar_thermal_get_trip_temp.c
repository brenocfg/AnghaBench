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
struct thermal_zone_device {int dummy; } ;
struct rcar_thermal_priv {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MCELSIUS (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct device* rcar_priv_to_dev (struct rcar_thermal_priv*) ; 
 struct rcar_thermal_priv* rcar_zone_to_priv (struct thermal_zone_device*) ; 

__attribute__((used)) static int rcar_thermal_get_trip_temp(struct thermal_zone_device *zone,
				      int trip, int *temp)
{
	struct rcar_thermal_priv *priv = rcar_zone_to_priv(zone);
	struct device *dev = rcar_priv_to_dev(priv);

	/* see rcar_thermal_get_temp() */
	switch (trip) {
	case 0: /* +90 <= temp */
		*temp = MCELSIUS(90);
		break;
	default:
		dev_err(dev, "rcar driver trip error\n");
		return -EINVAL;
	}

	return 0;
}