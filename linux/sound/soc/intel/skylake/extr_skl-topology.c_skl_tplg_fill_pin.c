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
struct snd_soc_tplg_vendor_value_elem {int token; int /*<<< orphan*/  value; } ;
struct snd_soc_tplg_vendor_uuid_elem {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mod_uuid; int /*<<< orphan*/  instance_id; int /*<<< orphan*/  module_id; } ;
struct skl_module_pin {TYPE_1__ id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SKL_TKN_U32_PIN_INST_ID 130 
#define  SKL_TKN_U32_PIN_MOD_ID 129 
#define  SKL_TKN_UUID 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int skl_tplg_get_uuid (struct device*,int /*<<< orphan*/ *,struct snd_soc_tplg_vendor_uuid_elem*) ; 

__attribute__((used)) static int skl_tplg_fill_pin(struct device *dev,
			struct snd_soc_tplg_vendor_value_elem *tkn_elem,
			struct skl_module_pin *m_pin,
			int pin_index)
{
	int ret;

	switch (tkn_elem->token) {
	case SKL_TKN_U32_PIN_MOD_ID:
		m_pin[pin_index].id.module_id = tkn_elem->value;
		break;

	case SKL_TKN_U32_PIN_INST_ID:
		m_pin[pin_index].id.instance_id = tkn_elem->value;
		break;

	case SKL_TKN_UUID:
		ret = skl_tplg_get_uuid(dev, &m_pin[pin_index].id.mod_uuid,
			(struct snd_soc_tplg_vendor_uuid_elem *)tkn_elem);
		if (ret < 0)
			return ret;

		break;

	default:
		dev_err(dev, "%d Not a pin token\n", tkn_elem->token);
		return -EINVAL;
	}

	return 0;
}