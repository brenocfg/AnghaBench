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
typedef  size_t obs_key_t ;
struct TYPE_3__ {int /*<<< orphan*/ * keys; } ;
typedef  TYPE_1__ obs_hotkeys_platform_t ;
typedef  int /*<<< orphan*/  UInt32 ;
typedef  scalar_t__ UInt16 ;
typedef  int /*<<< orphan*/  IOHIDElementRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFRetain (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_KEY ; 
 int /*<<< orphan*/  IOHIDElementGetUsage (int /*<<< orphan*/ ) ; 
 size_t OBS_KEY_NONE ; 
 scalar_t__ da_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t obs_key_from_virtual_key (scalar_t__) ; 
 scalar_t__ usage_to_carbon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void load_key(obs_hotkeys_platform_t *plat, IOHIDElementRef key)
{
	UInt32 usage_code  = IOHIDElementGetUsage(key);
	UInt16 carbon_code = usage_to_carbon(usage_code);

	if (carbon_code == INVALID_KEY) return;

	obs_key_t obs_key = obs_key_from_virtual_key(carbon_code);
	if (obs_key == OBS_KEY_NONE)
		return;

	da_push_back(plat->keys[obs_key], &key);
	CFRetain(*(IOHIDElementRef*)da_end(plat->keys[obs_key]));
}