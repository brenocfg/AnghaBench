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
struct TYPE_2__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct cs43130_private {int /*<<< orphan*/ * dc_threshold; int /*<<< orphan*/ * ac_freq; void* ac_meas; void* dc_meas; int /*<<< orphan*/  xtal_ibias; } ;

/* Variables and functions */
 int CS43130_AC_FREQ ; 
 int CS43130_DC_THRESHOLD ; 
 int /*<<< orphan*/  CS43130_XTAL_IBIAS_12_5UA ; 
 int /*<<< orphan*/  CS43130_XTAL_IBIAS_15UA ; 
 int /*<<< orphan*/  CS43130_XTAL_IBIAS_7_5UA ; 
 int /*<<< orphan*/  CS43130_XTAL_UNUSED ; 
 int EINVAL ; 
 int /*<<< orphan*/ * cs43130_ac_freq ; 
 int /*<<< orphan*/ * cs43130_dc_threshold ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,unsigned int) ; 
 void* of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u16_array (struct device_node*,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,unsigned int*) ; 

__attribute__((used)) static int cs43130_handle_device_data(struct i2c_client *i2c_client,
				      struct cs43130_private *cs43130)
{
	struct device_node *np = i2c_client->dev.of_node;
	unsigned int val;
	int i;

	if (of_property_read_u32(np, "cirrus,xtal-ibias", &val) < 0) {
		/* Crystal is unused. System clock is used for external MCLK */
		cs43130->xtal_ibias = CS43130_XTAL_UNUSED;
		return 0;
	}

	switch (val) {
	case 1:
		cs43130->xtal_ibias = CS43130_XTAL_IBIAS_7_5UA;
		break;
	case 2:
		cs43130->xtal_ibias = CS43130_XTAL_IBIAS_12_5UA;
		break;
	case 3:
		cs43130->xtal_ibias = CS43130_XTAL_IBIAS_15UA;
		break;
	default:
		dev_err(&i2c_client->dev,
			"Invalid cirrus,xtal-ibias value: %d\n", val);
		return -EINVAL;
	}

	cs43130->dc_meas = of_property_read_bool(np, "cirrus,dc-measure");
	cs43130->ac_meas = of_property_read_bool(np, "cirrus,ac-measure");

	if (of_property_read_u16_array(np, "cirrus,ac-freq", cs43130->ac_freq,
					CS43130_AC_FREQ) < 0) {
		for (i = 0; i < CS43130_AC_FREQ; i++)
			cs43130->ac_freq[i] = cs43130_ac_freq[i];
	}

	if (of_property_read_u16_array(np, "cirrus,dc-threshold",
				       cs43130->dc_threshold,
				       CS43130_DC_THRESHOLD) < 0) {
		for (i = 0; i < CS43130_DC_THRESHOLD; i++)
			cs43130->dc_threshold[i] = cs43130_dc_threshold[i];
	}

	return 0;
}