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
struct vaapi_gl_mapper_priv {int /*<<< orphan*/ * gl_textures; void* EGLImageTargetTexture2DOES; void* DestroyImageKHR; void* CreateImageKHR; } ;
struct ra_tex_params {int dimensions; int d; int render_src; int src_linear; TYPE_1__* format; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct ra_imgfmt_desc {int num_planes; TYPE_1__** planes; } ;
struct ra_hwdec_mapper {int /*<<< orphan*/  ra; struct priv* priv; } ;
struct priv {int /*<<< orphan*/ * tex; int /*<<< orphan*/  layout; struct vaapi_gl_mapper_priv* interop_mapper_priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* TexParameteri ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GenTextures ) (int,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {scalar_t__ ctype; } ;
typedef  TYPE_2__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  GL_CLAMP_TO_EDGE ; 
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_S ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_T ; 
 scalar_t__ RA_CTYPE_UNORM ; 
 scalar_t__ eglGetProcAddress (char*) ; 
 int /*<<< orphan*/  mp_image_plane_h (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_image_plane_w (int /*<<< orphan*/ *,int) ; 
 struct vaapi_gl_mapper_priv* p ; 
 int /*<<< orphan*/  ra_create_wrapped_tex (int /*<<< orphan*/ ,struct ra_tex_params*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ra_gl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vaapi_gl_mapper_priv* talloc_ptrtype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vaapi_gl_mapper_init(struct ra_hwdec_mapper *mapper,
                                 const struct ra_imgfmt_desc *desc)
{
    struct priv *p_mapper = mapper->priv;
    struct vaapi_gl_mapper_priv *p = talloc_ptrtype(NULL, p);
    p_mapper->interop_mapper_priv = p;

    // EGL_KHR_image_base
    p->CreateImageKHR = (void *)eglGetProcAddress("eglCreateImageKHR");
    p->DestroyImageKHR = (void *)eglGetProcAddress("eglDestroyImageKHR");
    // GL_OES_EGL_image
    p->EGLImageTargetTexture2DOES =
        (void *)eglGetProcAddress("glEGLImageTargetTexture2DOES");

    if (!p->CreateImageKHR || !p->DestroyImageKHR ||
        !p->EGLImageTargetTexture2DOES)
        return false;

    GL *gl = ra_gl_get(mapper->ra);
    gl->GenTextures(4, p->gl_textures);
    for (int n = 0; n < desc->num_planes; n++) {
        gl->BindTexture(GL_TEXTURE_2D, p->gl_textures[n]);
        gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        gl->BindTexture(GL_TEXTURE_2D, 0);

        struct ra_tex_params params = {
            .dimensions = 2,
            .w = mp_image_plane_w(&p_mapper->layout, n),
            .h = mp_image_plane_h(&p_mapper->layout, n),
            .d = 1,
            .format = desc->planes[n],
            .render_src = true,
            .src_linear = true,
        };

        if (params.format->ctype != RA_CTYPE_UNORM)
            return false;

        p_mapper->tex[n] = ra_create_wrapped_tex(mapper->ra, &params,
                                                 p->gl_textures[n]);
        if (!p_mapper->tex[n])
            return false;
    }

    return true;
}