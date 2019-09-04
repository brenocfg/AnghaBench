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
struct skl_specific_cfg {int caps_size; int param_id; scalar_t__ caps; int /*<<< orphan*/  set_params; } ;
struct skl_module_cfg {struct skl_specific_cfg formats_config; } ;
struct skl_mic_sel_config {scalar_t__ flags; int /*<<< orphan*/  mic_switch; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SKL_MIC_SEL_SWITCH ; 
 int /*<<< orphan*/  SKL_PARAM_SET ; 
 scalar_t__ devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct skl_mic_sel_config*,int) ; 

__attribute__((used)) static int skl_fill_mic_sel_params(struct skl_module_cfg *mconfig,
	struct skl_mic_sel_config *mic_cfg, struct device *dev)
{
	struct skl_specific_cfg *sp_cfg = &mconfig->formats_config;

	sp_cfg->caps_size = sizeof(struct skl_mic_sel_config);
	sp_cfg->set_params = SKL_PARAM_SET;
	sp_cfg->param_id = 0x00;
	if (!sp_cfg->caps) {
		sp_cfg->caps = devm_kzalloc(dev, sp_cfg->caps_size, GFP_KERNEL);
		if (!sp_cfg->caps)
			return -ENOMEM;
	}

	mic_cfg->mic_switch = SKL_MIC_SEL_SWITCH;
	mic_cfg->flags = 0;
	memcpy(sp_cfg->caps, mic_cfg, sp_cfg->caps_size);

	return 0;
}