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
struct vdp_functions {int /*<<< orphan*/  (* output_surface_destroy ) (scalar_t__) ;} ;
struct ra_hwdec_mapper {int /*<<< orphan*/  log; struct priv* priv; } ;
struct priv {scalar_t__ vdp_surface; int vdpgl_initialized; int /*<<< orphan*/  mixer; int /*<<< orphan*/  gl_textures; scalar_t__ vdpgl_surface; int /*<<< orphan*/  mapped; TYPE_1__* ctx; TYPE_2__* gl; } ;
typedef  int /*<<< orphan*/  VdpStatus ;
struct TYPE_5__ {int /*<<< orphan*/  (* VDPAUFiniNV ) () ;int /*<<< orphan*/  (* DeleteTextures ) (int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* VDPAUUnregisterSurfaceNV ) (scalar_t__) ;} ;
struct TYPE_4__ {struct vdp_functions vdp; } ;
typedef  TYPE_2__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_VDP_WARNING (struct ra_hwdec_mapper*,char*) ; 
 scalar_t__ VDP_INVALID_HANDLE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gl_check_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mp_vdpau_mixer_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (scalar_t__) ; 
 int /*<<< orphan*/  stub4 () ; 

__attribute__((used)) static void mapper_uninit(struct ra_hwdec_mapper *mapper)
{
    struct priv *p = mapper->priv;
    GL *gl = p->gl;
    struct vdp_functions *vdp = &p->ctx->vdp;
    VdpStatus vdp_st;

    assert(!p->mapped);

    if (p->vdpgl_surface)
        gl->VDPAUUnregisterSurfaceNV(p->vdpgl_surface);
    p->vdpgl_surface = 0;

    gl->DeleteTextures(4, p->gl_textures);

    if (p->vdp_surface != VDP_INVALID_HANDLE) {
        vdp_st = vdp->output_surface_destroy(p->vdp_surface);
        CHECK_VDP_WARNING(mapper, "Error when calling vdp_output_surface_destroy");
    }
    p->vdp_surface = VDP_INVALID_HANDLE;

    gl_check_error(gl, mapper->log, "Before uninitializing OpenGL interop");

    if (p->vdpgl_initialized)
        gl->VDPAUFiniNV();

    p->vdpgl_initialized = false;

    gl_check_error(gl, mapper->log, "After uninitializing OpenGL interop");

    mp_vdpau_mixer_destroy(p->mixer);
}