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
struct vo_wayland_state {int user_sbc; int frame_wait; scalar_t__ presentation; TYPE_1__* opts; int /*<<< orphan*/  feedback; int /*<<< orphan*/  surface; } ;
struct ra_ctx {TYPE_2__* vo; } ;
struct TYPE_4__ {struct vo_wayland_state* wl; } ;
struct TYPE_3__ {int /*<<< orphan*/  frame_offset; int /*<<< orphan*/  disable_vsync; } ;

/* Variables and functions */
 int /*<<< orphan*/  feedback_listener ; 
 int last_available_sync (struct vo_wayland_state*) ; 
 int /*<<< orphan*/  queue_new_sync (struct vo_wayland_state*) ; 
 int /*<<< orphan*/  vo_wayland_wait_frame (struct vo_wayland_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wayland_sync_swap (struct vo_wayland_state*) ; 
 int /*<<< orphan*/  wp_presentation_feedback (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wp_presentation_feedback_add_listener (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct vo_wayland_state*) ; 

__attribute__((used)) static void wayland_vk_swap_buffers(struct ra_ctx *ctx)
{
    struct vo_wayland_state *wl = ctx->vo->wl;

    if (wl->presentation) {
        wl->feedback = wp_presentation_feedback(wl->presentation, wl->surface);
        wp_presentation_feedback_add_listener(wl->feedback, &feedback_listener, wl);
        wl->user_sbc += 1;
        int index = last_available_sync(wl);
        if (index < 0)
            queue_new_sync(wl);
    }

    if (!wl->opts->disable_vsync)
        vo_wayland_wait_frame(wl, wl->opts->frame_offset);

    if (wl->presentation)
        wayland_sync_swap(wl);

    wl->frame_wait = true;
}