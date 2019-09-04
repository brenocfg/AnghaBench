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
struct vdp_functions {int /*<<< orphan*/  (* presentation_queue_block_until_surface_idle ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ;} ;
struct surface {scalar_t__ surface; } ;
struct ra_ctx {struct priv* priv; } ;
struct priv {size_t idx_surfaces; int /*<<< orphan*/  vdp_queue; struct surface* surfaces; TYPE_1__* vdp; } ;
typedef  int /*<<< orphan*/  VdpTime ;
typedef  int /*<<< orphan*/  VdpStatus ;
struct TYPE_2__ {struct vdp_functions vdp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_VDP_WARNING (struct ra_ctx*,char*) ; 
 scalar_t__ VDP_INVALID_HANDLE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vdpau_swap_buffers(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    struct vdp_functions *vdp = &p->vdp->vdp;
    VdpStatus vdp_st;

    // This is the *next* surface we will be rendering to. By delaying the
    // block_until_idle, we're essentially allowing p->num_surfaces - 1
    // in-flight surfaces, plus the one currently visible surface.
    struct surface *surf = &p->surfaces[p->idx_surfaces];
    if (surf->surface == VDP_INVALID_HANDLE)
        return;

    VdpTime prev_vsync_time;
    vdp_st = vdp->presentation_queue_block_until_surface_idle(p->vdp_queue,
                                                              surf->surface,
                                                              &prev_vsync_time);
    CHECK_VDP_WARNING(ctx, "waiting for surface failed");
}