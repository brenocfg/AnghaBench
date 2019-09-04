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
struct intel_sst_drv {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct intel_sst_drv* dev_get_drvdata (struct device*) ; 
 int sst_drain_stream (struct intel_sst_drv*,unsigned int,int) ; 

__attribute__((used)) static int sst_cdev_stream_partial_drain(struct device *dev,
		unsigned int str_id)
{
	struct intel_sst_drv *ctx = dev_get_drvdata(dev);

	return sst_drain_stream(ctx, str_id, true);
}