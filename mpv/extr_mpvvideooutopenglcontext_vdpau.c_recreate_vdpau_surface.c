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
struct vdp_functions {scalar_t__ (* output_surface_create ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct surface {int mapped; int /*<<< orphan*/  registered; int /*<<< orphan*/  texture; int /*<<< orphan*/  fbo; int /*<<< orphan*/  surface; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct ra_ctx {TYPE_2__* vo; struct priv* priv; } ;
struct TYPE_6__ {scalar_t__ (* CheckFramebufferStatus ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* VDPAUUnmapSurfacesNV ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* BindFramebuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* FramebufferTexture2D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GenFramebuffers ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* VDPAUMapSurfacesNV ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* VDPAUSurfaceAccessNV ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* VDPAURegisterOutputSurfaceNV ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* GenTextures ) (int,int /*<<< orphan*/ *) ;} ;
struct priv {TYPE_3__ gl; TYPE_1__* vdp; } ;
typedef  scalar_t__ VdpStatus ;
typedef  int /*<<< orphan*/  VdpDevice ;
struct TYPE_5__ {int /*<<< orphan*/  dheight; int /*<<< orphan*/  dwidth; } ;
struct TYPE_4__ {struct vdp_functions vdp; int /*<<< orphan*/  vdp_device; } ;
typedef  scalar_t__ GLenum ;
typedef  TYPE_3__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  BRAINDEATH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_VDP_ERROR_NORETURN (struct ra_ctx*,char*) ; 
 int /*<<< orphan*/  GL_COLOR_ATTACHMENT0 ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER ; 
 scalar_t__ GL_FRAMEBUFFER_COMPLETE ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_WRITE_DISCARD_NV ; 
 int /*<<< orphan*/  MP_ERR (struct ra_ctx*,char*,...) ; 
 int /*<<< orphan*/  VDP_RGBA_FORMAT_B8G8R8A8 ; 
 scalar_t__ VDP_STATUS_OK ; 
 int /*<<< orphan*/  destroy_vdpau_surface (struct ra_ctx*,struct surface*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub9 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool recreate_vdpau_surface(struct ra_ctx *ctx,
                                   struct surface *surface)
{
    struct priv *p = ctx->priv;
    VdpDevice dev = p->vdp->vdp_device;
    struct vdp_functions *vdp = &p->vdp->vdp;
    VdpStatus vdp_st;
    GL *gl = &p->gl;

    destroy_vdpau_surface(ctx, surface);

    surface->w = ctx->vo->dwidth;
    surface->h = ctx->vo->dheight;

    vdp_st = vdp->output_surface_create(dev, VDP_RGBA_FORMAT_B8G8R8A8,
                                        surface->w, surface->h,
                                        &surface->surface);
    CHECK_VDP_ERROR_NORETURN(ctx, "creating vdp output surface");
    if (vdp_st != VDP_STATUS_OK)
        goto error;

    gl->GenTextures(1, &surface->texture);

    surface->registered =
        gl->VDPAURegisterOutputSurfaceNV(BRAINDEATH(surface->surface),
                                         GL_TEXTURE_2D,
                                         1, &surface->texture);
    if (!surface->registered) {
        MP_ERR(ctx, "could not register vdpau surface with GL\n");
        goto error;
    }

    gl->VDPAUSurfaceAccessNV(surface->registered, GL_WRITE_DISCARD_NV);
    gl->VDPAUMapSurfacesNV(1, &surface->registered);
    surface->mapped = true;

    gl->GenFramebuffers(1, &surface->fbo);
    gl->BindFramebuffer(GL_FRAMEBUFFER, surface->fbo);
    gl->FramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                             GL_TEXTURE_2D, surface->texture, 0);
    GLenum err = gl->CheckFramebufferStatus(GL_FRAMEBUFFER);
    if (err != GL_FRAMEBUFFER_COMPLETE) {
        MP_ERR(ctx, "Framebuffer completeness check failed (error=%d).\n",
               (int)err);
        goto error;
    }
    gl->BindFramebuffer(GL_FRAMEBUFFER, 0);

    gl->VDPAUUnmapSurfacesNV(1, &surface->registered);
    surface->mapped = false;

    return true;

error:
    destroy_vdpau_surface(ctx, surface);
    return false;
}