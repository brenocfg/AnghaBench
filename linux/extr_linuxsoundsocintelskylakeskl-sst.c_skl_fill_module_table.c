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
struct sst_dsp {int /*<<< orphan*/  module_list; int /*<<< orphan*/  dev; } ;
struct skl_module_table {int /*<<< orphan*/  list; TYPE_1__* mod_info; } ;
struct firmware {int dummy; } ;
struct TYPE_2__ {int mod_id; struct firmware const* fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*,int) ; 
 void* devm_kzalloc (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct skl_module_table *skl_fill_module_table(struct sst_dsp *ctx,
						char *mod_name, int mod_id)
{
	const struct firmware *fw;
	struct skl_module_table *skl_module;
	unsigned int size;
	int ret;

	ret = request_firmware(&fw, mod_name, ctx->dev);
	if (ret < 0) {
		dev_err(ctx->dev, "Request Module %s failed :%d\n",
							mod_name, ret);
		return NULL;
	}

	skl_module = devm_kzalloc(ctx->dev, sizeof(*skl_module), GFP_KERNEL);
	if (skl_module == NULL) {
		release_firmware(fw);
		return NULL;
	}

	size = sizeof(*skl_module->mod_info);
	skl_module->mod_info = devm_kzalloc(ctx->dev, size, GFP_KERNEL);
	if (skl_module->mod_info == NULL) {
		release_firmware(fw);
		return NULL;
	}

	skl_module->mod_info->mod_id = mod_id;
	skl_module->mod_info->fw = fw;
	list_add(&skl_module->list, &ctx->module_list);

	return skl_module;
}