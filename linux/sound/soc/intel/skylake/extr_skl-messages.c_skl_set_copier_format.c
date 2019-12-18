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
struct skl_module_cfg {int dummy; } ;
struct skl_dev {int dummy; } ;
struct skl_audio_data_format {int dummy; } ;
struct skl_cpr_cfg {struct skl_audio_data_format out_fmt; } ;
struct skl_base_cfg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  skl_set_base_module_format (struct skl_dev*,struct skl_module_cfg*,struct skl_base_cfg*) ; 
 int /*<<< orphan*/  skl_setup_cpr_gateway_cfg (struct skl_dev*,struct skl_module_cfg*,struct skl_cpr_cfg*) ; 
 int /*<<< orphan*/  skl_setup_out_format (struct skl_dev*,struct skl_module_cfg*,struct skl_audio_data_format*) ; 

__attribute__((used)) static void skl_set_copier_format(struct skl_dev *skl,
			struct skl_module_cfg *mconfig,
			struct skl_cpr_cfg *cpr_mconfig)
{
	struct skl_audio_data_format *out_fmt = &cpr_mconfig->out_fmt;
	struct skl_base_cfg *base_cfg = (struct skl_base_cfg *)cpr_mconfig;

	skl_set_base_module_format(skl, mconfig, base_cfg);

	skl_setup_out_format(skl, mconfig, out_fmt);
	skl_setup_cpr_gateway_cfg(skl, mconfig, cpr_mconfig);
}