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
struct TYPE_6__ {int /*<<< orphan*/  manager; scalar_t__ layout_data; int /*<<< orphan*/ * layout; int /*<<< orphan*/  tis; } ;
typedef  TYPE_1__ obs_hotkeys_platform_t ;
typedef  int /*<<< orphan*/  UCKeyboardLayout ;
typedef  scalar_t__ IOReturn ;
typedef  scalar_t__ CFDataRef ;

/* Variables and functions */
 scalar_t__ CFDataGetBytePtr (scalar_t__) ; 
 int /*<<< orphan*/  CFRetain (scalar_t__) ; 
 int /*<<< orphan*/  IOHIDManagerCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IOHIDManagerOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  TISCopyCurrentKeyboardLayoutInputSource () ; 
 scalar_t__ TISGetInputSourceProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* bzalloc (int) ; 
 int /*<<< orphan*/  hotkeys_release (TYPE_1__*) ; 
 int /*<<< orphan*/  init_keyboard (TYPE_1__*) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kIOHIDOptionsTypeNone ; 
 scalar_t__ kIOReturnSuccess ; 
 int /*<<< orphan*/  kTISPropertyUnicodeKeyLayoutData ; 

__attribute__((used)) static bool init_hotkeys_platform(obs_hotkeys_platform_t **plat_)
{
	if (!plat_)
		return false;

	*plat_ = bzalloc(sizeof(obs_hotkeys_platform_t));
	obs_hotkeys_platform_t *plat = *plat_;
	if (!plat) {
		*plat_ = NULL;
		return false;
	}

	plat->tis         = TISCopyCurrentKeyboardLayoutInputSource();
	plat->layout_data = (CFDataRef)TISGetInputSourceProperty(plat->tis,
					kTISPropertyUnicodeKeyLayoutData);

	if (!plat->layout_data) {
		blog(LOG_ERROR, "hotkeys-cocoa: Failed getting LayoutData");
		goto fail;
	}

	CFRetain(plat->layout_data);
	plat->layout = (UCKeyboardLayout*)CFDataGetBytePtr(plat->layout_data);

	plat->manager = IOHIDManagerCreate(kCFAllocatorDefault,
						kIOHIDOptionsTypeNone);

	IOReturn openStatus = IOHIDManagerOpen(plat->manager,
						kIOHIDOptionsTypeNone);
	if (openStatus != kIOReturnSuccess) {
		blog(LOG_ERROR, "hotkeys-cocoa: Failed opening HIDManager");
		goto fail;
	}

	init_keyboard(plat);

	return true;

fail:
	hotkeys_release(plat);
	*plat_ = NULL;
	return false;
}