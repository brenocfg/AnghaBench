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
struct intel_sst_drv {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  STREAM_RUNNING ; 
 struct intel_sst_drv* dev_get_drvdata (struct device*) ; 
 struct stream_info* get_stream_info (struct intel_sst_drv*,unsigned int) ; 
 int sst_start_stream (struct intel_sst_drv*,unsigned int) ; 

__attribute__((used)) static int sst_cdev_stream_start(struct device *dev, unsigned int str_id)
{
	struct stream_info *str_info;
	struct intel_sst_drv *ctx = dev_get_drvdata(dev);

	str_info = get_stream_info(ctx, str_id);
	if (!str_info)
		return -EINVAL;
	str_info->prev = str_info->status;
	str_info->status = STREAM_RUNNING;
	return sst_start_stream(ctx, str_id);
}