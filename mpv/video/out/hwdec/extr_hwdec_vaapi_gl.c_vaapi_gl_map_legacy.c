#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct vaapi_gl_mapper_priv {int /*<<< orphan*/ * images; int /*<<< orphan*/  (* EGLImageTargetTexture2DOES ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * gl_textures; int /*<<< orphan*/  (* CreateImageKHR ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ;} ;
struct ra_hwdec_mapper {TYPE_2__** tex; int /*<<< orphan*/  ra; struct priv* priv; } ;
struct ra_format {int num_components; int* component_size; } ;
struct TYPE_10__ {int* offsets; int* pitches; } ;
struct priv {int num_planes; TYPE_2__** tex; TYPE_3__ current_image; struct vaapi_gl_mapper_priv* interop_mapper_priv; } ;
typedef  TYPE_3__ VAImage ;
struct TYPE_11__ {int handle; } ;
typedef  TYPE_4__ VABufferInfo ;
struct TYPE_12__ {int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int w; int h; struct ra_format* format; } ;
struct TYPE_9__ {TYPE_1__ params; } ;
typedef  TYPE_5__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_ATTRIB (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EGL_DMA_BUF_PLANE0_FD_EXT ; 
 int /*<<< orphan*/  EGL_DMA_BUF_PLANE0_OFFSET_EXT ; 
 int /*<<< orphan*/  EGL_DMA_BUF_PLANE0_PITCH_EXT ; 
 int /*<<< orphan*/  EGL_HEIGHT ; 
 int /*<<< orphan*/  EGL_LINUX_DMA_BUF_EXT ; 
 int /*<<< orphan*/  EGL_LINUX_DRM_FOURCC_EXT ; 
 int EGL_NONE ; 
 int /*<<< orphan*/  EGL_NO_CONTEXT ; 
 int /*<<< orphan*/  EGL_WIDTH ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  eglGetCurrentDisplay () ; 
 TYPE_5__* ra_gl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vaapi_gl_map_legacy(struct ra_hwdec_mapper *mapper,
                                const VABufferInfo *buffer_info,
                                const int *drm_fmts) {
    struct priv *p_mapper = mapper->priv;
    struct vaapi_gl_mapper_priv *p = p_mapper->interop_mapper_priv;

    GL *gl = ra_gl_get(mapper->ra);

    VAImage *va_image = &p_mapper->current_image;

    for (int n = 0; n < p_mapper->num_planes; n++) {
        int attribs[20] = {EGL_NONE};
        int num_attribs = 0;

        const struct ra_format *fmt = p_mapper->tex[n]->params.format;
        int n_comp = fmt->num_components;
        int comp_s = fmt->component_size[n] / 8;
        if (n_comp < 1 || n_comp > 3 || comp_s < 1 || comp_s > 2)
            return false;
        int drm_fmt = drm_fmts[n_comp - 1 + (comp_s - 1) * 4];
        if (!drm_fmt)
            return false;

        ADD_ATTRIB(EGL_LINUX_DRM_FOURCC_EXT, drm_fmt);
        ADD_ATTRIB(EGL_WIDTH, p_mapper->tex[n]->params.w);
        ADD_ATTRIB(EGL_HEIGHT, p_mapper->tex[n]->params.h);
        ADD_ATTRIB(EGL_DMA_BUF_PLANE0_FD_EXT, buffer_info->handle);
        ADD_ATTRIB(EGL_DMA_BUF_PLANE0_OFFSET_EXT, va_image->offsets[n]);
        ADD_ATTRIB(EGL_DMA_BUF_PLANE0_PITCH_EXT, va_image->pitches[n]);

        p->images[n] = p->CreateImageKHR(eglGetCurrentDisplay(),
            EGL_NO_CONTEXT, EGL_LINUX_DMA_BUF_EXT, NULL, attribs);
        if (!p->images[n])
            return false;

        gl->BindTexture(GL_TEXTURE_2D, p->gl_textures[n]);
        p->EGLImageTargetTexture2DOES(GL_TEXTURE_2D, p->images[n]);

        mapper->tex[n] = p_mapper->tex[n];
    }
    gl->BindTexture(GL_TEXTURE_2D, 0);

    return true;
}