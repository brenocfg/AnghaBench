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
struct intel_sst_drv {scalar_t__ sst_state; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int GET_USAGE_COUNT (struct device*) ; 
 scalar_t__ SST_RESET ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct intel_sst_drv* dev_get_drvdata (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int sst_load_fw (struct intel_sst_drv*) ; 
 int sst_pm_runtime_put (struct intel_sst_drv*) ; 
 int /*<<< orphan*/  sst_set_fw_state_locked (struct intel_sst_drv*,scalar_t__) ; 

__attribute__((used)) static int sst_power_control(struct device *dev, bool state)
{
	struct intel_sst_drv *ctx = dev_get_drvdata(dev);
	int ret = 0;
	int usage_count = 0;

	if (state) {
		ret = pm_runtime_get_sync(dev);
		usage_count = GET_USAGE_COUNT(dev);
		dev_dbg(ctx->dev, "Enable: pm usage count: %d\n", usage_count);
		if (ret < 0) {
			pm_runtime_put_sync(dev);
			dev_err(ctx->dev, "Runtime get failed with err: %d\n", ret);
			return ret;
		}
		if ((ctx->sst_state == SST_RESET) && (usage_count == 1)) {
			ret = sst_load_fw(ctx);
			if (ret) {
				dev_err(dev, "FW download fail %d\n", ret);
				sst_set_fw_state_locked(ctx, SST_RESET);
				ret = sst_pm_runtime_put(ctx);
			}
		}
	} else {
		usage_count = GET_USAGE_COUNT(dev);
		dev_dbg(ctx->dev, "Disable: pm usage count: %d\n", usage_count);
		return sst_pm_runtime_put(ctx);
	}
	return ret;
}