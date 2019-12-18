#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct vdp_functions {int /*<<< orphan*/  (* output_surface_create ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {int hw_subfmt; int imgfmt; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct ra_hwdec_mapper {int vdpau_fields; int /*<<< orphan*/  log; TYPE_2__ dst_params; TYPE_2__ src_params; int /*<<< orphan*/  ra; struct priv* priv; TYPE_1__* owner; } ;
struct priv_owner {TYPE_6__* ctx; } ;
struct TYPE_12__ {int chroma_w; } ;
struct priv {int vdpgl_initialized; int direct_mode; int /*<<< orphan*/  vdpgl_surface; int /*<<< orphan*/ * gl_textures; int /*<<< orphan*/  vdp_surface; TYPE_6__* ctx; TYPE_5__ direct_desc; int /*<<< orphan*/  preemption_counter; int /*<<< orphan*/  mixer; TYPE_3__* gl; } ;
typedef  int /*<<< orphan*/  VdpStatus ;
struct TYPE_13__ {int /*<<< orphan*/  vdp_device; int /*<<< orphan*/  get_proc_address; struct vdp_functions vdp; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* VDPAUSurfaceAccessNV ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* VDPAURegisterOutputSurfaceNV ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* TexParameteri ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GenTextures ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* VDPAUInitNV ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {struct priv_owner* priv; } ;
typedef  TYPE_3__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  BRAINDEATH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_VDP_ERROR (struct ra_hwdec_mapper*,char*) ; 
 int /*<<< orphan*/  GL_CLAMP_TO_EDGE ; 
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_READ_ONLY ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_S ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_T ; 
 int IMGFMT_420P ; 
 int IMGFMT_444P ; 
 int IMGFMT_NV12 ; 
 int IMGFMT_NV24 ; 
 int IMGFMT_RGB0 ; 
 int /*<<< orphan*/  MP_ERR (struct ra_hwdec_mapper*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VDP_INVALID_HANDLE ; 
 int /*<<< orphan*/  VDP_RGBA_FORMAT_B8G8R8A8 ; 
 int /*<<< orphan*/  gl_check_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mp_imgfmt_to_name (int) ; 
 scalar_t__ mp_vdpau_handle_preemption (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_vdpau_mixer_create (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_get_imgfmt_desc (int /*<<< orphan*/ ,int,TYPE_5__*) ; 
 TYPE_3__* ra_gl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub17 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mapper_init(struct ra_hwdec_mapper *mapper)
{
    struct priv_owner *p_owner = mapper->owner->priv;
    struct priv *p = mapper->priv;

    p->gl = ra_gl_get(mapper->ra);
    p->ctx = p_owner->ctx;

    GL *gl = p->gl;
    struct vdp_functions *vdp = &p->ctx->vdp;
    VdpStatus vdp_st;

    p->vdp_surface = VDP_INVALID_HANDLE;
    p->mixer = mp_vdpau_mixer_create(p->ctx, mapper->log);
    if (!p->mixer)
        return -1;

    mapper->dst_params = mapper->src_params;

    if (mp_vdpau_handle_preemption(p->ctx, &p->preemption_counter) < 0)
        return -1;

    gl->VDPAUInitNV(BRAINDEATH(p->ctx->vdp_device), p->ctx->get_proc_address);

    p->vdpgl_initialized = true;

    p->direct_mode = mapper->dst_params.hw_subfmt == IMGFMT_NV12 ||
                     mapper->dst_params.hw_subfmt == IMGFMT_NV24 ||
                     mapper->dst_params.hw_subfmt == IMGFMT_420P ||
                     mapper->dst_params.hw_subfmt == IMGFMT_444P;
    mapper->vdpau_fields = p->direct_mode;

    gl->GenTextures(4, p->gl_textures);

    if (p->direct_mode) {
        int imgfmt = mapper->dst_params.hw_subfmt;
        if (!ra_get_imgfmt_desc(mapper->ra, imgfmt, &p->direct_desc)) {
            MP_ERR(mapper, "Unsupported format: %s\n", mp_imgfmt_to_name(imgfmt));
            return -1;
        }
        mapper->dst_params.imgfmt = p->direct_desc.chroma_w == 1 ?
                                    IMGFMT_NV24 : IMGFMT_NV12;
        mapper->dst_params.hw_subfmt = 0;

        for (int n = 0; n < 4; n++) {
            gl->BindTexture(GL_TEXTURE_2D, p->gl_textures[n]);
            gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            gl->BindTexture(GL_TEXTURE_2D, 0);
        }
    } else {
        gl->BindTexture(GL_TEXTURE_2D, p->gl_textures[0]);
        gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        gl->BindTexture(GL_TEXTURE_2D, 0);

        vdp_st = vdp->output_surface_create(p->ctx->vdp_device,
                                            VDP_RGBA_FORMAT_B8G8R8A8,
                                            mapper->src_params.w,
                                            mapper->src_params.h,
                                            &p->vdp_surface);
        CHECK_VDP_ERROR(mapper, "Error when calling vdp_output_surface_create");

        p->vdpgl_surface = gl->VDPAURegisterOutputSurfaceNV(BRAINDEATH(p->vdp_surface),
                                                            GL_TEXTURE_2D,
                                                            1, p->gl_textures);
        if (!p->vdpgl_surface)
            return -1;

        gl->VDPAUSurfaceAccessNV(p->vdpgl_surface, GL_READ_ONLY);

        mapper->dst_params.imgfmt = IMGFMT_RGB0;
        mapper->dst_params.hw_subfmt = 0;
    }

    gl_check_error(gl, mapper->log, "After initializing vdpau OpenGL interop");

    return 0;
}