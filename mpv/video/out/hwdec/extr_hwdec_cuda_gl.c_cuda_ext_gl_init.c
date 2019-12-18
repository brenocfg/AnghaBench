#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ra_tex_params {int dimensions; int d; int render_src; int /*<<< orphan*/  src_linear; struct ra_format const* format; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct ra_hwdec_mapper {int /*<<< orphan*/ * tex; int /*<<< orphan*/  ra; struct cuda_mapper_priv* priv; TYPE_1__* owner; } ;
struct ra_format {int /*<<< orphan*/  linear_filter; } ;
struct ext_gl {int /*<<< orphan*/  cu_res; } ;
struct cuda_mapper_priv {int /*<<< orphan*/ * cu_array; int /*<<< orphan*/  layout; struct ext_gl** ext; } ;
struct cuda_hw_priv {TYPE_2__* cu; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cuCtxPopCurrent ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* cuGraphicsUnmapResources ) (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cuGraphicsSubResourceGetMappedArray ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cuGraphicsMapResources ) (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cuGraphicsGLRegisterImage ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct cuda_hw_priv* priv; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  TYPE_2__ CudaFunctions ;
typedef  int /*<<< orphan*/  CUcontext ;

/* Variables and functions */
 int CHECK_CU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CU_GRAPHICS_REGISTER_FLAGS_WRITE_DISCARD ; 
 struct ext_gl* egl ; 
 int /*<<< orphan*/  mp_image_plane_h (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_image_plane_w (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ra_gl_get_raw_tex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ra_tex_create (int /*<<< orphan*/ ,struct ra_tex_params*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *) ; 
 struct ext_gl* talloc_ptrtype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cuda_ext_gl_init(struct ra_hwdec_mapper *mapper,
                             const struct ra_format *format, int n)
{
    struct cuda_hw_priv *p_owner = mapper->owner->priv;
    struct cuda_mapper_priv *p = mapper->priv;
    CudaFunctions *cu = p_owner->cu;
    int ret = 0;
    CUcontext dummy;

    struct ext_gl *egl = talloc_ptrtype(NULL, egl);
    p->ext[n] = egl;

    struct ra_tex_params params = {
        .dimensions = 2,
        .w = mp_image_plane_w(&p->layout, n),
        .h = mp_image_plane_h(&p->layout, n),
        .d = 1,
        .format = format,
        .render_src = true,
        .src_linear = format->linear_filter,
    };

    mapper->tex[n] = ra_tex_create(mapper->ra, &params);
    if (!mapper->tex[n]) {
        goto error;
    }

    GLuint texture;
    GLenum target;
    ra_gl_get_raw_tex(mapper->ra, mapper->tex[n], &texture, &target);

    ret = CHECK_CU(cu->cuGraphicsGLRegisterImage(&egl->cu_res, texture, target,
                                                 CU_GRAPHICS_REGISTER_FLAGS_WRITE_DISCARD));
    if (ret < 0)
        goto error;

    ret = CHECK_CU(cu->cuGraphicsMapResources(1, &egl->cu_res, 0));
    if (ret < 0)
        goto error;

    ret = CHECK_CU(cu->cuGraphicsSubResourceGetMappedArray(&p->cu_array[n], egl->cu_res,
                                                           0, 0));
    if (ret < 0)
        goto error;

    ret = CHECK_CU(cu->cuGraphicsUnmapResources(1, &egl->cu_res, 0));
    if (ret < 0)
        goto error;

    return true;

error:
    CHECK_CU(cu->cuCtxPopCurrent(&dummy));
    return false;
}