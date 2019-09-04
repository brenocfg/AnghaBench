#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xcb_keycode_t ;
struct TYPE_4__ {size_t num; scalar_t__* array; } ;
struct keycode_list {TYPE_1__ list; } ;
typedef  int /*<<< orphan*/  obs_key_t ;
struct TYPE_5__ {struct keycode_list* keycodes; } ;
typedef  TYPE_2__ obs_hotkeys_platform_t ;

/* Variables and functions */
 size_t OBS_KEY_LAST_VALUE ; 
 int /*<<< orphan*/  OBS_KEY_NONE ; 

__attribute__((used)) static obs_key_t key_from_keycode(obs_hotkeys_platform_t *context,
		xcb_keycode_t code)
{
	for (size_t i = 0; i < OBS_KEY_LAST_VALUE; i++) {
		struct keycode_list *codes = &context->keycodes[i];

		for (size_t j = 0; j < codes->list.num; j++) {
			if (codes->list.array[j] == code) {
				return (obs_key_t)i;
			}
		}
	}

	return OBS_KEY_NONE;
}