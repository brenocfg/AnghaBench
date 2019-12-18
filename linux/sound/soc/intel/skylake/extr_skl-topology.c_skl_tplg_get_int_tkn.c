#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_tplg_vendor_value_elem {int token; int value; } ;
struct skl_module_res {int id; int nr_input_pins; int nr_output_pins; } ;
struct skl_module_iface {int fmt_idx; } ;
struct skl_module {struct skl_module_iface* formats; struct skl_module_res* resources; } ;
struct TYPE_3__ {TYPE_2__* astate_cfg; } ;
struct skl_dev {int lib_count; int nr_modules; TYPE_1__ cfg; struct skl_module** modules; } ;
struct skl_astate_param {int kcps; int clk_src; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int count; struct skl_astate_param* astate_table; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SKL_IN_DIR_BIT_MASK ; 
 int SKL_MAX_ASTATE_CFG ; 
 int SKL_PIN_COUNT_MASK ; 
#define  SKL_TKN_MM_U32_CPC 162 
#define  SKL_TKN_MM_U32_CPS 161 
#define  SKL_TKN_MM_U32_DMA_SIZE 160 
#define  SKL_TKN_MM_U32_FMT_ID 159 
#define  SKL_TKN_MM_U32_INTF_PIN_ID 158 
#define  SKL_TKN_MM_U32_NUM_IN_FMT 157 
#define  SKL_TKN_MM_U32_NUM_OUT_FMT 156 
#define  SKL_TKN_MM_U32_PIN_BUF 155 
#define  SKL_TKN_MM_U32_RES_ID 154 
#define  SKL_TKN_MM_U32_RES_PIN_ID 153 
#define  SKL_TKN_MM_U8_MOD_IDX 152 
#define  SKL_TKN_MM_U8_NUM_INTF 151 
#define  SKL_TKN_MM_U8_NUM_RES 150 
#define  SKL_TKN_U32_ASTATE_CLK_SRC 149 
#define  SKL_TKN_U32_ASTATE_COUNT 148 
#define  SKL_TKN_U32_ASTATE_IDX 147 
#define  SKL_TKN_U32_ASTATE_KCPS 146 
#define  SKL_TKN_U32_DIR_PIN_COUNT 145 
#define  SKL_TKN_U32_FMT_BIT_DEPTH 144 
#define  SKL_TKN_U32_FMT_CH 143 
#define  SKL_TKN_U32_FMT_CH_CONFIG 142 
#define  SKL_TKN_U32_FMT_CH_MAP 141 
#define  SKL_TKN_U32_FMT_FREQ 140 
#define  SKL_TKN_U32_FMT_INTERLEAVE 139 
#define  SKL_TKN_U32_FMT_SAMPLE_SIZE 138 
#define  SKL_TKN_U32_FMT_SAMPLE_TYPE 137 
#define  SKL_TKN_U32_IBS 136 
#define  SKL_TKN_U32_LIB_COUNT 135 
#define  SKL_TKN_U32_MEM_PAGES 134 
#define  SKL_TKN_U32_OBS 133 
#define  SKL_TKN_U8_IN_PIN_TYPE 132 
#define  SKL_TKN_U8_IN_QUEUE_COUNT 131 
#define  SKL_TKN_U8_NUM_MOD 130 
#define  SKL_TKN_U8_OUT_PIN_TYPE 129 
#define  SKL_TKN_U8_OUT_QUEUE_COUNT 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct skl_module** devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (struct device*,size_t,int /*<<< orphan*/ ) ; 
 int skl_tplg_fill_mod_info (struct device*,struct snd_soc_tplg_vendor_value_elem*,struct skl_module*) ; 
 int skl_tplg_fill_res_tkn (struct device*,struct snd_soc_tplg_vendor_value_elem*,struct skl_module_res*,int,int) ; 
 int skl_tplg_manifest_fill_fmt (struct device*,struct skl_module_iface*,struct snd_soc_tplg_vendor_value_elem*,int,int) ; 
 size_t struct_size (TYPE_2__*,struct skl_astate_param*,int) ; 

__attribute__((used)) static int skl_tplg_get_int_tkn(struct device *dev,
		struct snd_soc_tplg_vendor_value_elem *tkn_elem,
		struct skl_dev *skl)
{
	int tkn_count = 0, ret;
	static int mod_idx, res_val_idx, intf_val_idx, dir, pin_idx;
	struct skl_module_res *res = NULL;
	struct skl_module_iface *fmt = NULL;
	struct skl_module *mod = NULL;
	static struct skl_astate_param *astate_table;
	static int astate_cfg_idx, count;
	int i;
	size_t size;

	if (skl->modules) {
		mod = skl->modules[mod_idx];
		res = &mod->resources[res_val_idx];
		fmt = &mod->formats[intf_val_idx];
	}

	switch (tkn_elem->token) {
	case SKL_TKN_U32_LIB_COUNT:
		skl->lib_count = tkn_elem->value;
		break;

	case SKL_TKN_U8_NUM_MOD:
		skl->nr_modules = tkn_elem->value;
		skl->modules = devm_kcalloc(dev, skl->nr_modules,
				sizeof(*skl->modules), GFP_KERNEL);
		if (!skl->modules)
			return -ENOMEM;

		for (i = 0; i < skl->nr_modules; i++) {
			skl->modules[i] = devm_kzalloc(dev,
					sizeof(struct skl_module), GFP_KERNEL);
			if (!skl->modules[i])
				return -ENOMEM;
		}
		break;

	case SKL_TKN_MM_U8_MOD_IDX:
		mod_idx = tkn_elem->value;
		break;

	case SKL_TKN_U32_ASTATE_COUNT:
		if (astate_table != NULL) {
			dev_err(dev, "More than one entry for A-State count");
			return -EINVAL;
		}

		if (tkn_elem->value > SKL_MAX_ASTATE_CFG) {
			dev_err(dev, "Invalid A-State count %d\n",
				tkn_elem->value);
			return -EINVAL;
		}

		size = struct_size(skl->cfg.astate_cfg, astate_table,
				   tkn_elem->value);
		skl->cfg.astate_cfg = devm_kzalloc(dev, size, GFP_KERNEL);
		if (!skl->cfg.astate_cfg)
			return -ENOMEM;

		astate_table = skl->cfg.astate_cfg->astate_table;
		count = skl->cfg.astate_cfg->count = tkn_elem->value;
		break;

	case SKL_TKN_U32_ASTATE_IDX:
		if (tkn_elem->value >= count) {
			dev_err(dev, "Invalid A-State index %d\n",
				tkn_elem->value);
			return -EINVAL;
		}

		astate_cfg_idx = tkn_elem->value;
		break;

	case SKL_TKN_U32_ASTATE_KCPS:
		astate_table[astate_cfg_idx].kcps = tkn_elem->value;
		break;

	case SKL_TKN_U32_ASTATE_CLK_SRC:
		astate_table[astate_cfg_idx].clk_src = tkn_elem->value;
		break;

	case SKL_TKN_U8_IN_PIN_TYPE:
	case SKL_TKN_U8_OUT_PIN_TYPE:
	case SKL_TKN_U8_IN_QUEUE_COUNT:
	case SKL_TKN_U8_OUT_QUEUE_COUNT:
	case SKL_TKN_MM_U8_NUM_RES:
	case SKL_TKN_MM_U8_NUM_INTF:
		ret = skl_tplg_fill_mod_info(dev, tkn_elem, mod);
		if (ret < 0)
			return ret;
		break;

	case SKL_TKN_U32_DIR_PIN_COUNT:
		dir = tkn_elem->value & SKL_IN_DIR_BIT_MASK;
		pin_idx = (tkn_elem->value & SKL_PIN_COUNT_MASK) >> 4;
		break;

	case SKL_TKN_MM_U32_RES_ID:
		if (!res)
			return -EINVAL;

		res->id = tkn_elem->value;
		res_val_idx = tkn_elem->value;
		break;

	case SKL_TKN_MM_U32_FMT_ID:
		if (!fmt)
			return -EINVAL;

		fmt->fmt_idx = tkn_elem->value;
		intf_val_idx = tkn_elem->value;
		break;

	case SKL_TKN_MM_U32_CPS:
	case SKL_TKN_MM_U32_DMA_SIZE:
	case SKL_TKN_MM_U32_CPC:
	case SKL_TKN_U32_MEM_PAGES:
	case SKL_TKN_U32_OBS:
	case SKL_TKN_U32_IBS:
	case SKL_TKN_MM_U32_RES_PIN_ID:
	case SKL_TKN_MM_U32_PIN_BUF:
		ret = skl_tplg_fill_res_tkn(dev, tkn_elem, res, pin_idx, dir);
		if (ret < 0)
			return ret;

		break;

	case SKL_TKN_MM_U32_NUM_IN_FMT:
		if (!fmt)
			return -EINVAL;

		res->nr_input_pins = tkn_elem->value;
		break;

	case SKL_TKN_MM_U32_NUM_OUT_FMT:
		if (!fmt)
			return -EINVAL;

		res->nr_output_pins = tkn_elem->value;
		break;

	case SKL_TKN_U32_FMT_CH:
	case SKL_TKN_U32_FMT_FREQ:
	case SKL_TKN_U32_FMT_BIT_DEPTH:
	case SKL_TKN_U32_FMT_SAMPLE_SIZE:
	case SKL_TKN_U32_FMT_CH_CONFIG:
	case SKL_TKN_U32_FMT_INTERLEAVE:
	case SKL_TKN_U32_FMT_SAMPLE_TYPE:
	case SKL_TKN_U32_FMT_CH_MAP:
	case SKL_TKN_MM_U32_INTF_PIN_ID:
		ret = skl_tplg_manifest_fill_fmt(dev, fmt, tkn_elem,
						 dir, pin_idx);
		if (ret < 0)
			return ret;
		break;

	default:
		dev_err(dev, "Not a manifest token %d\n", tkn_elem->token);
		return -EINVAL;
	}
	tkn_count++;

	return tkn_count;
}