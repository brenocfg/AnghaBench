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
struct spmi_regulator_init_data {int /*<<< orphan*/  vs_soft_start_strength; int /*<<< orphan*/  pin_ctrl_hpm; int /*<<< orphan*/  pin_ctrl_enable; } ;
struct spmi_regulator {int /*<<< orphan*/  ocp_retry_delay_ms; int /*<<< orphan*/  ocp_max_retries; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPMI_REGULATOR_PIN_CTRL_ENABLE_HW_DEFAULT ; 
 int /*<<< orphan*/  SPMI_REGULATOR_PIN_CTRL_HPM_HW_DEFAULT ; 
 int /*<<< orphan*/  SPMI_VS_SOFT_START_STR_HW_DEFAULT ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spmi_regulator_get_dt_config(struct spmi_regulator *vreg,
		struct device_node *node, struct spmi_regulator_init_data *data)
{
	/*
	 * Initialize configuration parameters to use hardware default in case
	 * no value is specified via device tree.
	 */
	data->pin_ctrl_enable	    = SPMI_REGULATOR_PIN_CTRL_ENABLE_HW_DEFAULT;
	data->pin_ctrl_hpm	    = SPMI_REGULATOR_PIN_CTRL_HPM_HW_DEFAULT;
	data->vs_soft_start_strength	= SPMI_VS_SOFT_START_STR_HW_DEFAULT;

	/* These bindings are optional, so it is okay if they aren't found. */
	of_property_read_u32(node, "qcom,ocp-max-retries",
		&vreg->ocp_max_retries);
	of_property_read_u32(node, "qcom,ocp-retry-delay",
		&vreg->ocp_retry_delay_ms);
	of_property_read_u32(node, "qcom,pin-ctrl-enable",
		&data->pin_ctrl_enable);
	of_property_read_u32(node, "qcom,pin-ctrl-hpm", &data->pin_ctrl_hpm);
	of_property_read_u32(node, "qcom,vs-soft-start-strength",
		&data->vs_soft_start_strength);
}