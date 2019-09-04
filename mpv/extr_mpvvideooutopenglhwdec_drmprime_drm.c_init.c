#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct ra_hwdec {int /*<<< orphan*/  ra; int /*<<< orphan*/  global; int /*<<< orphan*/  log; struct priv* priv; } ;
struct priv {TYPE_4__* ctx; int /*<<< orphan*/  display_h; int /*<<< orphan*/  display_w; int /*<<< orphan*/  log; } ;
struct mpv_opengl_drm_params {int /*<<< orphan*/  connector_id; int /*<<< orphan*/  crtc_id; int /*<<< orphan*/  fd; } ;
struct drm_opts {int drm_draw_plane; int drm_drmprime_video_plane; } ;
typedef  TYPE_3__* drmModeCrtcPtr ;
struct TYPE_10__ {int /*<<< orphan*/  fd; TYPE_1__* crtc; int /*<<< orphan*/  drmprime_video_plane; } ;
struct TYPE_8__ {int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;
struct TYPE_9__ {TYPE_2__ mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CAP_PRIME ; 
 int /*<<< orphan*/  MP_ERR (struct ra_hwdec*,char*) ; 
 int /*<<< orphan*/  disable_video_plane (struct ra_hwdec*) ; 
 scalar_t__ drmGetCap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drmModeFreeCrtc (TYPE_3__*) ; 
 TYPE_3__* drmModeGetCrtc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* drm_atomic_create_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  drm_conf ; 
 int /*<<< orphan*/  mp_err (int /*<<< orphan*/ ,char*) ; 
 struct drm_opts* mp_get_config_group (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_verbose (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mp_warn (int /*<<< orphan*/ ,char*) ; 
 struct mpv_opengl_drm_params* ra_get_native_resource (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uninit (struct ra_hwdec*) ; 

__attribute__((used)) static int init(struct ra_hwdec *hw)
{
    struct priv *p = hw->priv;
    int draw_plane, drmprime_video_plane;

    p->log = hw->log;

    void *tmp = talloc_new(NULL);
    struct drm_opts *opts = mp_get_config_group(tmp, hw->global, &drm_conf);
    draw_plane = opts->drm_draw_plane;
    drmprime_video_plane = opts->drm_drmprime_video_plane;
    talloc_free(tmp);

    struct mpv_opengl_drm_params *drm_params;

    drm_params = ra_get_native_resource(hw->ra, "drm_params");
    if (drm_params) {
        p->ctx = drm_atomic_create_context(p->log, drm_params->fd, drm_params->crtc_id,
                                           drm_params->connector_id, draw_plane, drmprime_video_plane);
        if (!p->ctx) {
            mp_err(p->log, "Failed to retrieve DRM atomic context.\n");
            goto err;
        }
        if (!p->ctx->drmprime_video_plane) {
            mp_warn(p->log, "No drmprime video plane. You might need to specify it manually using --drm-drmprime-video-plane\n");
            goto err;
        }
    } else {
        mp_verbose(p->log, "Failed to retrieve DRM fd from native display.\n");
        goto err;
    }

    drmModeCrtcPtr crtc;
    crtc = drmModeGetCrtc(p->ctx->fd, p->ctx->crtc->id);
    if (crtc) {
        p->display_w = crtc->mode.hdisplay;
        p->display_h = crtc->mode.vdisplay;
        drmModeFreeCrtc(crtc);
    }

    uint64_t has_prime;
    if (drmGetCap(p->ctx->fd, DRM_CAP_PRIME, &has_prime) < 0) {
        MP_ERR(hw, "Card does not support prime handles.\n");
        goto err;
    }

    disable_video_plane(hw);
    return 0;

err:
    uninit(hw);
    return -1;
}