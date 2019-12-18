#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct cs35l34_platform_data {unsigned int boost_vtge; unsigned int boost_ind; unsigned int boost_peak; unsigned int i2s_sdinloc; unsigned int tdm_rising_edge; void* amp_inv; void* gain_zc_disable; void* digsft_disable; void* aif_half_drv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 void* of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,unsigned int*) ; 

__attribute__((used)) static int cs35l34_handle_of_data(struct i2c_client *i2c_client,
				struct cs35l34_platform_data *pdata)
{
	struct device_node *np = i2c_client->dev.of_node;
	unsigned int val;

	if (of_property_read_u32(np, "cirrus,boost-vtge-millivolt",
		&val) >= 0) {
		/* Boost Voltage has a maximum of 8V */
		if (val > 8000 || (val < 3300 && val > 0)) {
			dev_err(&i2c_client->dev,
				"Invalid Boost Voltage %d mV\n", val);
			return -EINVAL;
		}
		if (val == 0)
			pdata->boost_vtge = 0; /* Use VP */
		else
			pdata->boost_vtge = ((val - 3300)/100) + 1;
	} else {
		dev_warn(&i2c_client->dev,
			"Boost Voltage not specified. Using VP\n");
	}

	if (of_property_read_u32(np, "cirrus,boost-ind-nanohenry", &val) >= 0) {
		pdata->boost_ind = val;
	} else {
		dev_err(&i2c_client->dev, "Inductor not specified.\n");
		return -EINVAL;
	}

	if (of_property_read_u32(np, "cirrus,boost-peak-milliamp", &val) >= 0) {
		if (val > 3840 || val < 1200) {
			dev_err(&i2c_client->dev,
				"Invalid Boost Peak Current %d mA\n", val);
			return -EINVAL;
		}
		pdata->boost_peak = ((val - 1200)/80) + 1;
	}

	pdata->aif_half_drv = of_property_read_bool(np,
		"cirrus,aif-half-drv");
	pdata->digsft_disable = of_property_read_bool(np,
		"cirrus,digsft-disable");

	pdata->gain_zc_disable = of_property_read_bool(np,
		"cirrus,gain-zc-disable");
	pdata->amp_inv = of_property_read_bool(np, "cirrus,amp-inv");

	if (of_property_read_u32(np, "cirrus,i2s-sdinloc", &val) >= 0)
		pdata->i2s_sdinloc = val;
	if (of_property_read_u32(np, "cirrus,tdm-rising-edge", &val) >= 0)
		pdata->tdm_rising_edge = val;

	return 0;
}