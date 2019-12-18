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
typedef  int /*<<< orphan*/  wl_fixed_t ;
typedef  int uint32_t ;
struct wl_pointer {int dummy; } ;
struct vo_wayland_state {TYPE_1__* vo; } ;
struct TYPE_2__ {int /*<<< orphan*/  input_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_WHEEL_DOWN ; 
 int /*<<< orphan*/  MP_WHEEL_LEFT ; 
 int /*<<< orphan*/  MP_WHEEL_RIGHT ; 
 int /*<<< orphan*/  MP_WHEEL_UP ; 
#define  WL_POINTER_AXIS_HORIZONTAL_SCROLL 129 
#define  WL_POINTER_AXIS_VERTICAL_SCROLL 128 
 double abs (double) ; 
 int /*<<< orphan*/  mp_input_put_wheel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 double wl_fixed_to_double (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pointer_handle_axis(void *data, struct wl_pointer *wl_pointer,
                                uint32_t time, uint32_t axis, wl_fixed_t value)
{
    struct vo_wayland_state *wl = data;
    if (wl_fixed_to_double(value) == 0)
        return;
    double val = wl_fixed_to_double(value)/abs(wl_fixed_to_double(value));
    switch (axis) {
    case WL_POINTER_AXIS_VERTICAL_SCROLL:
        if (value > 0)
            mp_input_put_wheel(wl->vo->input_ctx, MP_WHEEL_DOWN,  +val);
        if (value < 0)
            mp_input_put_wheel(wl->vo->input_ctx, MP_WHEEL_UP,    -val);
        break;
    case WL_POINTER_AXIS_HORIZONTAL_SCROLL:
        if (value > 0)
            mp_input_put_wheel(wl->vo->input_ctx, MP_WHEEL_RIGHT, +val);
        if (value < 0)
            mp_input_put_wheel(wl->vo->input_ctx, MP_WHEEL_LEFT,  -val);
        break;
    }
}