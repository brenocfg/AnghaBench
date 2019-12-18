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
typedef  int /*<<< orphan*/  xcb_query_keymap_reply_t ;
typedef  int /*<<< orphan*/  xcb_generic_error_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_4__ {size_t num; int /*<<< orphan*/ * array; } ;
struct keycode_list {TYPE_1__ list; } ;
typedef  size_t obs_key_t ;
struct TYPE_5__ {int /*<<< orphan*/  super_r_code; int /*<<< orphan*/  super_l_code; struct keycode_list* keycodes; } ;
typedef  TYPE_2__ obs_hotkeys_platform_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 size_t OBS_KEY_META ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ keycode_pressed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_query_keymap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xcb_query_keymap_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static bool key_pressed(xcb_connection_t *connection,
			obs_hotkeys_platform_t *context, obs_key_t key)
{
	struct keycode_list *codes = &context->keycodes[key];
	xcb_generic_error_t *error = NULL;
	xcb_query_keymap_reply_t *reply;
	bool pressed = false;

	reply = xcb_query_keymap_reply(connection, xcb_query_keymap(connection),
				       &error);
	if (error) {
		blog(LOG_WARNING, "xcb_query_keymap failed");

	} else if (key == OBS_KEY_META) {
		pressed = keycode_pressed(reply, context->super_l_code) ||
			  keycode_pressed(reply, context->super_r_code);

	} else {
		for (size_t i = 0; i < codes->list.num; i++) {
			if (keycode_pressed(reply, codes->list.array[i])) {
				pressed = true;
				break;
			}
		}
	}

	free(reply);
	free(error);
	return pressed;
}