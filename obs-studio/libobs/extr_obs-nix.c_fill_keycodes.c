#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xcb_keysym_t ;
struct TYPE_10__ {scalar_t__ keysyms_per_keycode; } ;
typedef  TYPE_1__ xcb_get_keyboard_mapping_reply_t ;
typedef  int /*<<< orphan*/  xcb_get_keyboard_mapping_cookie_t ;
typedef  TYPE_1__ xcb_generic_error_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct xcb_setup_t {int min_keycode; int max_keycode; } ;
struct obs_core_hotkeys {TYPE_3__* platform_context; } ;
typedef  int /*<<< orphan*/  obs_key_t ;
struct TYPE_11__ {int min_keycode; int num_keysyms; int syms_per_code; int super_l_code; int super_r_code; int /*<<< orphan*/  keysyms; int /*<<< orphan*/  display; } ;
typedef  TYPE_3__ obs_hotkeys_platform_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  OBS_KEY_NONE ; 
 int /*<<< orphan*/ * XGetXCBConnection (int /*<<< orphan*/ ) ; 
 scalar_t__ const XK_Super_L ; 
 scalar_t__ const XK_Super_R ; 
 int /*<<< orphan*/  add_key (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bmemdup (scalar_t__ const*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  key_from_base_keysym (TYPE_3__*,scalar_t__ const) ; 
 int /*<<< orphan*/  xcb_get_keyboard_mapping (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__* xcb_get_keyboard_mapping_keysyms (TYPE_1__*) ; 
 TYPE_1__* xcb_get_keyboard_mapping_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 
 struct xcb_setup_t* xcb_get_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool fill_keycodes(struct obs_core_hotkeys *hotkeys)
{
	obs_hotkeys_platform_t *context = hotkeys->platform_context;
	xcb_connection_t *connection = XGetXCBConnection(context->display);
	const struct xcb_setup_t *setup = xcb_get_setup(connection);
	xcb_get_keyboard_mapping_cookie_t cookie;
	xcb_get_keyboard_mapping_reply_t *reply;
	xcb_generic_error_t *error = NULL;
	int code;

	int mincode = setup->min_keycode;
	int maxcode = setup->max_keycode;

	context->min_keycode = setup->min_keycode;

	cookie = xcb_get_keyboard_mapping(connection, mincode,
					  maxcode - mincode + 1);

	reply = xcb_get_keyboard_mapping_reply(connection, cookie, &error);

	if (error || !reply) {
		blog(LOG_WARNING, "xcb_get_keyboard_mapping_reply failed");
		goto error1;
	}

	const xcb_keysym_t *keysyms = xcb_get_keyboard_mapping_keysyms(reply);
	int syms_per_code = (int)reply->keysyms_per_keycode;

	context->num_keysyms = (maxcode - mincode + 1) * syms_per_code;
	context->syms_per_code = syms_per_code;
	context->keysyms =
		bmemdup(keysyms, sizeof(xcb_keysym_t) * context->num_keysyms);

	for (code = mincode; code <= maxcode; code++) {
		const xcb_keysym_t *sym;
		obs_key_t key;

		sym = &keysyms[(code - mincode) * syms_per_code];

		for (int i = 0; i < syms_per_code; i++) {
			if (!sym[i])
				break;

			if (sym[i] == XK_Super_L) {
				context->super_l_code = code;
				break;
			} else if (sym[i] == XK_Super_R) {
				context->super_r_code = code;
				break;
			} else {
				key = key_from_base_keysym(context, sym[i]);

				if (key != OBS_KEY_NONE) {
					add_key(context, key, code);
					break;
				}
			}
		}
	}

error1:
	free(reply);
	free(error);

	return error != NULL || reply == NULL;
}