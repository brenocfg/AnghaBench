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
struct vdp_functions {int /*<<< orphan*/  (* presentation_queue_create ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* presentation_queue_target_create_x11 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct ra_ctx {TYPE_3__* vo; struct priv* priv; } ;
struct GL {int /*<<< orphan*/  (* VDPAUInitNV ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct priv {int /*<<< orphan*/  vdp_queue; int /*<<< orphan*/  vdp_target; TYPE_1__* vdp; struct GL gl; } ;
typedef  int /*<<< orphan*/  VdpStatus ;
typedef  int /*<<< orphan*/  VdpDevice ;
struct TYPE_6__ {TYPE_2__* x11; } ;
struct TYPE_5__ {int /*<<< orphan*/  window; } ;
struct TYPE_4__ {int /*<<< orphan*/  get_proc_address; struct vdp_functions vdp; int /*<<< orphan*/  vdp_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRAINDEATH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_VDP_ERROR (struct ra_ctx*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_vdpau_objects(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    struct GL *gl = &p->gl;
    VdpDevice dev = p->vdp->vdp_device;
    struct vdp_functions *vdp = &p->vdp->vdp;
    VdpStatus vdp_st;

    gl->VDPAUInitNV(BRAINDEATH(dev), p->vdp->get_proc_address);

    vdp_st = vdp->presentation_queue_target_create_x11(dev, ctx->vo->x11->window,
                                                       &p->vdp_target);
    CHECK_VDP_ERROR(ctx, "creating vdp target");

    vdp_st = vdp->presentation_queue_create(dev, p->vdp_target, &p->vdp_queue);
    CHECK_VDP_ERROR(ctx, "creating vdp presentation queue");

    return 0;
}