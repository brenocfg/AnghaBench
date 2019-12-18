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
struct cs35l36_vpbr_cfg {int is_present; unsigned int vpbr_en; unsigned int vpbr_thld; unsigned int vpbr_atk_rate; unsigned int vpbr_atk_vol; unsigned int vpbr_max_attn; unsigned int vpbr_wait; unsigned int vpbr_rel_rate; unsigned int vpbr_mute_en; } ;
struct cs35l36_platform_data {unsigned int bst_vctl; unsigned int bst_vctl_sel; unsigned int bst_ipk; unsigned int temp_warn_thld; unsigned int boost_ind; unsigned int irq_drv_sel; unsigned int irq_gpio_sel; void* vmon_pol_inv; void* imon_pol_inv; void* amp_pcm_inv; void* dcm_mode; void* multi_amp_mode; struct cs35l36_vpbr_cfg vpbr_config; } ;

/* Variables and functions */
 unsigned int CS35L36_VALID_PDATA ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 void* of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,unsigned int*) ; 

__attribute__((used)) static int cs35l36_handle_of_data(struct i2c_client *i2c_client,
				struct cs35l36_platform_data *pdata)
{
	struct device_node *np = i2c_client->dev.of_node;
	struct cs35l36_vpbr_cfg *vpbr_config = &pdata->vpbr_config;
	struct device_node *vpbr_node;
	unsigned int val;
	int ret;

	if (!np)
		return 0;

	ret = of_property_read_u32(np, "cirrus,boost-ctl-millivolt", &val);
	if (!ret) {
		if (val < 2550 || val > 12000) {
			dev_err(&i2c_client->dev,
				"Invalid Boost Voltage %d mV\n", val);
			return -EINVAL;
		}
		pdata->bst_vctl = (((val - 2550) / 100) + 1) << 1;
	} else {
		dev_err(&i2c_client->dev,
			"Unable to find required parameter 'cirrus,boost-ctl-millivolt'");
		return -EINVAL;
	}

	ret = of_property_read_u32(np, "cirrus,boost-ctl-select", &val);
	if (!ret)
		pdata->bst_vctl_sel = val | CS35L36_VALID_PDATA;

	ret = of_property_read_u32(np, "cirrus,boost-peak-milliamp", &val);
	if (!ret) {
		if (val < 1600 || val > 4500) {
			dev_err(&i2c_client->dev,
				"Invalid Boost Peak Current %u mA\n", val);
			return -EINVAL;
		}

		pdata->bst_ipk = (val - 1600) / 50;
	} else {
		dev_err(&i2c_client->dev,
			"Unable to find required parameter 'cirrus,boost-peak-milliamp'");
		return -EINVAL;
	}

	pdata->multi_amp_mode = of_property_read_bool(np,
					"cirrus,multi-amp-mode");

	pdata->dcm_mode = of_property_read_bool(np,
					"cirrus,dcm-mode-enable");

	pdata->amp_pcm_inv = of_property_read_bool(np,
					"cirrus,amp-pcm-inv");

	pdata->imon_pol_inv = of_property_read_bool(np,
					"cirrus,imon-pol-inv");

	pdata->vmon_pol_inv = of_property_read_bool(np,
					"cirrus,vmon-pol-inv");

	if (of_property_read_u32(np, "cirrus,temp-warn-threshold", &val) >= 0)
		pdata->temp_warn_thld = val | CS35L36_VALID_PDATA;

	if (of_property_read_u32(np, "cirrus,boost-ind-nanohenry", &val) >= 0) {
		pdata->boost_ind = val;
	} else {
		dev_err(&i2c_client->dev, "Inductor not specified.\n");
		return -EINVAL;
	}

	if (of_property_read_u32(np, "cirrus,irq-drive-select", &val) >= 0)
		pdata->irq_drv_sel = val | CS35L36_VALID_PDATA;

	if (of_property_read_u32(np, "cirrus,irq-gpio-select", &val) >= 0)
		pdata->irq_gpio_sel = val | CS35L36_VALID_PDATA;

	/* VPBR Config */
	vpbr_node = of_get_child_by_name(np, "cirrus,vpbr-config");
	vpbr_config->is_present = vpbr_node ? true : false;
	if (vpbr_config->is_present) {
		if (of_property_read_u32(vpbr_node, "cirrus,vpbr-en",
					 &val) >= 0)
			vpbr_config->vpbr_en = val;
		if (of_property_read_u32(vpbr_node, "cirrus,vpbr-thld",
					 &val) >= 0)
			vpbr_config->vpbr_thld = val;
		if (of_property_read_u32(vpbr_node, "cirrus,vpbr-atk-rate",
					 &val) >= 0)
			vpbr_config->vpbr_atk_rate = val;
		if (of_property_read_u32(vpbr_node, "cirrus,vpbr-atk-vol",
					 &val) >= 0)
			vpbr_config->vpbr_atk_vol = val;
		if (of_property_read_u32(vpbr_node, "cirrus,vpbr-max-attn",
					 &val) >= 0)
			vpbr_config->vpbr_max_attn = val;
		if (of_property_read_u32(vpbr_node, "cirrus,vpbr-wait",
					 &val) >= 0)
			vpbr_config->vpbr_wait = val;
		if (of_property_read_u32(vpbr_node, "cirrus,vpbr-rel-rate",
					 &val) >= 0)
			vpbr_config->vpbr_rel_rate = val;
		if (of_property_read_u32(vpbr_node, "cirrus,vpbr-mute-en",
					 &val) >= 0)
			vpbr_config->vpbr_mute_en = val;
	}
	of_node_put(vpbr_node);

	return 0;
}