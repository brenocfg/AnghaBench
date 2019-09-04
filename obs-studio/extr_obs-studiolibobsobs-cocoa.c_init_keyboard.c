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
typedef  int /*<<< orphan*/  IOHIDDeviceRef ;
typedef  scalar_t__ CFTypeRef ;
typedef  int /*<<< orphan*/  CFSetRef ;
typedef  int CFIndex ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int CFSetGetCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFSetGetValues (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  copy_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kHIDPage_GenericDesktop ; 
 int /*<<< orphan*/  kHIDUsage_GD_Keyboard ; 
 int /*<<< orphan*/  load_keyboard (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool init_keyboard(obs_hotkeys_platform_t *plat)
{
	CFSetRef keyboards = copy_devices(plat, kHIDPage_GenericDesktop,
						kHIDUsage_GD_Keyboard);
	if (!keyboards)
		return false;

	CFIndex count = CFSetGetCount(keyboards);

	CFTypeRef devices[count];
	CFSetGetValues(keyboards, devices);

	for (CFIndex i = 0; i < count; i++)
		load_keyboard(plat, (IOHIDDeviceRef)devices[i]);

	CFRelease(keyboards);
	return true;
}