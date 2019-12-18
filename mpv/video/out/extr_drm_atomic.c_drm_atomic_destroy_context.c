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
struct TYPE_3__ {int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {TYPE_1__ crtc; } ;
struct drm_atomic_context {int /*<<< orphan*/  drmprime_video_plane; int /*<<< orphan*/  draw_plane; int /*<<< orphan*/  connector; int /*<<< orphan*/  crtc; TYPE_2__ old_state; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_destroy_blob (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_object_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct drm_atomic_context*) ; 

void drm_atomic_destroy_context(struct drm_atomic_context *ctx)
{
    drm_mode_destroy_blob(ctx->fd, &ctx->old_state.crtc.mode);
    drm_object_free(ctx->crtc);
    drm_object_free(ctx->connector);
    drm_object_free(ctx->draw_plane);
    drm_object_free(ctx->drmprime_video_plane);
    talloc_free(ctx);
}