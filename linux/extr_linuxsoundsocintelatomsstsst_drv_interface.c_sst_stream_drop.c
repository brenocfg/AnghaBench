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
struct stream_info {int /*<<< orphan*/  status; int /*<<< orphan*/  prev; } ;
struct intel_sst_drv {scalar_t__ sst_state; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SST_FW_RUNNING ; 
 int /*<<< orphan*/  STREAM_INIT ; 
 int /*<<< orphan*/  STREAM_UN_INIT ; 
 struct intel_sst_drv* dev_get_drvdata (struct device*) ; 
 struct stream_info* get_stream_info (struct intel_sst_drv*,int) ; 
 int sst_drop_stream (struct intel_sst_drv*,int) ; 

__attribute__((used)) static int sst_stream_drop(struct device *dev, int str_id)
{
	struct stream_info *str_info;
	struct intel_sst_drv *ctx = dev_get_drvdata(dev);

	if (ctx->sst_state != SST_FW_RUNNING)
		return 0;

	str_info = get_stream_info(ctx, str_id);
	if (!str_info)
		return -EINVAL;
	str_info->prev = STREAM_UN_INIT;
	str_info->status = STREAM_INIT;
	return sst_drop_stream(ctx, str_id);
}