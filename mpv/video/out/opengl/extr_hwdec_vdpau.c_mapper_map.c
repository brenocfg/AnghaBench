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
typedef  int uint32_t ;
struct vdp_functions {int /*<<< orphan*/  (* video_surface_get_parameters ) (intptr_t,int /*<<< orphan*/ *,int*,int*) ;} ;
struct ra_tex_params {int dimensions; int w; int h; int d; int render_src; int src_linear; int /*<<< orphan*/  format; } ;
struct TYPE_7__ {int w; int h; } ;
struct ra_hwdec_mapper {void** tex; int /*<<< orphan*/  ra; TYPE_2__ src_params; TYPE_4__* src; struct priv* priv; } ;
struct TYPE_6__ {int chroma_w; int chroma_h; } ;
struct priv {int mapped; int /*<<< orphan*/ * gl_textures; int /*<<< orphan*/  vdpgl_surface; int /*<<< orphan*/  vdp_surface; int /*<<< orphan*/  mixer; TYPE_1__ direct_desc; scalar_t__ direct_mode; int /*<<< orphan*/  preemption_counter; TYPE_5__* ctx; TYPE_3__* gl; } ;
typedef  intptr_t VdpVideoSurface ;
typedef  int /*<<< orphan*/  VdpStatus ;
typedef  int /*<<< orphan*/  VdpChromaType ;
struct TYPE_10__ {struct vdp_functions vdp; } ;
struct TYPE_9__ {int /*<<< orphan*/ * planes; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* VDPAUMapSurfacesNV ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* VDPAUSurfaceAccessNV ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* VDPAURegisterVideoSurfaceNV ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  BRAINDEATH (intptr_t) ; 
 int /*<<< orphan*/  CHECK_VDP_ERROR (struct ra_hwdec_mapper*,char*) ; 
 int /*<<< orphan*/  GL_READ_ONLY ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 scalar_t__ mapper_init (struct ra_hwdec_mapper*) ; 
 int /*<<< orphan*/  mapper_uninit (struct ra_hwdec_mapper*) ; 
 int /*<<< orphan*/  mark_vdpau_objects_uninitialized (struct ra_hwdec_mapper*) ; 
 int mp_vdpau_handle_preemption (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_vdpau_mixer_render (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 void* ra_create_wrapped_tex (int /*<<< orphan*/ ,struct ra_tex_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_find_unorm_format (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (intptr_t,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mapper_map(struct ra_hwdec_mapper *mapper)
{
    struct priv *p = mapper->priv;
    GL *gl = p->gl;
    struct vdp_functions *vdp = &p->ctx->vdp;
    VdpStatus vdp_st;

    int pe = mp_vdpau_handle_preemption(p->ctx, &p->preemption_counter);
    if (pe < 1) {
        mark_vdpau_objects_uninitialized(mapper);
        if (pe < 0)
            return -1;
        mapper_uninit(mapper);
        if (mapper_init(mapper) < 0)
            return -1;
    }

    if (p->direct_mode) {
        VdpVideoSurface surface = (intptr_t)mapper->src->planes[3];

        // We need the uncropped size.
        VdpChromaType s_chroma_type;
        uint32_t s_w, s_h;
        vdp_st = vdp->video_surface_get_parameters(surface, &s_chroma_type, &s_w, &s_h);
        CHECK_VDP_ERROR(mapper, "Error when calling vdp_video_surface_get_parameters");

        p->vdpgl_surface = gl->VDPAURegisterVideoSurfaceNV(BRAINDEATH(surface),
                                                           GL_TEXTURE_2D,
                                                           4, p->gl_textures);
        if (!p->vdpgl_surface)
            return -1;

        gl->VDPAUSurfaceAccessNV(p->vdpgl_surface, GL_READ_ONLY);
        gl->VDPAUMapSurfacesNV(1, &p->vdpgl_surface);

        p->mapped = true;

        for (int n = 0; n < 4; n++) {
            bool chroma = n >= 2;
            int w_scale = chroma ? p->direct_desc.chroma_w : 1;
            int h_scale = chroma ? p->direct_desc.chroma_h * 2 : 2;

            struct ra_tex_params params = {
                .dimensions = 2,
                .w = s_w / w_scale,
                .h = s_h / h_scale,
                .d = 1,
                .format = ra_find_unorm_format(mapper->ra, 1, chroma ? 2 : 1),
                .render_src = true,
            };

            if (!params.format)
                return -1;

            mapper->tex[n] =
                ra_create_wrapped_tex(mapper->ra, &params, p->gl_textures[n]);
            if (!mapper->tex[n])
                return -1;
        }
    } else {
        if (!p->vdpgl_surface)
            return -1;

        mp_vdpau_mixer_render(p->mixer, NULL, p->vdp_surface, NULL, mapper->src,
                              NULL);

        gl->VDPAUMapSurfacesNV(1, &p->vdpgl_surface);

        p->mapped = true;

        struct ra_tex_params params = {
            .dimensions = 2,
            .w = mapper->src_params.w,
            .h = mapper->src_params.h,
            .d = 1,
            .format = ra_find_unorm_format(mapper->ra, 1, 4),
            .render_src = true,
            .src_linear = true,
        };

        if (!params.format)
            return -1;

        mapper->tex[0] =
            ra_create_wrapped_tex(mapper->ra, &params, p->gl_textures[0]);
        if (!mapper->tex[0])
            return -1;
    }

    return 0;
}