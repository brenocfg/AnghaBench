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
struct wl_keyboard {int dummy; } ;
struct vo_wayland_state {TYPE_2__* vo; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  input_ctx; TYPE_1__* opts; } ;
struct TYPE_3__ {scalar_t__ native_keyrepeat; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_input_set_repeat_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void keyboard_handle_repeat_info(void *data, struct wl_keyboard *wl_keyboard,
                                        int32_t rate, int32_t delay)
{
    struct vo_wayland_state *wl = data;
    if (wl->vo->opts->native_keyrepeat)
        mp_input_set_repeat_info(wl->vo->input_ctx, rate, delay);
}