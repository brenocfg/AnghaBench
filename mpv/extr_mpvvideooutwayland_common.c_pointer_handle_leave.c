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
struct wl_surface {int dummy; } ;
struct wl_pointer {int dummy; } ;
struct vo_wayland_state {TYPE_1__* vo; } ;
struct TYPE_2__ {int /*<<< orphan*/  input_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_KEY_MOUSE_LEAVE ; 
 int /*<<< orphan*/  mp_input_put_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pointer_handle_leave(void *data, struct wl_pointer *pointer,
                                 uint32_t serial, struct wl_surface *surface)
{
    struct vo_wayland_state *wl = data;
    mp_input_put_key(wl->vo->input_ctx, MP_KEY_MOUSE_LEAVE);
}