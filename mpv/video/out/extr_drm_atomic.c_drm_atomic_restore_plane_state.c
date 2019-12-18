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
struct drm_object {int dummy; } ;
struct drm_atomic_plane_state {int /*<<< orphan*/  zpos; int /*<<< orphan*/  crtc_h; int /*<<< orphan*/  crtc_w; int /*<<< orphan*/  crtc_y; int /*<<< orphan*/  crtc_x; int /*<<< orphan*/  src_h; int /*<<< orphan*/  src_w; int /*<<< orphan*/  src_y; int /*<<< orphan*/  src_x; int /*<<< orphan*/  crtc_id; int /*<<< orphan*/  fb_id; } ;
typedef  int /*<<< orphan*/  drmModeAtomicReq ;

/* Variables and functions */
 scalar_t__ drm_object_set_property (int /*<<< orphan*/ *,struct drm_object*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool drm_atomic_restore_plane_state(drmModeAtomicReq *request,
                                           struct drm_object *plane,
                                           const struct drm_atomic_plane_state *plane_state)
{
    if (!plane)
        return true;

    bool ret = true;

    if (0 > drm_object_set_property(request, plane, "FB_ID", plane_state->fb_id))
        ret = false;
    if (0 > drm_object_set_property(request, plane, "CRTC_ID", plane_state->crtc_id))
        ret = false;
    if (0 > drm_object_set_property(request, plane, "SRC_X", plane_state->src_x))
        ret = false;
    if (0 > drm_object_set_property(request, plane, "SRC_Y", plane_state->src_y))
        ret = false;
    if (0 > drm_object_set_property(request, plane, "SRC_W", plane_state->src_w))
        ret = false;
    if (0 > drm_object_set_property(request, plane, "SRC_H", plane_state->src_h))
        ret = false;
    if (0 > drm_object_set_property(request, plane, "CRTC_X", plane_state->crtc_x))
        ret = false;
    if (0 > drm_object_set_property(request, plane, "CRTC_Y", plane_state->crtc_y))
        ret = false;
    if (0 > drm_object_set_property(request, plane, "CRTC_W", plane_state->crtc_w))
        ret = false;
    if (0 > drm_object_set_property(request, plane, "CRTC_H", plane_state->crtc_h))
        ret = false;
    // ZPOS might not exist, so ignore whether or not this succeeds
    drm_object_set_property(request, plane, "ZPOS", plane_state->zpos);

    return ret;
}