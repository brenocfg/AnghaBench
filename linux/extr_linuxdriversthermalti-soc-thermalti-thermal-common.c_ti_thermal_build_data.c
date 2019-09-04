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
struct ti_thermal_data {int sensor_id; int /*<<< orphan*/  thermal_wq; int /*<<< orphan*/  pcb_tz; int /*<<< orphan*/  mode; struct ti_bandgap* bgp; } ;
struct ti_bandgap {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THERMAL_DEVICE_ENABLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct ti_thermal_data* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_zone_get_zone_by_name (char*) ; 
 int /*<<< orphan*/  ti_thermal_work ; 

__attribute__((used)) static struct ti_thermal_data
*ti_thermal_build_data(struct ti_bandgap *bgp, int id)
{
	struct ti_thermal_data *data;

	data = devm_kzalloc(bgp->dev, sizeof(*data), GFP_KERNEL);
	if (!data) {
		dev_err(bgp->dev, "kzalloc fail\n");
		return NULL;
	}
	data->sensor_id = id;
	data->bgp = bgp;
	data->mode = THERMAL_DEVICE_ENABLED;
	/* pcb_tz will be either valid or PTR_ERR() */
	data->pcb_tz = thermal_zone_get_zone_by_name("pcb");
	INIT_WORK(&data->thermal_wq, ti_thermal_work);

	return data;
}