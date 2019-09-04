#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  manager; } ;
typedef  TYPE_1__ obs_hotkeys_platform_t ;
typedef  int /*<<< orphan*/  UInt32 ;
typedef  int /*<<< orphan*/ * CFSetRef ;
typedef  int /*<<< orphan*/ * CFDictionaryRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int CFSetGetCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IOHIDManagerCopyDevices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOHIDManagerSetDeviceMatching (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * copy_device_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CFSetRef copy_devices(obs_hotkeys_platform_t *plat,
		UInt32 page, UInt32 usage)
{
	CFDictionaryRef mask = copy_device_mask(page, usage);
	IOHIDManagerSetDeviceMatching(plat->manager, mask);
	CFRelease(mask);

	CFSetRef devices = IOHIDManagerCopyDevices(plat->manager);
	if (!devices)
		return NULL;

	if (CFSetGetCount(devices) < 1) {
		CFRelease(devices);
		return NULL;
	}

	return devices;
}