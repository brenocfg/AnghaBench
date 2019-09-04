#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct vo {double monitor_par; int /*<<< orphan*/  log; TYPE_4__* opts; struct priv* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  page_flip_handler; int /*<<< orphan*/  version; } ;
struct priv {double screen_w; scalar_t__ screen_h; TYPE_3__* bufs; TYPE_5__* kms; int /*<<< orphan*/  vt_switcher; scalar_t__ vt_switcher_active; TYPE_1__ ev; int /*<<< orphan*/  sws; } ;
struct TYPE_10__ {int /*<<< orphan*/  card_no; int /*<<< orphan*/  fd; } ;
struct TYPE_9__ {double force_monitor_aspect; int monitor_pixel_aspect; TYPE_2__* drm_opts; } ;
struct TYPE_8__ {double width; scalar_t__ height; } ;
struct TYPE_7__ {int /*<<< orphan*/  drm_mode_spec; int /*<<< orphan*/  drm_connector_spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CAP_DUMB_BUFFER ; 
 int /*<<< orphan*/  DRM_EVENT_CONTEXT_VERSION ; 
 int /*<<< orphan*/  MP_ERR (struct vo*,char*,...) ; 
 int /*<<< orphan*/  MP_WARN (struct vo*,char*) ; 
 int /*<<< orphan*/  acquire_vt ; 
 int /*<<< orphan*/  crtc_setup (struct vo*) ; 
 scalar_t__ drmGetCap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fb_setup_double_buffering (struct vo*) ; 
 TYPE_5__* kms_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_sws_alloc (struct vo*) ; 
 int /*<<< orphan*/  mp_verbose (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  page_flipped ; 
 int /*<<< orphan*/  release_vt ; 
 int /*<<< orphan*/  uninit (struct vo*) ; 
 int /*<<< orphan*/  vt_switcher_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vo*) ; 
 scalar_t__ vt_switcher_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt_switcher_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vo*) ; 

__attribute__((used)) static int preinit(struct vo *vo)
{
    struct priv *p = vo->priv;
    p->sws = mp_sws_alloc(vo);
    p->ev.version = DRM_EVENT_CONTEXT_VERSION;
    p->ev.page_flip_handler = page_flipped;

    p->vt_switcher_active = vt_switcher_init(&p->vt_switcher, vo->log);
    if (p->vt_switcher_active) {
        vt_switcher_acquire(&p->vt_switcher, acquire_vt, vo);
        vt_switcher_release(&p->vt_switcher, release_vt, vo);
    } else {
        MP_WARN(vo, "Failed to set up VT switcher. Terminal switching will be unavailable.\n");
    }

    p->kms = kms_create(vo->log,
                        vo->opts->drm_opts->drm_connector_spec,
                        vo->opts->drm_opts->drm_mode_spec,
                        0, 0, false);
    if (!p->kms) {
        MP_ERR(vo, "Failed to create KMS.\n");
        goto err;
    }

    if (!fb_setup_double_buffering(vo)) {
        MP_ERR(vo, "Failed to set up double buffering.\n");
        goto err;
    }

    uint64_t has_dumb;
    if (drmGetCap(p->kms->fd, DRM_CAP_DUMB_BUFFER, &has_dumb) < 0) {
        MP_ERR(vo, "Card \"%d\" does not support dumb buffers.\n",
               p->kms->card_no);
        goto err;
    }

    p->screen_w = p->bufs[0].width;
    p->screen_h = p->bufs[0].height;

    if (!crtc_setup(vo)) {
        MP_ERR(vo, "Cannot set CRTC: %s\n", mp_strerror(errno));
        goto err;
    }

    if (vo->opts->force_monitor_aspect != 0.0) {
        vo->monitor_par = p->screen_w / (double) p->screen_h /
                          vo->opts->force_monitor_aspect;
    } else {
        vo->monitor_par = 1 / vo->opts->monitor_pixel_aspect;
    }
    mp_verbose(vo->log, "Monitor pixel aspect: %g\n", vo->monitor_par);

    return 0;

err:
    uninit(vo);
    return -1;
}