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
typedef  int /*<<< orphan*/  wl_fixed_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_surface {int dummy; } ;
struct wl_data_offer {int dummy; } ;
struct wl_data_device {int dummy; } ;
struct vo_wayland_state {int /*<<< orphan*/  dnd_mime_type; struct wl_data_offer* dnd_offer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FATAL (struct vo_wayland_state*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct vo_wayland_state*,char*,int /*<<< orphan*/ ) ; 
 int WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY ; 
 int WL_DATA_DEVICE_MANAGER_DND_ACTION_MOVE ; 
 int /*<<< orphan*/  wl_data_offer_accept (struct wl_data_offer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_data_offer_set_actions (struct wl_data_offer*,int,int) ; 

__attribute__((used)) static void data_device_handle_enter(void *data, struct wl_data_device *wl_ddev,
                                     uint32_t serial, struct wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y,
                                     struct wl_data_offer *id)
{
    struct vo_wayland_state *wl = data;
    if (wl->dnd_offer != id) {
        MP_FATAL(wl, "DND offer ID mismatch!\n");
        return;
    }

    wl_data_offer_set_actions(id, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY |
                                  WL_DATA_DEVICE_MANAGER_DND_ACTION_MOVE,
                                  WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY);

    wl_data_offer_accept(id, serial, wl->dnd_mime_type);

    MP_VERBOSE(wl, "Accepting DND offer with mime type %s\n", wl->dnd_mime_type);
}