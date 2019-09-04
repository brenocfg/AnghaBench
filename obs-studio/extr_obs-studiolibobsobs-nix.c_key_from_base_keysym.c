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
typedef  scalar_t__ xcb_keysym_t ;
typedef  int /*<<< orphan*/  obs_key_t ;
struct TYPE_3__ {scalar_t__* base_keysyms; } ;
typedef  TYPE_1__ obs_hotkeys_platform_t ;

/* Variables and functions */
 size_t OBS_KEY_LAST_VALUE ; 
 int /*<<< orphan*/  OBS_KEY_NONE ; 

__attribute__((used)) static obs_key_t key_from_base_keysym(obs_hotkeys_platform_t *context,
		xcb_keysym_t code)
{
	for (size_t i = 0; i < OBS_KEY_LAST_VALUE; i++) {
		if (context->base_keysyms[i] == (xcb_keysym_t)code) {
			return (obs_key_t)i;
		}
	}

	return OBS_KEY_NONE;
}