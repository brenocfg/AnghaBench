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
struct vo_wayland_state {int /*<<< orphan*/  last_queue_display_time; int /*<<< orphan*/  last_skipped_vsyncs; int /*<<< orphan*/  vsync_duration; int /*<<< orphan*/  hidden; scalar_t__ presentation; } ;
struct vo_vsync_info {int /*<<< orphan*/  last_queue_display_time; int /*<<< orphan*/  skipped_vsyncs; int /*<<< orphan*/  vsync_duration; } ;
struct ra_ctx {TYPE_1__* vo; } ;
struct TYPE_2__ {struct vo_wayland_state* wl; } ;

/* Variables and functions */

__attribute__((used)) static void wayland_egl_get_vsync(struct ra_ctx *ctx, struct vo_vsync_info *info)
{
    struct vo_wayland_state *wl = ctx->vo->wl;
    if (wl->presentation && !wl->hidden) {
        info->vsync_duration = wl->vsync_duration;
        info->skipped_vsyncs = wl->last_skipped_vsyncs;
        info->last_queue_display_time = wl->last_queue_display_time;
    }
}