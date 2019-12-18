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
struct snd_soc_tplg_vendor_value_elem {int dummy; } ;
struct skl_module_pin {int in_use; int /*<<< orphan*/  pin_state; } ;
struct skl_module_cfg {struct skl_module_pin* m_out_pin; struct skl_module_pin* m_in_pin; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SKL_DIR_IN 129 
#define  SKL_DIR_OUT 128 
 int /*<<< orphan*/  SKL_PIN_UNBIND ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int skl_tplg_fill_pin (struct device*,struct snd_soc_tplg_vendor_value_elem*,struct skl_module_pin*,int) ; 

__attribute__((used)) static int skl_tplg_fill_pins_info(struct device *dev,
		struct skl_module_cfg *mconfig,
		struct snd_soc_tplg_vendor_value_elem *tkn_elem,
		int dir, int pin_count)
{
	int ret;
	struct skl_module_pin *m_pin;

	switch (dir) {
	case SKL_DIR_IN:
		m_pin = mconfig->m_in_pin;
		break;

	case SKL_DIR_OUT:
		m_pin = mconfig->m_out_pin;
		break;

	default:
		dev_err(dev, "Invalid direction value\n");
		return -EINVAL;
	}

	ret = skl_tplg_fill_pin(dev, tkn_elem, m_pin, pin_count);
	if (ret < 0)
		return ret;

	m_pin[pin_count].in_use = false;
	m_pin[pin_count].pin_state = SKL_PIN_UNBIND;

	return 0;
}