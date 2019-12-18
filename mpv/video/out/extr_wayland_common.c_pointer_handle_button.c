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
typedef  int uint32_t ;
struct wl_pointer {int dummy; } ;
struct vo_wayland_state {int /*<<< orphan*/  mouse_y; int /*<<< orphan*/  mouse_x; TYPE_1__* vo; } ;
struct TYPE_2__ {int /*<<< orphan*/  input_ctx; } ;

/* Variables and functions */
#define  BTN_EXTRA 132 
#define  BTN_LEFT 131 
#define  BTN_MIDDLE 130 
#define  BTN_RIGHT 129 
#define  BTN_SIDE 128 
 int MP_KEY_STATE_DOWN ; 
 int MP_KEY_STATE_UP ; 
 int MP_MBTN_BACK ; 
 int MP_MBTN_FORWARD ; 
 int MP_MBTN_LEFT ; 
 int MP_MBTN_MID ; 
 int MP_MBTN_RIGHT ; 
 int WL_POINTER_BUTTON_STATE_PRESSED ; 
 int /*<<< orphan*/  mp_input_put_key (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_input_test_dragging (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_move (struct vo_wayland_state*,int) ; 

__attribute__((used)) static void pointer_handle_button(void *data, struct wl_pointer *wl_pointer,
                                  uint32_t serial, uint32_t time, uint32_t button,
                                  uint32_t state)
{
    struct vo_wayland_state *wl = data;

    state = state == WL_POINTER_BUTTON_STATE_PRESSED ? MP_KEY_STATE_DOWN
                                                     : MP_KEY_STATE_UP;

    switch (button) {
    case BTN_LEFT:
        button = MP_MBTN_LEFT;
        break;
    case BTN_MIDDLE:
        button = MP_MBTN_MID;
        break;
    case BTN_RIGHT:
        button = MP_MBTN_RIGHT;
        break;
    case BTN_SIDE:
        button = MP_MBTN_BACK;
        break;
    case BTN_EXTRA:
        button = MP_MBTN_FORWARD;
        break;
    default:
        button = 0;
        break;
    }

    if (button) {
        mp_input_put_key(wl->vo->input_ctx, button | state);
    }

    if (!mp_input_test_dragging(wl->vo->input_ctx, wl->mouse_x, wl->mouse_y) &&
        (button == MP_MBTN_LEFT) && (state == MP_KEY_STATE_DOWN))
        window_move(wl, serial);
}