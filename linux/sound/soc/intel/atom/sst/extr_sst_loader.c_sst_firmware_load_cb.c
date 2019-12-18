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
struct intel_sst_drv {scalar_t__ sst_state; int /*<<< orphan*/  sst_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/ * fw_in_mem; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 scalar_t__ SST_RESET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int /*<<< orphan*/  sst_cache_and_parse_fw (struct intel_sst_drv*,struct firmware const*) ; 

void sst_firmware_load_cb(const struct firmware *fw, void *context)
{
	struct intel_sst_drv *ctx = context;

	dev_dbg(ctx->dev, "Enter\n");

	if (fw == NULL) {
		dev_err(ctx->dev, "request fw failed\n");
		return;
	}

	mutex_lock(&ctx->sst_lock);

	if (ctx->sst_state != SST_RESET ||
			ctx->fw_in_mem != NULL) {
		release_firmware(fw);
		mutex_unlock(&ctx->sst_lock);
		return;
	}

	dev_dbg(ctx->dev, "Request Fw completed\n");
	sst_cache_and_parse_fw(ctx, fw);
	mutex_unlock(&ctx->sst_lock);
}