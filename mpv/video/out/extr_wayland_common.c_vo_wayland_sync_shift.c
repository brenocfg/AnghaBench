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
struct vo_wayland_sync {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct vo_wayland_state {int sync_size; struct vo_wayland_sync* sync; } ;

/* Variables and functions */

void vo_wayland_sync_shift(struct vo_wayland_state *wl)
{
    for (int i = wl->sync_size - 1; i > 0; --i) {
        wl->sync[i] = wl->sync[i-1];
    }
    struct vo_wayland_sync sync = {0, 0, 0, 0};
    wl->sync[0] = sync;
}