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
struct cs35l32_platform_data {unsigned int sdout_share; unsigned int boost_mng; unsigned int sdout_datacfg; unsigned int batt_thresh; unsigned int batt_recov; } ;

/* Variables and functions */
#define  CS35L32_BATT_RECOV_3_1V 145 
#define  CS35L32_BATT_RECOV_3_2V 144 
#define  CS35L32_BATT_RECOV_3_3V 143 
#define  CS35L32_BATT_RECOV_3_4V 142 
#define  CS35L32_BATT_RECOV_3_5V 141 
#define  CS35L32_BATT_RECOV_3_6V 140 
#define  CS35L32_BATT_THRESH_3_1V 139 
#define  CS35L32_BATT_THRESH_3_2V 138 
#define  CS35L32_BATT_THRESH_3_3V 137 
#define  CS35L32_BATT_THRESH_3_4V 136 
#define  CS35L32_BOOST_MGR_AUTO 135 
#define  CS35L32_BOOST_MGR_AUTO_AUDIO 134 
#define  CS35L32_BOOST_MGR_BYPASS 133 
#define  CS35L32_BOOST_MGR_FIXED 132 
#define  CS35L32_DATA_CFG_LR 131 
#define  CS35L32_DATA_CFG_LR_STAT 130 
#define  CS35L32_DATA_CFG_LR_VP 129 
#define  CS35L32_DATA_CFG_LR_VPSTAT 128 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,unsigned int) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,unsigned int*) ; 

__attribute__((used)) static int cs35l32_handle_of_data(struct i2c_client *i2c_client,
				    struct cs35l32_platform_data *pdata)
{
	struct device_node *np = i2c_client->dev.of_node;
	unsigned int val;

	if (of_property_read_u32(np, "cirrus,sdout-share", &val) >= 0)
		pdata->sdout_share = val;

	if (of_property_read_u32(np, "cirrus,boost-manager", &val))
		val = -1u;

	switch (val) {
	case CS35L32_BOOST_MGR_AUTO:
	case CS35L32_BOOST_MGR_AUTO_AUDIO:
	case CS35L32_BOOST_MGR_BYPASS:
	case CS35L32_BOOST_MGR_FIXED:
		pdata->boost_mng = val;
		break;
	case -1u:
	default:
		dev_err(&i2c_client->dev,
			"Wrong cirrus,boost-manager DT value %d\n", val);
		pdata->boost_mng = CS35L32_BOOST_MGR_BYPASS;
	}

	if (of_property_read_u32(np, "cirrus,sdout-datacfg", &val))
		val = -1u;
	switch (val) {
	case CS35L32_DATA_CFG_LR_VP:
	case CS35L32_DATA_CFG_LR_STAT:
	case CS35L32_DATA_CFG_LR:
	case CS35L32_DATA_CFG_LR_VPSTAT:
		pdata->sdout_datacfg = val;
		break;
	case -1u:
	default:
		dev_err(&i2c_client->dev,
			"Wrong cirrus,sdout-datacfg DT value %d\n", val);
		pdata->sdout_datacfg = CS35L32_DATA_CFG_LR;
	}

	if (of_property_read_u32(np, "cirrus,battery-threshold", &val))
		val = -1u;
	switch (val) {
	case CS35L32_BATT_THRESH_3_1V:
	case CS35L32_BATT_THRESH_3_2V:
	case CS35L32_BATT_THRESH_3_3V:
	case CS35L32_BATT_THRESH_3_4V:
		pdata->batt_thresh = val;
		break;
	case -1u:
	default:
		dev_err(&i2c_client->dev,
			"Wrong cirrus,battery-threshold DT value %d\n", val);
		pdata->batt_thresh = CS35L32_BATT_THRESH_3_3V;
	}

	if (of_property_read_u32(np, "cirrus,battery-recovery", &val))
		val = -1u;
	switch (val) {
	case CS35L32_BATT_RECOV_3_1V:
	case CS35L32_BATT_RECOV_3_2V:
	case CS35L32_BATT_RECOV_3_3V:
	case CS35L32_BATT_RECOV_3_4V:
	case CS35L32_BATT_RECOV_3_5V:
	case CS35L32_BATT_RECOV_3_6V:
		pdata->batt_recov = val;
		break;
	case -1u:
	default:
		dev_err(&i2c_client->dev,
			"Wrong cirrus,battery-recovery DT value %d\n", val);
		pdata->batt_recov = CS35L32_BATT_RECOV_3_4V;
	}

	return 0;
}