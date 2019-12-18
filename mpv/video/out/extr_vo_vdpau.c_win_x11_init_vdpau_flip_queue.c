#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vo_x11_state {int /*<<< orphan*/  window; } ;
struct vo {struct vo_x11_state* x11; struct vdpctx* priv; } ;
struct TYPE_4__ {scalar_t__ a; double r; double g; double b; } ;
struct vdpctx {scalar_t__ flip_target; scalar_t__ flip_queue; int user_fps; scalar_t__ composite_detect; TYPE_1__ colorkey; int /*<<< orphan*/  vdp_device; struct vdp_functions* vdp; } ;
struct vdp_functions {int /*<<< orphan*/  (* presentation_queue_set_background_color ) (scalar_t__,TYPE_2__*) ;int /*<<< orphan*/  (* presentation_queue_create ) (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ;int /*<<< orphan*/  (* presentation_queue_target_create_x11 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ;} ;
typedef  int /*<<< orphan*/  VdpStatus ;
struct TYPE_5__ {double red; double green; double blue; int /*<<< orphan*/  alpha; } ;
typedef  TYPE_2__ VdpColor ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_VDP_ERROR (struct vo*,char*) ; 
 int /*<<< orphan*/  CHECK_VDP_WARNING (struct vo*,char*) ; 
 int /*<<< orphan*/  MP_INFO (struct vo*,char*) ; 
 scalar_t__ VDP_INVALID_HANDLE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,TYPE_2__*) ; 
 scalar_t__ vo_x11_screen_is_composited (struct vo*) ; 

__attribute__((used)) static int win_x11_init_vdpau_flip_queue(struct vo *vo)
{
    struct vdpctx *vc = vo->priv;
    struct vdp_functions *vdp = vc->vdp;
    struct vo_x11_state *x11 = vo->x11;
    VdpStatus vdp_st;

    if (vc->flip_target == VDP_INVALID_HANDLE) {
        vdp_st = vdp->presentation_queue_target_create_x11(vc->vdp_device,
                                                           x11->window,
                                                           &vc->flip_target);
        CHECK_VDP_ERROR(vo, "Error when calling "
                        "vdp_presentation_queue_target_create_x11");
    }

    /* Emperically this seems to be the first call which fails when we
     * try to reinit after preemption while the user is still switched
     * from X to a virtual terminal (creating the vdp_device initially
     * succeeds, as does creating the flip_target above). This is
     * probably not guaranteed behavior.
     */
    if (vc->flip_queue == VDP_INVALID_HANDLE) {
        vdp_st = vdp->presentation_queue_create(vc->vdp_device, vc->flip_target,
                                                &vc->flip_queue);
        CHECK_VDP_ERROR(vo, "Error when calling vdp_presentation_queue_create");
    }

    if (vc->colorkey.a > 0) {
        VdpColor color = {
            .red = vc->colorkey.r / 255.0,
            .green = vc->colorkey.g / 255.0,
            .blue = vc->colorkey.b / 255.0,
            .alpha = 0,
        };
        vdp_st = vdp->presentation_queue_set_background_color(vc->flip_queue,
                                                              &color);
        CHECK_VDP_WARNING(vo, "Error setting colorkey");
    }

    if (vc->composite_detect && vo_x11_screen_is_composited(vo)) {
        MP_INFO(vo, "Compositing window manager detected. Assuming timing info "
                "is inaccurate.\n");
        vc->user_fps = -1;
    }

    return 0;
}