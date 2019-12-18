#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_tplg_vendor_value_elem {int token; int value; } ;
struct skl_module_res {int dummy; } ;
struct skl_module_iface {int dummy; } ;
struct TYPE_10__ {int caps_size; int set_params; int param_id; } ;
struct TYPE_8__ {int instance_id; } ;
struct skl_module_cfg {int res_idx; int fmt_idx; int time_slot; int core_id; int m_type; int dev_type; int hw_conn_type; int vbus_id; int params_fixup; int converter; int d0i3_caps; int domain; int dma_buffer_size; TYPE_4__ formats_config; TYPE_3__* mod_cfg; TYPE_5__* pipe; TYPE_2__ id; void* m_out_pin; void* m_in_pin; TYPE_1__* module; } ;
struct skl_dev {scalar_t__ nr_modules; } ;
struct device {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  nr_cfgs; } ;
struct TYPE_9__ {int res_idx; int fmt_idx; } ;
struct TYPE_7__ {int max_input_pins; int max_output_pins; struct skl_module_iface* formats; struct skl_module_res* resources; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_IN_QUEUE ; 
 int /*<<< orphan*/  MAX_OUT_QUEUE ; 
 int SKL_IN_DIR_BIT_MASK ; 
 int SKL_PIN_COUNT_MASK ; 
#define  SKL_TKN_CFG_MOD_FMT_ID 179 
#define  SKL_TKN_CFG_MOD_RES_ID 178 
 int SKL_TKN_MAX ; 
#define  SKL_TKN_U16_MOD_INST_ID 177 
#define  SKL_TKN_U32_CAPS_PARAMS_ID 176 
#define  SKL_TKN_U32_CAPS_SET_PARAMS 175 
#define  SKL_TKN_U32_CAPS_SIZE 174 
#define  SKL_TKN_U32_CFG_FREQ 173 
#define  SKL_TKN_U32_CONVERTER 172 
#define  SKL_TKN_U32_D0I3_CAPS 171 
#define  SKL_TKN_U32_DIR_PIN_COUNT 170 
#define  SKL_TKN_U32_DMA_BUF_SIZE 169 
#define  SKL_TKN_U32_FMT_BIT_DEPTH 168 
#define  SKL_TKN_U32_FMT_CH 167 
#define  SKL_TKN_U32_FMT_CH_CONFIG 166 
#define  SKL_TKN_U32_FMT_CH_MAP 165 
#define  SKL_TKN_U32_FMT_FREQ 164 
#define  SKL_TKN_U32_FMT_INTERLEAVE 163 
#define  SKL_TKN_U32_FMT_SAMPLE_SIZE 162 
#define  SKL_TKN_U32_FMT_SAMPLE_TYPE 161 
#define  SKL_TKN_U32_IBS 160 
#define  SKL_TKN_U32_MAX_MCPS 159 
#define  SKL_TKN_U32_MEM_PAGES 158 
#define  SKL_TKN_U32_NUM_CONFIGS 157 
#define  SKL_TKN_U32_OBS 156 
#define  SKL_TKN_U32_PARAMS_FIXUP 155 
#define  SKL_TKN_U32_PATH_MEM_PGS 154 
#define  SKL_TKN_U32_PIN_INST_ID 153 
#define  SKL_TKN_U32_PIN_MOD_ID 152 
#define  SKL_TKN_U32_PIPE_CONFIG_ID 151 
#define  SKL_TKN_U32_PIPE_CONN_TYPE 150 
#define  SKL_TKN_U32_PIPE_DIRECTION 149 
#define  SKL_TKN_U32_PIPE_ID 148 
#define  SKL_TKN_U32_PIPE_MEM_PGS 147 
#define  SKL_TKN_U32_PIPE_PRIORITY 146 
#define  SKL_TKN_U32_PMODE 145 
#define  SKL_TKN_U32_PROC_DOMAIN 144 
#define  SKL_TKN_U32_VBUS_ID 143 
#define  SKL_TKN_U8_CFG_BPS 142 
#define  SKL_TKN_U8_CFG_CHAN 141 
#define  SKL_TKN_U8_CONN_TYPE 140 
#define  SKL_TKN_U8_CORE_ID 139 
#define  SKL_TKN_U8_DEV_TYPE 138 
#define  SKL_TKN_U8_DYN_IN_PIN 137 
#define  SKL_TKN_U8_DYN_OUT_PIN 136 
#define  SKL_TKN_U8_HW_CONN_TYPE 135 
#define  SKL_TKN_U8_IN_PIN_TYPE 134 
#define  SKL_TKN_U8_IN_QUEUE_COUNT 133 
#define  SKL_TKN_U8_MOD_TYPE 132 
#define  SKL_TKN_U8_OUT_PIN_TYPE 131 
#define  SKL_TKN_U8_OUT_QUEUE_COUNT 130 
#define  SKL_TKN_U8_TIME_SLOT 129 
#define  SKL_TKN_UUID 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 void* devm_kcalloc (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int skl_tplg_add_pipe (struct device*,struct skl_module_cfg*,struct skl_dev*,struct snd_soc_tplg_vendor_value_elem*) ; 
 int /*<<< orphan*/  skl_tplg_fill_pin_dynamic_val (void*,int /*<<< orphan*/ ,int) ; 
 int skl_tplg_fill_pins_info (struct device*,struct skl_module_cfg*,struct snd_soc_tplg_vendor_value_elem*,int,int) ; 
 int skl_tplg_fill_pipe_cfg (struct device*,TYPE_5__*,int,int,int,int) ; 
 int skl_tplg_fill_pipe_tkn (struct device*,TYPE_5__*,int,int) ; 
 int skl_tplg_fill_res_tkn (struct device*,struct snd_soc_tplg_vendor_value_elem*,struct skl_module_res*,int,int) ; 
 int skl_tplg_widget_fill_fmt (struct device*,struct skl_module_iface*,int,int,int,int) ; 

__attribute__((used)) static int skl_tplg_get_token(struct device *dev,
		struct snd_soc_tplg_vendor_value_elem *tkn_elem,
		struct skl_dev *skl, struct skl_module_cfg *mconfig)
{
	int tkn_count = 0;
	int ret;
	static int is_pipe_exists;
	static int pin_index, dir, conf_idx;
	struct skl_module_iface *iface = NULL;
	struct skl_module_res *res = NULL;
	int res_idx = mconfig->res_idx;
	int fmt_idx = mconfig->fmt_idx;

	/*
	 * If the manifest structure contains no modules, fill all
	 * the module data to 0th index.
	 * res_idx and fmt_idx are default set to 0.
	 */
	if (skl->nr_modules == 0) {
		res = &mconfig->module->resources[res_idx];
		iface = &mconfig->module->formats[fmt_idx];
	}

	if (tkn_elem->token > SKL_TKN_MAX)
		return -EINVAL;

	switch (tkn_elem->token) {
	case SKL_TKN_U8_IN_QUEUE_COUNT:
		mconfig->module->max_input_pins = tkn_elem->value;
		break;

	case SKL_TKN_U8_OUT_QUEUE_COUNT:
		mconfig->module->max_output_pins = tkn_elem->value;
		break;

	case SKL_TKN_U8_DYN_IN_PIN:
		if (!mconfig->m_in_pin)
			mconfig->m_in_pin =
				devm_kcalloc(dev, MAX_IN_QUEUE,
					     sizeof(*mconfig->m_in_pin),
					     GFP_KERNEL);
		if (!mconfig->m_in_pin)
			return -ENOMEM;

		skl_tplg_fill_pin_dynamic_val(mconfig->m_in_pin, MAX_IN_QUEUE,
					      tkn_elem->value);
		break;

	case SKL_TKN_U8_DYN_OUT_PIN:
		if (!mconfig->m_out_pin)
			mconfig->m_out_pin =
				devm_kcalloc(dev, MAX_IN_QUEUE,
					     sizeof(*mconfig->m_in_pin),
					     GFP_KERNEL);
		if (!mconfig->m_out_pin)
			return -ENOMEM;

		skl_tplg_fill_pin_dynamic_val(mconfig->m_out_pin, MAX_OUT_QUEUE,
					      tkn_elem->value);
		break;

	case SKL_TKN_U8_TIME_SLOT:
		mconfig->time_slot = tkn_elem->value;
		break;

	case SKL_TKN_U8_CORE_ID:
		mconfig->core_id = tkn_elem->value;
		break;

	case SKL_TKN_U8_MOD_TYPE:
		mconfig->m_type = tkn_elem->value;
		break;

	case SKL_TKN_U8_DEV_TYPE:
		mconfig->dev_type = tkn_elem->value;
		break;

	case SKL_TKN_U8_HW_CONN_TYPE:
		mconfig->hw_conn_type = tkn_elem->value;
		break;

	case SKL_TKN_U16_MOD_INST_ID:
		mconfig->id.instance_id =
		tkn_elem->value;
		break;

	case SKL_TKN_U32_MEM_PAGES:
	case SKL_TKN_U32_MAX_MCPS:
	case SKL_TKN_U32_OBS:
	case SKL_TKN_U32_IBS:
		ret = skl_tplg_fill_res_tkn(dev, tkn_elem, res, pin_index, dir);
		if (ret < 0)
			return ret;

		break;

	case SKL_TKN_U32_VBUS_ID:
		mconfig->vbus_id = tkn_elem->value;
		break;

	case SKL_TKN_U32_PARAMS_FIXUP:
		mconfig->params_fixup = tkn_elem->value;
		break;

	case SKL_TKN_U32_CONVERTER:
		mconfig->converter = tkn_elem->value;
		break;

	case SKL_TKN_U32_D0I3_CAPS:
		mconfig->d0i3_caps = tkn_elem->value;
		break;

	case SKL_TKN_U32_PIPE_ID:
		ret = skl_tplg_add_pipe(dev,
				mconfig, skl, tkn_elem);

		if (ret < 0) {
			if (ret == -EEXIST) {
				is_pipe_exists = 1;
				break;
			}
			return is_pipe_exists;
		}

		break;

	case SKL_TKN_U32_PIPE_CONFIG_ID:
		conf_idx = tkn_elem->value;
		break;

	case SKL_TKN_U32_PIPE_CONN_TYPE:
	case SKL_TKN_U32_PIPE_PRIORITY:
	case SKL_TKN_U32_PIPE_MEM_PGS:
	case SKL_TKN_U32_PMODE:
	case SKL_TKN_U32_PIPE_DIRECTION:
	case SKL_TKN_U32_NUM_CONFIGS:
		if (is_pipe_exists) {
			ret = skl_tplg_fill_pipe_tkn(dev, mconfig->pipe,
					tkn_elem->token, tkn_elem->value);
			if (ret < 0)
				return ret;
		}

		break;

	case SKL_TKN_U32_PATH_MEM_PGS:
	case SKL_TKN_U32_CFG_FREQ:
	case SKL_TKN_U8_CFG_CHAN:
	case SKL_TKN_U8_CFG_BPS:
		if (mconfig->pipe->nr_cfgs) {
			ret = skl_tplg_fill_pipe_cfg(dev, mconfig->pipe,
					tkn_elem->token, tkn_elem->value,
					conf_idx, dir);
			if (ret < 0)
				return ret;
		}
		break;

	case SKL_TKN_CFG_MOD_RES_ID:
		mconfig->mod_cfg[conf_idx].res_idx = tkn_elem->value;
		break;

	case SKL_TKN_CFG_MOD_FMT_ID:
		mconfig->mod_cfg[conf_idx].fmt_idx = tkn_elem->value;
		break;

	/*
	 * SKL_TKN_U32_DIR_PIN_COUNT token has the value for both
	 * direction and the pin count. The first four bits represent
	 * direction and next four the pin count.
	 */
	case SKL_TKN_U32_DIR_PIN_COUNT:
		dir = tkn_elem->value & SKL_IN_DIR_BIT_MASK;
		pin_index = (tkn_elem->value &
			SKL_PIN_COUNT_MASK) >> 4;

		break;

	case SKL_TKN_U32_FMT_CH:
	case SKL_TKN_U32_FMT_FREQ:
	case SKL_TKN_U32_FMT_BIT_DEPTH:
	case SKL_TKN_U32_FMT_SAMPLE_SIZE:
	case SKL_TKN_U32_FMT_CH_CONFIG:
	case SKL_TKN_U32_FMT_INTERLEAVE:
	case SKL_TKN_U32_FMT_SAMPLE_TYPE:
	case SKL_TKN_U32_FMT_CH_MAP:
		ret = skl_tplg_widget_fill_fmt(dev, iface, tkn_elem->token,
				tkn_elem->value, dir, pin_index);

		if (ret < 0)
			return ret;

		break;

	case SKL_TKN_U32_PIN_MOD_ID:
	case SKL_TKN_U32_PIN_INST_ID:
	case SKL_TKN_UUID:
		ret = skl_tplg_fill_pins_info(dev,
				mconfig, tkn_elem, dir,
				pin_index);
		if (ret < 0)
			return ret;

		break;

	case SKL_TKN_U32_CAPS_SIZE:
		mconfig->formats_config.caps_size =
			tkn_elem->value;

		break;

	case SKL_TKN_U32_CAPS_SET_PARAMS:
		mconfig->formats_config.set_params =
				tkn_elem->value;
		break;

	case SKL_TKN_U32_CAPS_PARAMS_ID:
		mconfig->formats_config.param_id =
				tkn_elem->value;
		break;

	case SKL_TKN_U32_PROC_DOMAIN:
		mconfig->domain =
			tkn_elem->value;

		break;

	case SKL_TKN_U32_DMA_BUF_SIZE:
		mconfig->dma_buffer_size = tkn_elem->value;
		break;

	case SKL_TKN_U8_IN_PIN_TYPE:
	case SKL_TKN_U8_OUT_PIN_TYPE:
	case SKL_TKN_U8_CONN_TYPE:
		break;

	default:
		dev_err(dev, "Token %d not handled\n",
				tkn_elem->token);
		return -EINVAL;
	}

	tkn_count++;

	return tkn_count;
}