#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int response_type; int mask; } ;
typedef  TYPE_1__ xcb_query_pointer_reply_t ;
typedef  int /*<<< orphan*/  xcb_query_pointer_cookie_t ;
struct TYPE_15__ {int detail; } ;
typedef  TYPE_2__ xcb_input_raw_button_release_event_t ;
struct TYPE_16__ {int detail; } ;
typedef  TYPE_3__ xcb_input_raw_button_press_event_t ;
typedef  TYPE_1__ xcb_generic_event_t ;
typedef  TYPE_1__ xcb_generic_error_t ;
struct TYPE_17__ {int event_type; } ;
typedef  TYPE_6__ xcb_ge_event_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  int uint16_t ;
typedef  int obs_key_t ;
struct TYPE_18__ {int* pressed; int* update; int* button_pressed; } ;
typedef  TYPE_7__ obs_hotkeys_platform_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
#define  OBS_KEY_MOUSE1 158 
#define  OBS_KEY_MOUSE10 157 
#define  OBS_KEY_MOUSE11 156 
#define  OBS_KEY_MOUSE12 155 
#define  OBS_KEY_MOUSE13 154 
#define  OBS_KEY_MOUSE14 153 
#define  OBS_KEY_MOUSE15 152 
#define  OBS_KEY_MOUSE16 151 
#define  OBS_KEY_MOUSE17 150 
#define  OBS_KEY_MOUSE18 149 
#define  OBS_KEY_MOUSE19 148 
#define  OBS_KEY_MOUSE2 147 
#define  OBS_KEY_MOUSE20 146 
#define  OBS_KEY_MOUSE21 145 
#define  OBS_KEY_MOUSE22 144 
#define  OBS_KEY_MOUSE23 143 
#define  OBS_KEY_MOUSE24 142 
#define  OBS_KEY_MOUSE25 141 
#define  OBS_KEY_MOUSE26 140 
#define  OBS_KEY_MOUSE27 139 
#define  OBS_KEY_MOUSE28 138 
#define  OBS_KEY_MOUSE29 137 
#define  OBS_KEY_MOUSE3 136 
#define  OBS_KEY_MOUSE4 135 
#define  OBS_KEY_MOUSE5 134 
#define  OBS_KEY_MOUSE6 133 
#define  OBS_KEY_MOUSE7 132 
#define  OBS_KEY_MOUSE8 131 
#define  OBS_KEY_MOUSE9 130 
 int XCB_BUTTON_MASK_1 ; 
 int XCB_BUTTON_MASK_2 ; 
 int XCB_BUTTON_MASK_3 ; 
 int XCB_GE_GENERIC ; 
#define  XCB_INPUT_RAW_BUTTON_PRESS 129 
#define  XCB_INPUT_RAW_BUTTON_RELEASE 128 
 int XINPUT_MOUSE_LEN ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  root_window (TYPE_7__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* xcb_poll_for_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_query_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* xcb_query_pointer_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 

__attribute__((used)) static bool mouse_button_pressed(xcb_connection_t *connection,
				 obs_hotkeys_platform_t *context, obs_key_t key)
{
	bool ret = false;

#if USE_XINPUT
	memset(context->pressed, 0, XINPUT_MOUSE_LEN);
	memset(context->update, 0, XINPUT_MOUSE_LEN);

	xcb_generic_event_t *ev;
	while ((ev = xcb_poll_for_event(connection))) {
		if ((ev->response_type & ~80) == XCB_GE_GENERIC) {
			switch (((xcb_ge_event_t *)ev)->event_type) {
			case XCB_INPUT_RAW_BUTTON_PRESS: {
				xcb_input_raw_button_press_event_t *mot;
				mot = (xcb_input_raw_button_press_event_t *)ev;
				if (mot->detail < XINPUT_MOUSE_LEN) {
					context->pressed[mot->detail - 1] =
						true;
					context->update[mot->detail - 1] = true;
				} else {
					blog(LOG_WARNING, "Unsupported button");
				}
				break;
			}
			case XCB_INPUT_RAW_BUTTON_RELEASE: {
				xcb_input_raw_button_release_event_t *mot;
				mot = (xcb_input_raw_button_release_event_t *)ev;
				if (mot->detail < XINPUT_MOUSE_LEN)
					context->update[mot->detail - 1] = true;
				else
					blog(LOG_WARNING, "Unsupported button");
				break;
			}
			default:
				break;
			}
		}
		free(ev);
	}

	// Mouse 2 for OBS is Right Click and Mouse 3 is Wheel Click.
	// Mouse Wheel axis clicks (xinput mot->detail 4 5 6 7) are ignored.
	switch (key) {
	case OBS_KEY_MOUSE1:
		ret = context->pressed[0] || context->button_pressed[0];
		break;
	case OBS_KEY_MOUSE2:
		ret = context->pressed[2] || context->button_pressed[2];
		break;
	case OBS_KEY_MOUSE3:
		ret = context->pressed[1] || context->button_pressed[1];
		break;
	case OBS_KEY_MOUSE4:
		ret = context->pressed[7] || context->button_pressed[7];
		break;
	case OBS_KEY_MOUSE5:
		ret = context->pressed[8] || context->button_pressed[8];
		break;
	case OBS_KEY_MOUSE6:
		ret = context->pressed[9] || context->button_pressed[9];
		break;
	case OBS_KEY_MOUSE7:
		ret = context->pressed[10] || context->button_pressed[10];
		break;
	case OBS_KEY_MOUSE8:
		ret = context->pressed[11] || context->button_pressed[11];
		break;
	case OBS_KEY_MOUSE9:
		ret = context->pressed[12] || context->button_pressed[12];
		break;
	case OBS_KEY_MOUSE10:
		ret = context->pressed[13] || context->button_pressed[13];
		break;
	case OBS_KEY_MOUSE11:
		ret = context->pressed[14] || context->button_pressed[14];
		break;
	case OBS_KEY_MOUSE12:
		ret = context->pressed[15] || context->button_pressed[15];
		break;
	case OBS_KEY_MOUSE13:
		ret = context->pressed[16] || context->button_pressed[16];
		break;
	case OBS_KEY_MOUSE14:
		ret = context->pressed[17] || context->button_pressed[17];
		break;
	case OBS_KEY_MOUSE15:
		ret = context->pressed[18] || context->button_pressed[18];
		break;
	case OBS_KEY_MOUSE16:
		ret = context->pressed[19] || context->button_pressed[19];
		break;
	case OBS_KEY_MOUSE17:
		ret = context->pressed[20] || context->button_pressed[20];
		break;
	case OBS_KEY_MOUSE18:
		ret = context->pressed[21] || context->button_pressed[21];
		break;
	case OBS_KEY_MOUSE19:
		ret = context->pressed[22] || context->button_pressed[22];
		break;
	case OBS_KEY_MOUSE20:
		ret = context->pressed[23] || context->button_pressed[23];
		break;
	case OBS_KEY_MOUSE21:
		ret = context->pressed[24] || context->button_pressed[24];
		break;
	case OBS_KEY_MOUSE22:
		ret = context->pressed[25] || context->button_pressed[25];
		break;
	case OBS_KEY_MOUSE23:
		ret = context->pressed[26] || context->button_pressed[26];
		break;
	case OBS_KEY_MOUSE24:
		ret = context->pressed[27] || context->button_pressed[27];
		break;
	case OBS_KEY_MOUSE25:
		ret = context->pressed[28] || context->button_pressed[28];
		break;
	case OBS_KEY_MOUSE26:
		ret = context->pressed[29] || context->button_pressed[29];
		break;
	case OBS_KEY_MOUSE27:
		ret = context->pressed[30] || context->button_pressed[30];
		break;
	case OBS_KEY_MOUSE28:
		ret = context->pressed[31] || context->button_pressed[31];
		break;
	case OBS_KEY_MOUSE29:
		ret = context->pressed[32] || context->button_pressed[32];
		break;
	default:
		break;
	}

	for (int i = 0; i != XINPUT_MOUSE_LEN; i++)
		if (context->update[i])
			context->button_pressed[i] = context->pressed[i];
#else
	xcb_generic_error_t *error = NULL;
	xcb_query_pointer_cookie_t qpc;
	xcb_query_pointer_reply_t *reply;

	qpc = xcb_query_pointer(connection, root_window(context, connection));
	reply = xcb_query_pointer_reply(connection, qpc, &error);

	if (error) {
		blog(LOG_WARNING, "xcb_query_pointer_reply failed");
	} else {
		uint16_t buttons = reply->mask;

		switch (key) {
		case OBS_KEY_MOUSE1:
			ret = buttons & XCB_BUTTON_MASK_1;
			break;
		case OBS_KEY_MOUSE2:
			ret = buttons & XCB_BUTTON_MASK_3;
			break;
		case OBS_KEY_MOUSE3:
			ret = buttons & XCB_BUTTON_MASK_2;
			break;
		default:;
		}
	}

	free(reply);
	free(error);
#endif
	return ret;
}