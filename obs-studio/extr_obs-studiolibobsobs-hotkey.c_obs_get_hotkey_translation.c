#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t obs_key_t ;
struct TYPE_3__ {char const** translations; } ;
struct TYPE_4__ {TYPE_1__ hotkeys; } ;

/* Variables and functions */
 size_t OBS_KEY_NONE ; 
 TYPE_2__* obs ; 

const char *obs_get_hotkey_translation(obs_key_t key, const char *def)
{
	if (key == OBS_KEY_NONE) {
		return NULL;
	}

	return obs->hotkeys.translations[key] ?
		obs->hotkeys.translations[key] : def;
}