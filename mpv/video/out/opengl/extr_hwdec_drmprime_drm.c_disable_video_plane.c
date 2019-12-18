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
struct ra_hwdec {struct priv* priv; } ;
struct priv {TYPE_1__* ctx; } ;
typedef  scalar_t__ drmModeAtomicReqPtr ;
struct TYPE_2__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  drmprime_video_plane; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ATOMIC_NONBLOCK ; 
 int /*<<< orphan*/  MP_ERR (struct ra_hwdec*,char*,int) ; 
 scalar_t__ drmModeAtomicAlloc () ; 
 int drmModeAtomicCommit (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drmModeAtomicFree (scalar_t__) ; 
 int /*<<< orphan*/  drm_object_set_property (scalar_t__,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_video_plane(struct ra_hwdec *hw)
{
    struct priv *p = hw->priv;
    if (!p->ctx)
        return;

    if (!p->ctx->drmprime_video_plane)
        return;

    // Disabling the drmprime video plane is needed on some devices when using
    // the primary plane for video. Primary buffer can't be active with no
    // framebuffer associated. So we need this function to commit it right away
    // as mpv will free all framebuffers on playback end.
    drmModeAtomicReqPtr request = drmModeAtomicAlloc();
    if (request) {
        drm_object_set_property(request, p->ctx->drmprime_video_plane, "FB_ID", 0);
        drm_object_set_property(request, p->ctx->drmprime_video_plane, "CRTC_ID", 0);

        int ret = drmModeAtomicCommit(p->ctx->fd, request,
                                  DRM_MODE_ATOMIC_NONBLOCK, NULL);

        if (ret)
            MP_ERR(hw, "Failed to commit disable plane request (code %d)", ret);
        drmModeAtomicFree(request);
    }
}