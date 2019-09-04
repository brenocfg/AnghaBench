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
typedef  void* u8 ;
struct monitor_cfg {int is_present; int imon_specs; int vmon_specs; int vpmon_specs; int vbstmon_specs; int vpbrstat_specs; int zerofill_specs; void* zerofill_frm; void* zerofill_loc; void* zerofill_dpth; void* vpbrstat_frm; void* vpbrstat_loc; void* vpbrstat_dpth; void* vbstmon_frm; void* vbstmon_loc; void* vbstmon_dpth; void* vpmon_frm; void* vpmon_loc; void* vpmon_dpth; void* vmon_frm; void* vmon_loc; void* vmon_dpth; void* imon_scale; void* imon_frm; void* imon_loc; void* imon_dpth; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct classh_cfg {int classh_algo_enable; unsigned int classh_bst_max_limit; unsigned int classh_mem_depth; unsigned int classh_release_rate; unsigned int classh_headroom; unsigned int classh_wk_fet_disable; unsigned int classh_wk_fet_delay; unsigned int classh_wk_fet_thld; unsigned int classh_vpch_auto; unsigned int classh_vpch_rate; unsigned int classh_vpch_man; void* classh_bst_override; } ;
struct cs35l35_platform_data {unsigned int bst_vctl; unsigned int bst_ipk; unsigned int boost_ind; unsigned int sp_drv_str; unsigned int sp_drv_unused; unsigned int aud_channel; unsigned int adv_channel; void* gain_zc; void* ext_bst; void* shared_bst; void* stereo; void* bst_pdn_fet_on; struct monitor_cfg mon_cfg; struct classh_cfg classh_algo; } ;

/* Variables and functions */
 int ARRAY_SIZE (void**) ; 
 unsigned int CS35L35_VALID_PDATA ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 void* of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,unsigned int*) ; 
 int of_property_read_u8_array (struct device_node*,char*,void**,int const) ; 

__attribute__((used)) static int cs35l35_handle_of_data(struct i2c_client *i2c_client,
				struct cs35l35_platform_data *pdata)
{
	struct device_node *np = i2c_client->dev.of_node;
	struct device_node *classh, *signal_format;
	struct classh_cfg *classh_config = &pdata->classh_algo;
	struct monitor_cfg *monitor_config = &pdata->mon_cfg;
	unsigned int val32 = 0;
	u8 monitor_array[4];
	const int imon_array_size = ARRAY_SIZE(monitor_array);
	const int mon_array_size = imon_array_size - 1;
	int ret = 0;

	if (!np)
		return 0;

	pdata->bst_pdn_fet_on = of_property_read_bool(np,
					"cirrus,boost-pdn-fet-on");

	ret = of_property_read_u32(np, "cirrus,boost-ctl-millivolt", &val32);
	if (ret >= 0) {
		if (val32 < 2600 || val32 > 9000) {
			dev_err(&i2c_client->dev,
				"Invalid Boost Voltage %d mV\n", val32);
			return -EINVAL;
		}
		pdata->bst_vctl = ((val32 - 2600) / 100) + 1;
	}

	ret = of_property_read_u32(np, "cirrus,boost-peak-milliamp", &val32);
	if (ret >= 0) {
		if (val32 < 1680 || val32 > 4480) {
			dev_err(&i2c_client->dev,
				"Invalid Boost Peak Current %u mA\n", val32);
			return -EINVAL;
		}

		pdata->bst_ipk = ((val32 - 1680) / 110) | CS35L35_VALID_PDATA;
	}

	ret = of_property_read_u32(np, "cirrus,boost-ind-nanohenry", &val32);
	if (ret >= 0) {
		pdata->boost_ind = val32;
	} else {
		dev_err(&i2c_client->dev, "Inductor not specified.\n");
		return -EINVAL;
	}

	if (of_property_read_u32(np, "cirrus,sp-drv-strength", &val32) >= 0)
		pdata->sp_drv_str = val32;
	if (of_property_read_u32(np, "cirrus,sp-drv-unused", &val32) >= 0)
		pdata->sp_drv_unused = val32 | CS35L35_VALID_PDATA;

	pdata->stereo = of_property_read_bool(np, "cirrus,stereo-config");

	if (pdata->stereo) {
		ret = of_property_read_u32(np, "cirrus,audio-channel", &val32);
		if (ret >= 0)
			pdata->aud_channel = val32;

		ret = of_property_read_u32(np, "cirrus,advisory-channel",
					   &val32);
		if (ret >= 0)
			pdata->adv_channel = val32;

		pdata->shared_bst = of_property_read_bool(np,
						"cirrus,shared-boost");
	}

	pdata->ext_bst = of_property_read_bool(np, "cirrus,external-boost");

	pdata->gain_zc = of_property_read_bool(np, "cirrus,amp-gain-zc");

	classh = of_get_child_by_name(np, "cirrus,classh-internal-algo");
	classh_config->classh_algo_enable = classh ? true : false;

	if (classh_config->classh_algo_enable) {
		classh_config->classh_bst_override =
			of_property_read_bool(np, "cirrus,classh-bst-overide");

		ret = of_property_read_u32(classh,
					   "cirrus,classh-bst-max-limit",
					   &val32);
		if (ret >= 0) {
			val32 |= CS35L35_VALID_PDATA;
			classh_config->classh_bst_max_limit = val32;
		}

		ret = of_property_read_u32(classh,
					   "cirrus,classh-bst-max-limit",
					   &val32);
		if (ret >= 0) {
			val32 |= CS35L35_VALID_PDATA;
			classh_config->classh_bst_max_limit = val32;
		}

		ret = of_property_read_u32(classh, "cirrus,classh-mem-depth",
					   &val32);
		if (ret >= 0) {
			val32 |= CS35L35_VALID_PDATA;
			classh_config->classh_mem_depth = val32;
		}

		ret = of_property_read_u32(classh, "cirrus,classh-release-rate",
					   &val32);
		if (ret >= 0)
			classh_config->classh_release_rate = val32;

		ret = of_property_read_u32(classh, "cirrus,classh-headroom",
					   &val32);
		if (ret >= 0) {
			val32 |= CS35L35_VALID_PDATA;
			classh_config->classh_headroom = val32;
		}

		ret = of_property_read_u32(classh,
					   "cirrus,classh-wk-fet-disable",
					   &val32);
		if (ret >= 0)
			classh_config->classh_wk_fet_disable = val32;

		ret = of_property_read_u32(classh, "cirrus,classh-wk-fet-delay",
					   &val32);
		if (ret >= 0) {
			val32 |= CS35L35_VALID_PDATA;
			classh_config->classh_wk_fet_delay = val32;
		}

		ret = of_property_read_u32(classh, "cirrus,classh-wk-fet-thld",
					   &val32);
		if (ret >= 0)
			classh_config->classh_wk_fet_thld = val32;

		ret = of_property_read_u32(classh, "cirrus,classh-vpch-auto",
					   &val32);
		if (ret >= 0) {
			val32 |= CS35L35_VALID_PDATA;
			classh_config->classh_vpch_auto = val32;
		}

		ret = of_property_read_u32(classh, "cirrus,classh-vpch-rate",
					   &val32);
		if (ret >= 0) {
			val32 |= CS35L35_VALID_PDATA;
			classh_config->classh_vpch_rate = val32;
		}

		ret = of_property_read_u32(classh, "cirrus,classh-vpch-man",
					   &val32);
		if (ret >= 0)
			classh_config->classh_vpch_man = val32;
	}
	of_node_put(classh);

	/* frame depth location */
	signal_format = of_get_child_by_name(np, "cirrus,monitor-signal-format");
	monitor_config->is_present = signal_format ? true : false;
	if (monitor_config->is_present) {
		ret = of_property_read_u8_array(signal_format, "cirrus,imon",
						monitor_array, imon_array_size);
		if (!ret) {
			monitor_config->imon_specs = true;
			monitor_config->imon_dpth = monitor_array[0];
			monitor_config->imon_loc = monitor_array[1];
			monitor_config->imon_frm = monitor_array[2];
			monitor_config->imon_scale = monitor_array[3];
		}
		ret = of_property_read_u8_array(signal_format, "cirrus,vmon",
						monitor_array, mon_array_size);
		if (!ret) {
			monitor_config->vmon_specs = true;
			monitor_config->vmon_dpth = monitor_array[0];
			monitor_config->vmon_loc = monitor_array[1];
			monitor_config->vmon_frm = monitor_array[2];
		}
		ret = of_property_read_u8_array(signal_format, "cirrus,vpmon",
						monitor_array, mon_array_size);
		if (!ret) {
			monitor_config->vpmon_specs = true;
			monitor_config->vpmon_dpth = monitor_array[0];
			monitor_config->vpmon_loc = monitor_array[1];
			monitor_config->vpmon_frm = monitor_array[2];
		}
		ret = of_property_read_u8_array(signal_format, "cirrus,vbstmon",
						monitor_array, mon_array_size);
		if (!ret) {
			monitor_config->vbstmon_specs = true;
			monitor_config->vbstmon_dpth = monitor_array[0];
			monitor_config->vbstmon_loc = monitor_array[1];
			monitor_config->vbstmon_frm = monitor_array[2];
		}
		ret = of_property_read_u8_array(signal_format, "cirrus,vpbrstat",
						monitor_array, mon_array_size);
		if (!ret) {
			monitor_config->vpbrstat_specs = true;
			monitor_config->vpbrstat_dpth = monitor_array[0];
			monitor_config->vpbrstat_loc = monitor_array[1];
			monitor_config->vpbrstat_frm = monitor_array[2];
		}
		ret = of_property_read_u8_array(signal_format, "cirrus,zerofill",
						monitor_array, mon_array_size);
		if (!ret) {
			monitor_config->zerofill_specs = true;
			monitor_config->zerofill_dpth = monitor_array[0];
			monitor_config->zerofill_loc = monitor_array[1];
			monitor_config->zerofill_frm = monitor_array[2];
		}
	}
	of_node_put(signal_format);

	return 0;
}