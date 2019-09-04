#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ra_tex_params {int dimensions; int d; int render_src; int src_linear; TYPE_3__* format; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct ra_imgfmt_desc {int num_planes; TYPE_3__** planes; int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {scalar_t__ imgfmt; scalar_t__ hw_subfmt; } ;
struct ra_hwdec_mapper {TYPE_6__ dst_params; int /*<<< orphan*/  ra; TYPE_6__ src_params; struct priv* priv; TYPE_1__* owner; } ;
struct priv_owner {int /*<<< orphan*/  probing_formats; } ;
struct TYPE_8__ {int /*<<< orphan*/  image_id; int /*<<< orphan*/  buf; } ;
struct priv {int num_planes; int /*<<< orphan*/ * tex; int /*<<< orphan*/ * gl_textures; void* EGLImageTargetTexture2DOES; void* DestroyImageKHR; void* CreateImageKHR; TYPE_2__ current_image; } ;
struct mp_image {int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* TexParameteri ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GenTextures ) (int,int /*<<< orphan*/ *) ;} ;
struct TYPE_9__ {scalar_t__ ctype; } ;
struct TYPE_7__ {struct priv_owner* priv; } ;
typedef  TYPE_4__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  GL_CLAMP_TO_EDGE ; 
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_S ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_T ; 
 int /*<<< orphan*/  MP_FATAL (struct ra_hwdec_mapper*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ RA_CTYPE_UNORM ; 
 int /*<<< orphan*/  VA_INVALID_ID ; 
 int /*<<< orphan*/  check_fmt (struct ra_hwdec_mapper*,scalar_t__) ; 
 scalar_t__ eglGetProcAddress (char*) ; 
 int /*<<< orphan*/  mp_image_plane_h (struct mp_image*,int) ; 
 int /*<<< orphan*/  mp_image_plane_w (struct mp_image*,int) ; 
 int /*<<< orphan*/  mp_image_set_params (struct mp_image*,TYPE_6__*) ; 
 int /*<<< orphan*/  mp_imgfmt_to_name (scalar_t__) ; 
 int /*<<< orphan*/  ra_create_wrapped_tex (int /*<<< orphan*/ ,struct ra_tex_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_get_imgfmt_desc (int /*<<< orphan*/ ,scalar_t__,struct ra_imgfmt_desc*) ; 
 TYPE_4__* ra_gl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mapper_init(struct ra_hwdec_mapper *mapper)
{
    struct priv_owner *p_owner = mapper->owner->priv;
    struct priv *p = mapper->priv;
    GL *gl = ra_gl_get(mapper->ra);

    p->current_image.buf = p->current_image.image_id = VA_INVALID_ID;

    // EGL_KHR_image_base
    p->CreateImageKHR = (void *)eglGetProcAddress("eglCreateImageKHR");
    p->DestroyImageKHR = (void *)eglGetProcAddress("eglDestroyImageKHR");
    // GL_OES_EGL_image
    p->EGLImageTargetTexture2DOES =
        (void *)eglGetProcAddress("glEGLImageTargetTexture2DOES");

    if (!p->CreateImageKHR || !p->DestroyImageKHR ||
        !p->EGLImageTargetTexture2DOES)
        return -1;

    mapper->dst_params = mapper->src_params;
    mapper->dst_params.imgfmt = mapper->src_params.hw_subfmt;
    mapper->dst_params.hw_subfmt = 0;

    struct ra_imgfmt_desc desc = {0};
    struct mp_image layout = {0};

    if (!ra_get_imgfmt_desc(mapper->ra, mapper->dst_params.imgfmt, &desc))
        return -1;

    p->num_planes = desc.num_planes;
    mp_image_set_params(&layout, &mapper->dst_params);

    gl->GenTextures(4, p->gl_textures);
    for (int n = 0; n < desc.num_planes; n++) {
        gl->BindTexture(GL_TEXTURE_2D, p->gl_textures[n]);
        gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        gl->BindTexture(GL_TEXTURE_2D, 0);

        struct ra_tex_params params = {
            .dimensions = 2,
            .w = mp_image_plane_w(&layout, n),
            .h = mp_image_plane_h(&layout, n),
            .d = 1,
            .format = desc.planes[n],
            .render_src = true,
            .src_linear = true,
        };

        if (params.format->ctype != RA_CTYPE_UNORM)
            return -1;

        p->tex[n] = ra_create_wrapped_tex(mapper->ra, &params,
                                          p->gl_textures[n]);
        if (!p->tex[n])
            return -1;
    }

    if (!p_owner->probing_formats && !check_fmt(mapper, mapper->dst_params.imgfmt))
    {
        MP_FATAL(mapper, "unsupported VA image format %s\n",
                 mp_imgfmt_to_name(mapper->dst_params.imgfmt));
        return -1;
    }

    return 0;
}