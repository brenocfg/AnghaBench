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
struct vo_frame {int dummy; } ;
struct vdp_functions {scalar_t__ (* presentation_queue_display ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct surface {scalar_t__ surface; int mapped; int /*<<< orphan*/  registered; } ;
struct ra_swapchain {TYPE_3__* ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* VDPAUUnmapSurfacesNV ) (int,int /*<<< orphan*/ *) ;} ;
struct priv {size_t idx_surfaces; int num_surfaces; int /*<<< orphan*/  vdp_queue; struct surface* surfaces; TYPE_1__* vdp; TYPE_2__ gl; } ;
typedef  scalar_t__ VdpStatus ;
struct TYPE_6__ {struct priv* priv; } ;
struct TYPE_4__ {struct vdp_functions vdp; } ;
typedef  TYPE_2__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_VDP_WARNING (TYPE_3__*,char*) ; 
 scalar_t__ VDP_INVALID_HANDLE ; 
 scalar_t__ VDP_STATUS_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ra_gl_ctx_submit_frame (struct ra_swapchain*,struct vo_frame const*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vdpau_submit_frame(struct ra_swapchain *sw,
                               const struct vo_frame *frame)
{
    struct priv *p = sw->ctx->priv;
    GL *gl = &p->gl;
    struct vdp_functions *vdp = &p->vdp->vdp;
    VdpStatus vdp_st;

    struct surface *surf = &p->surfaces[p->idx_surfaces];
    assert(surf->surface != VDP_INVALID_HANDLE);
    assert(surf->mapped);
    gl->VDPAUUnmapSurfacesNV(1, &surf->registered);
    surf->mapped = false;

    vdp_st = vdp->presentation_queue_display(p->vdp_queue, surf->surface, 0, 0, 0);
    CHECK_VDP_WARNING(sw->ctx, "trying to present vdp surface");

    p->idx_surfaces = (p->idx_surfaces + 1) % p->num_surfaces;
    return ra_gl_ctx_submit_frame(sw, frame) && vdp_st == VDP_STATUS_OK;
}