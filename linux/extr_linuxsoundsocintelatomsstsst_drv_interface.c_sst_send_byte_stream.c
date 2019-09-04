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
struct snd_sst_bytes_v2 {int dummy; } ;
struct intel_sst_drv {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct intel_sst_drv* dev_get_drvdata (struct device*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_pm_runtime_put (struct intel_sst_drv*) ; 
 int sst_send_byte_stream_mrfld (struct intel_sst_drv*,struct snd_sst_bytes_v2*) ; 

__attribute__((used)) static int sst_send_byte_stream(struct device *dev,
		struct snd_sst_bytes_v2 *bytes)
{
	int ret_val = 0;
	struct intel_sst_drv *ctx = dev_get_drvdata(dev);

	if (NULL == bytes)
		return -EINVAL;
	ret_val = pm_runtime_get_sync(ctx->dev);
	if (ret_val < 0) {
		pm_runtime_put_sync(ctx->dev);
		return ret_val;
	}

	ret_val = sst_send_byte_stream_mrfld(ctx, bytes);
	sst_pm_runtime_put(ctx);

	return ret_val;
}