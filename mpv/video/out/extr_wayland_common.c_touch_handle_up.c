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
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_touch {int dummy; } ;
struct vo_wayland_state {TYPE_1__* vo; scalar_t__ touch_entries; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  input_ctx; } ;

/* Variables and functions */
 int MP_KEY_STATE_UP ; 
 int MP_MBTN_LEFT ; 
 int /*<<< orphan*/  mp_input_put_key (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void touch_handle_up(void *data, struct wl_touch *wl_touch,
                            uint32_t serial, uint32_t time, int32_t id)
{
    struct vo_wayland_state *wl = data;

    wl->touch_entries = 0;

    mp_input_put_key(wl->vo->input_ctx, MP_MBTN_LEFT | MP_KEY_STATE_UP);
}