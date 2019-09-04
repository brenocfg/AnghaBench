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
typedef  enum thermal_trip_type { ____Placeholder_thermal_trip_type } thermal_trip_type ;

/* Variables and functions */
#define  THERMAL_TRIP_CRITICAL 128 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct device* rcar_priv_to_dev (struct rcar_thermal_priv*) ; 
 struct rcar_thermal_priv* rcar_zone_to_priv (struct thermal_zone_device*) ; 

__attribute__((used)) static int rcar_thermal_notify(struct thermal_zone_device *zone,
			       int trip, enum thermal_trip_type type)
{
	struct rcar_thermal_priv *priv = rcar_zone_to_priv(zone);
	struct device *dev = rcar_priv_to_dev(priv);

	switch (type) {
	case THERMAL_TRIP_CRITICAL:
		/* FIXME */
		dev_warn(dev, "Thermal reached to critical temperature\n");
		break;
	default:
		break;
	}

	return 0;
}