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
typedef  size_t obs_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 size_t OBS_KEY_LAST_VALUE ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int) ; 
 char const** obs_key_names ; 

const char *obs_key_to_name(obs_key_t key)
{
	if (key >= OBS_KEY_LAST_VALUE) {
		blog(LOG_ERROR,
		     "obs-hotkey.c: queried unknown key "
		     "with code %d",
		     (int)key);
		return "";
	}

	return obs_key_names[key];
}