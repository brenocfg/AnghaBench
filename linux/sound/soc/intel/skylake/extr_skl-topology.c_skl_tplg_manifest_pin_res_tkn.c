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
struct skl_module_res {struct skl_module_pin_resources* output; struct skl_module_pin_resources* input; } ;
struct skl_module_pin_resources {int /*<<< orphan*/  buf_size; int /*<<< orphan*/  pin_index; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SKL_DIR_IN 131 
#define  SKL_DIR_OUT 130 
#define  SKL_TKN_MM_U32_PIN_BUF 129 
#define  SKL_TKN_MM_U32_RES_PIN_ID 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 

__attribute__((used)) static int skl_tplg_manifest_pin_res_tkn(struct device *dev,
		struct snd_soc_tplg_vendor_value_elem *tkn_elem,
		struct skl_module_res *res, int pin_idx, int dir)
{
	struct skl_module_pin_resources *m_pin;

	switch (dir) {
	case SKL_DIR_IN:
		m_pin = &res->input[pin_idx];
		break;

	case SKL_DIR_OUT:
		m_pin = &res->output[pin_idx];
		break;

	default:
		dev_err(dev, "Invalid pin direction: %d\n", dir);
		return -EINVAL;
	}

	switch (tkn_elem->token) {
	case SKL_TKN_MM_U32_RES_PIN_ID:
		m_pin->pin_index = tkn_elem->value;
		break;

	case SKL_TKN_MM_U32_PIN_BUF:
		m_pin->buf_size = tkn_elem->value;
		break;

	default:
		dev_err(dev, "Invalid token: %d\n", tkn_elem->token);
		return -EINVAL;
	}

	return 0;
}