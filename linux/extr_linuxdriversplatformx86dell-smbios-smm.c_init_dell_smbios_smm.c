#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int GFP_DMA32 ; 
 int GFP_KERNEL ; 
 scalar_t__ __get_free_page (int) ; 
 void* buffer ; 
 int dell_smbios_register_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dell_smbios_smm_call ; 
 int /*<<< orphan*/  dmi_walk (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_cmd_address ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 TYPE_1__* platform_device ; 
 int platform_device_add (TYPE_1__*) ; 
 TYPE_1__* platform_device_alloc (char*,int) ; 
 int /*<<< orphan*/  platform_device_del (TYPE_1__*) ; 
 int /*<<< orphan*/  platform_device_put (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ test_wsmt_enabled () ; 

int init_dell_smbios_smm(void)
{
	int ret;
	/*
	 * Allocate buffer below 4GB for SMI data--only 32-bit physical addr
	 * is passed to SMI handler.
	 */
	buffer = (void *)__get_free_page(GFP_KERNEL | GFP_DMA32);
	if (!buffer)
		return -ENOMEM;

	dmi_walk(find_cmd_address, NULL);

	if (test_wsmt_enabled()) {
		pr_debug("Disabling due to WSMT enabled\n");
		ret = -ENODEV;
		goto fail_wsmt;
	}

	platform_device = platform_device_alloc("dell-smbios", 1);
	if (!platform_device) {
		ret = -ENOMEM;
		goto fail_platform_device_alloc;
	}

	ret = platform_device_add(platform_device);
	if (ret)
		goto fail_platform_device_add;

	ret = dell_smbios_register_device(&platform_device->dev,
					  &dell_smbios_smm_call);
	if (ret)
		goto fail_register;

	return 0;

fail_register:
	platform_device_del(platform_device);

fail_platform_device_add:
	platform_device_put(platform_device);

fail_wsmt:
fail_platform_device_alloc:
	free_page((unsigned long)buffer);
	return ret;
}