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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sst_dsp {int /*<<< orphan*/  dev; } ;
struct skl_module_table {TYPE_2__* mod_info; int /*<<< orphan*/  usage_cnt; } ;
typedef  int /*<<< orphan*/  mod_name ;
struct TYPE_4__ {TYPE_1__* fw; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct skl_module_table* skl_fill_module_table (struct sst_dsp*,char*,int /*<<< orphan*/ ) ; 
 int skl_get_module (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 struct skl_module_table* skl_module_get_from_id (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int skl_transfer_module (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int skl_load_module(struct sst_dsp *ctx, u16 mod_id, u8 *guid)
{
	struct skl_module_table *module_entry = NULL;
	int ret = 0;
	char mod_name[64]; /* guid str = 32 chars + 4 hyphens */

	snprintf(mod_name, sizeof(mod_name), "intel/dsp_fw_%pUL.bin", guid);

	module_entry = skl_module_get_from_id(ctx, mod_id);
	if (module_entry == NULL) {
		module_entry = skl_fill_module_table(ctx, mod_name, mod_id);
		if (module_entry == NULL) {
			dev_err(ctx->dev, "Failed to Load module\n");
			return -EINVAL;
		}
	}

	if (!module_entry->usage_cnt) {
		ret = skl_transfer_module(ctx, module_entry->mod_info->fw->data,
				module_entry->mod_info->fw->size,
				mod_id, 0, true);
		if (ret < 0) {
			dev_err(ctx->dev, "Failed to Load module\n");
			return ret;
		}
	}

	ret = skl_get_module(ctx, mod_id);

	return ret;
}