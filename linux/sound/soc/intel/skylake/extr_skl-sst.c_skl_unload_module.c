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
typedef  int /*<<< orphan*/  u16 ;
struct sst_dsp {int /*<<< orphan*/  dev; struct skl_dev* thread_context; } ;
struct skl_dev {int /*<<< orphan*/  ipc; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SKL_NUM_MODULES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  skl_get_module (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int skl_ipc_unload_modules (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int skl_put_module (struct sst_dsp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skl_unload_module(struct sst_dsp *ctx, u16 mod_id)
{
	int usage_cnt;
	struct skl_dev *skl = ctx->thread_context;
	int ret = 0;

	usage_cnt = skl_put_module(ctx, mod_id);
	if (usage_cnt < 0) {
		dev_err(ctx->dev, "Module bad usage cnt!:%d\n", usage_cnt);
		return -EIO;
	}

	/* if module is used by others return, no need to unload */
	if (usage_cnt > 0)
		return 0;

	ret = skl_ipc_unload_modules(&skl->ipc,
			SKL_NUM_MODULES, &mod_id);
	if (ret < 0) {
		dev_err(ctx->dev, "Failed to UnLoad module\n");
		skl_get_module(ctx, mod_id);
		return ret;
	}

	return ret;
}