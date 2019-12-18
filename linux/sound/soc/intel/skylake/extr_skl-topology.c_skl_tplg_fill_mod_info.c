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
struct snd_soc_tplg_vendor_value_elem {int token; int /*<<< orphan*/  value; } ;
struct skl_module {int /*<<< orphan*/  nr_interfaces; int /*<<< orphan*/  nr_resources; int /*<<< orphan*/  max_output_pins; int /*<<< orphan*/  max_input_pins; int /*<<< orphan*/  output_pin_type; int /*<<< orphan*/  input_pin_type; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SKL_TKN_MM_U8_NUM_INTF 133 
#define  SKL_TKN_MM_U8_NUM_RES 132 
#define  SKL_TKN_U8_IN_PIN_TYPE 131 
#define  SKL_TKN_U8_IN_QUEUE_COUNT 130 
#define  SKL_TKN_U8_OUT_PIN_TYPE 129 
#define  SKL_TKN_U8_OUT_QUEUE_COUNT 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 

__attribute__((used)) static int skl_tplg_fill_mod_info(struct device *dev,
		struct snd_soc_tplg_vendor_value_elem *tkn_elem,
		struct skl_module *mod)
{

	if (!mod)
		return -EINVAL;

	switch (tkn_elem->token) {
	case SKL_TKN_U8_IN_PIN_TYPE:
		mod->input_pin_type = tkn_elem->value;
		break;

	case SKL_TKN_U8_OUT_PIN_TYPE:
		mod->output_pin_type = tkn_elem->value;
		break;

	case SKL_TKN_U8_IN_QUEUE_COUNT:
		mod->max_input_pins = tkn_elem->value;
		break;

	case SKL_TKN_U8_OUT_QUEUE_COUNT:
		mod->max_output_pins = tkn_elem->value;
		break;

	case SKL_TKN_MM_U8_NUM_RES:
		mod->nr_resources = tkn_elem->value;
		break;

	case SKL_TKN_MM_U8_NUM_INTF:
		mod->nr_interfaces = tkn_elem->value;
		break;

	default:
		dev_err(dev, "Invalid mod info token %d", tkn_elem->token);
		return -EINVAL;
	}

	return 0;
}