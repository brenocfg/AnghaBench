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
typedef  int /*<<< orphan*/  obs_hotkeys_platform_t ;
typedef  int /*<<< orphan*/  IOHIDElementRef ;
typedef  int /*<<< orphan*/  IOHIDDeviceRef ;
typedef  scalar_t__ CFIndex ;
typedef  int /*<<< orphan*/  CFArrayRef ;

/* Variables and functions */
 scalar_t__ CFArrayGetCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFArrayGetValueAtIndex (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOHIDDeviceCopyMatchingElements (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IOHIDElementGetUsagePage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ kHIDPage_KeyboardOrKeypad ; 
 int /*<<< orphan*/  kIOHIDOptionsTypeNone ; 
 int /*<<< orphan*/  load_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void load_keyboard(obs_hotkeys_platform_t *plat,
		IOHIDDeviceRef keyboard)
{
	CFArrayRef keys = IOHIDDeviceCopyMatchingElements(keyboard, NULL,
							kIOHIDOptionsTypeNone);

	if (!keys) {
		blog(LOG_ERROR, "hotkeys-cocoa: Getting keyboard keys failed");
		return;
	}

	CFIndex count = CFArrayGetCount(keys);
	if (!count) {
		blog(LOG_ERROR, "hotkeys-cocoa: Keyboard has no keys");
		CFRelease(keys);
		return;
	}

	for (CFIndex i = 0; i < count; i++) {
		IOHIDElementRef key =
			(IOHIDElementRef)CFArrayGetValueAtIndex(keys, i);

		// Skip non-matching keys elements
		if (IOHIDElementGetUsagePage(key) != kHIDPage_KeyboardOrKeypad)
			continue;

		load_key(plat, key);
	}

	CFRelease(keys);
}