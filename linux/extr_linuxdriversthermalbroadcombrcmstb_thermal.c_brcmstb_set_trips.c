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
struct brcmstb_thermal_priv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  TMON_TRIP_TYPE_HIGH ; 
 int /*<<< orphan*/  TMON_TRIP_TYPE_LOW ; 
 int /*<<< orphan*/  avs_tmon_set_trip_temp (struct brcmstb_thermal_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avs_tmon_trip_enable (struct brcmstb_thermal_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int brcmstb_set_trips(void *data, int low, int high)
{
	struct brcmstb_thermal_priv *priv = data;

	dev_dbg(priv->dev, "set trips %d <--> %d\n", low, high);

	/*
	 * Disable low-temp if "low" is too small. As per thermal framework
	 * API, we use -INT_MAX rather than INT_MIN.
	 */
	if (low <= -INT_MAX) {
		avs_tmon_trip_enable(priv, TMON_TRIP_TYPE_LOW, 0);
	} else {
		avs_tmon_set_trip_temp(priv, TMON_TRIP_TYPE_LOW, low);
		avs_tmon_trip_enable(priv, TMON_TRIP_TYPE_LOW, 1);
	}

	/* Disable high-temp if "high" is too big. */
	if (high == INT_MAX) {
		avs_tmon_trip_enable(priv, TMON_TRIP_TYPE_HIGH, 0);
	} else {
		avs_tmon_set_trip_temp(priv, TMON_TRIP_TYPE_HIGH, high);
		avs_tmon_trip_enable(priv, TMON_TRIP_TYPE_HIGH, 1);
	}

	return 0;
}