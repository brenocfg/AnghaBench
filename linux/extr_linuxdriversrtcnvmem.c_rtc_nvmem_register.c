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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct rtc_device {scalar_t__ nvram_old_abi; int /*<<< orphan*/  nvmem; int /*<<< orphan*/  owner; TYPE_1__ dev; } ;
struct nvmem_config {int /*<<< orphan*/  size; int /*<<< orphan*/  owner; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmem_register (struct nvmem_config*) ; 
 int /*<<< orphan*/  rtc_nvram_register (struct rtc_device*,int /*<<< orphan*/ ) ; 

int rtc_nvmem_register(struct rtc_device *rtc,
		       struct nvmem_config *nvmem_config)
{
	if (!IS_ERR_OR_NULL(rtc->nvmem))
		return -EBUSY;

	if (!nvmem_config)
		return -ENODEV;

	nvmem_config->dev = rtc->dev.parent;
	nvmem_config->owner = rtc->owner;
	rtc->nvmem = nvmem_register(nvmem_config);
	if (IS_ERR(rtc->nvmem))
		return PTR_ERR(rtc->nvmem);

	/* Register the old ABI */
	if (rtc->nvram_old_abi)
		rtc_nvram_register(rtc, nvmem_config->size);

	return 0;
}