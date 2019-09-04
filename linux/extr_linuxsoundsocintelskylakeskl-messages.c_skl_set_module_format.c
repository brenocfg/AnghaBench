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
typedef  int /*<<< orphan*/  u16 ;
struct skl_sst {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  module_id; } ;
struct skl_module_cfg {int m_type; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  SKL_MODULE_TYPE_ALGO 134 
#define  SKL_MODULE_TYPE_BASE_OUTFMT 133 
#define  SKL_MODULE_TYPE_COPIER 132 
#define  SKL_MODULE_TYPE_KPB 131 
#define  SKL_MODULE_TYPE_MIC_SELECT 130 
#define  SKL_MODULE_TYPE_SRCINT 129 
#define  SKL_MODULE_TYPE_UPDWMIX 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump_debug (char*,int /*<<< orphan*/ ,int,int,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skl_get_module_param_size (struct skl_sst*,struct skl_module_cfg*) ; 
 int /*<<< orphan*/  skl_set_algo_format (struct skl_sst*,struct skl_module_cfg*,void*) ; 
 int /*<<< orphan*/  skl_set_base_module_format (struct skl_sst*,struct skl_module_cfg*,void*) ; 
 int /*<<< orphan*/  skl_set_base_outfmt_format (struct skl_sst*,struct skl_module_cfg*,void*) ; 
 int /*<<< orphan*/  skl_set_copier_format (struct skl_sst*,struct skl_module_cfg*,void*) ; 
 int /*<<< orphan*/  skl_set_src_format (struct skl_sst*,struct skl_module_cfg*,void*) ; 
 int /*<<< orphan*/  skl_set_updown_mixer_format (struct skl_sst*,struct skl_module_cfg*,void*) ; 

__attribute__((used)) static int skl_set_module_format(struct skl_sst *ctx,
			struct skl_module_cfg *module_config,
			u16 *module_config_size,
			void **param_data)
{
	u16 param_size;

	param_size  = skl_get_module_param_size(ctx, module_config);

	*param_data = kzalloc(param_size, GFP_KERNEL);
	if (NULL == *param_data)
		return -ENOMEM;

	*module_config_size = param_size;

	switch (module_config->m_type) {
	case SKL_MODULE_TYPE_COPIER:
		skl_set_copier_format(ctx, module_config, *param_data);
		break;

	case SKL_MODULE_TYPE_SRCINT:
		skl_set_src_format(ctx, module_config, *param_data);
		break;

	case SKL_MODULE_TYPE_UPDWMIX:
		skl_set_updown_mixer_format(ctx, module_config, *param_data);
		break;

	case SKL_MODULE_TYPE_ALGO:
		skl_set_algo_format(ctx, module_config, *param_data);
		break;

	case SKL_MODULE_TYPE_BASE_OUTFMT:
	case SKL_MODULE_TYPE_MIC_SELECT:
	case SKL_MODULE_TYPE_KPB:
		skl_set_base_outfmt_format(ctx, module_config, *param_data);
		break;

	default:
		skl_set_base_module_format(ctx, module_config, *param_data);
		break;

	}

	dev_dbg(ctx->dev, "Module type=%d config size: %d bytes\n",
			module_config->id.module_id, param_size);
	print_hex_dump_debug("Module params:", DUMP_PREFIX_OFFSET, 8, 4,
			*param_data, param_size, false);
	return 0;
}