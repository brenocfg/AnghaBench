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
struct intel_sst_drv {unsigned int dev_id; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct intel_sst_drv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 

int sst_alloc_drv_context(struct intel_sst_drv **ctx,
		struct device *dev, unsigned int dev_id)
{
	*ctx = devm_kzalloc(dev, sizeof(struct intel_sst_drv), GFP_KERNEL);
	if (!(*ctx))
		return -ENOMEM;

	(*ctx)->dev = dev;
	(*ctx)->dev_id = dev_id;

	return 0;
}