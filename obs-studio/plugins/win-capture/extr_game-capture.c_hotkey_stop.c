#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ mode; } ;
struct game_capture {int /*<<< orphan*/  deactivate_hook; TYPE_1__ config; } ;
typedef  int /*<<< orphan*/  obs_hotkey_t ;
typedef  int /*<<< orphan*/  obs_hotkey_pair_id ;

/* Variables and functions */
 scalar_t__ CAPTURE_MODE_HOTKEY ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool hotkey_stop(void *data, obs_hotkey_pair_id id, obs_hotkey_t *hotkey,
			bool pressed)
{
	struct game_capture *gc = data;

	if (pressed && gc->config.mode == CAPTURE_MODE_HOTKEY) {
		info("Deactivate hotkey pressed");
		os_atomic_set_bool(&gc->deactivate_hook, true);
	}

	return true;
}