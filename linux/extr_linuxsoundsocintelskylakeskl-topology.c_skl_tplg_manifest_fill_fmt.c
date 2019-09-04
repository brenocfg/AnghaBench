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
typedef  int u32 ;
struct snd_soc_tplg_vendor_value_elem {int token; int /*<<< orphan*/  value; } ;
struct skl_module_fmt {int dummy; } ;
struct skl_module_pin_fmt {int /*<<< orphan*/  id; struct skl_module_fmt fmt; } ;
struct skl_module_iface {struct skl_module_pin_fmt* outputs; struct skl_module_pin_fmt* inputs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SKL_DIR_IN 130 
#define  SKL_DIR_OUT 129 
#define  SKL_TKN_MM_U32_INTF_PIN_ID 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int skl_tplg_fill_fmt (struct device*,struct skl_module_fmt*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skl_tplg_manifest_fill_fmt(struct device *dev,
		struct skl_module_iface *fmt,
		struct snd_soc_tplg_vendor_value_elem *tkn_elem,
		u32 dir, int fmt_idx)
{
	struct skl_module_pin_fmt *dst_fmt;
	struct skl_module_fmt *mod_fmt;
	int ret;

	if (!fmt)
		return -EINVAL;

	switch (dir) {
	case SKL_DIR_IN:
		dst_fmt = &fmt->inputs[fmt_idx];
		break;

	case SKL_DIR_OUT:
		dst_fmt = &fmt->outputs[fmt_idx];
		break;

	default:
		dev_err(dev, "Invalid direction: %d\n", dir);
		return -EINVAL;
	}

	mod_fmt = &dst_fmt->fmt;

	switch (tkn_elem->token) {
	case SKL_TKN_MM_U32_INTF_PIN_ID:
		dst_fmt->id = tkn_elem->value;
		break;

	default:
		ret = skl_tplg_fill_fmt(dev, mod_fmt, tkn_elem->token,
					tkn_elem->value);
		if (ret < 0)
			return ret;
		break;
	}

	return 0;
}