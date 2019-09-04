#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vdp_functions {int /*<<< orphan*/  (* presentation_queue_target_destroy ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* presentation_queue_destroy ) (int /*<<< orphan*/ ) ;} ;
struct ra_ctx {TYPE_2__* vo; struct priv* priv; } ;
struct priv {int num_surfaces; scalar_t__ context; TYPE_3__* vdp; int /*<<< orphan*/  vdp_target; int /*<<< orphan*/  vdp_queue; int /*<<< orphan*/ * surfaces; } ;
typedef  int /*<<< orphan*/  VdpStatus ;
struct TYPE_6__ {struct vdp_functions vdp; } ;
struct TYPE_5__ {TYPE_1__* x11; } ;
struct TYPE_4__ {int /*<<< orphan*/ * display; } ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_VDP_WARNING (struct ra_ctx*,char*) ; 
 int /*<<< orphan*/  None ; 
 int /*<<< orphan*/  VDP_INVALID_HANDLE ; 
 int /*<<< orphan*/  destroy_vdpau_surface (struct ra_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glXDestroyContext (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  glXMakeCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_vdpau_destroy (TYPE_3__*) ; 
 int /*<<< orphan*/  ra_gl_ctx_uninit (struct ra_ctx*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vo_x11_uninit (TYPE_2__*) ; 

__attribute__((used)) static void vdpau_uninit(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    ra_gl_ctx_uninit(ctx);

    if (p->vdp) {
        struct vdp_functions *vdp = &p->vdp->vdp;
        VdpStatus vdp_st;

        for (int n = 0; n < p->num_surfaces; n++)
            destroy_vdpau_surface(ctx, &p->surfaces[n]);

        if (p->vdp_queue != VDP_INVALID_HANDLE) {
            vdp_st = vdp->presentation_queue_destroy(p->vdp_queue);
            CHECK_VDP_WARNING(ctx, "destroying presentation queue");
        }

        if (p->vdp_target != VDP_INVALID_HANDLE) {
            vdp_st = vdp->presentation_queue_target_destroy(p->vdp_target);
            CHECK_VDP_WARNING(ctx, "destroying presentation target");
        }

        mp_vdpau_destroy(p->vdp);
    }

    if (p->context) {
        Display *display = ctx->vo->x11->display;
        glXMakeCurrent(display, None, NULL);
        glXDestroyContext(display, p->context);
    }

    vo_x11_uninit(ctx->vo);
}