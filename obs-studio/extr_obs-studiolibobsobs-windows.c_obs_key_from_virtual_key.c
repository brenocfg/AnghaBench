#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  obs_key_t ;
struct TYPE_5__ {int* vk_codes; } ;
typedef  TYPE_2__ obs_hotkeys_platform_t ;
struct TYPE_4__ {TYPE_2__* platform_context; } ;
struct TYPE_6__ {TYPE_1__ hotkeys; } ;

/* Variables and functions */
 size_t OBS_KEY_LAST_VALUE ; 
 int /*<<< orphan*/  OBS_KEY_NONE ; 
 TYPE_3__* obs ; 

obs_key_t obs_key_from_virtual_key(int code)
{
	obs_hotkeys_platform_t *platform = obs->hotkeys.platform_context;

	for (size_t i = 0; i < OBS_KEY_LAST_VALUE; i++) {
		if (platform->vk_codes[i] == code) {
			return (obs_key_t)i;
		}
	}

	return OBS_KEY_NONE;
}