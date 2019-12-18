#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  srgb_decode; int /*<<< orphan*/  mip_filter; void* min_filter; void* mag_filter; } ;
struct TYPE_14__ {TYPE_4__ sampler_desc; int /*<<< orphan*/  name; } ;
struct wined3d_texture {TYPE_5__ texture_rgb; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* p_glEnd ) () ;int /*<<< orphan*/  (* p_glVertex2i ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glTexCoord3fv ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* p_glBegin ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glTexEnvi ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glTexParameteri ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glEnable ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {TYPE_2__ gl; } ;
struct wined3d_gl_info {TYPE_3__ gl_ops; scalar_t__* supported; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct blt_info {int /*<<< orphan*/  bind_target; TYPE_1__* texcoords; } ;
typedef  enum wined3d_texture_filter_type { ____Placeholder_wined3d_texture_filter_type } wined3d_texture_filter_type ;
struct TYPE_15__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  left; int /*<<< orphan*/  top; } ;
struct TYPE_10__ {int /*<<< orphan*/  x; } ;
typedef  TYPE_6__ RECT ;

/* Variables and functions */
 size_t EXT_TEXTURE_SRGB_DECODE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GL_CLAMP_TO_EDGE ; 
 int /*<<< orphan*/  GL_REPLACE ; 
 int /*<<< orphan*/  GL_SKIP_DECODE_EXT ; 
 int /*<<< orphan*/  GL_TEXTURE_ENV ; 
 int /*<<< orphan*/  GL_TEXTURE_ENV_MODE ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_SRGB_DECODE_EXT ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_S ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_T ; 
 int /*<<< orphan*/  GL_TRIANGLE_STRIP ; 
 int /*<<< orphan*/  WINED3D_TEXF_NONE ; 
 void* WINED3D_TEXF_POINT ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  context_bind_texture (struct wined3d_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub14 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub17 () ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  texture2d_get_blt_info (struct wined3d_texture*,unsigned int,TYPE_6__ const*,struct blt_info*) ; 
 int /*<<< orphan*/  wined3d_gl_mag_filter (int) ; 
 int /*<<< orphan*/  wined3d_gl_min_mip_filter (int,int /*<<< orphan*/ ) ; 

void draw_textured_quad(struct wined3d_texture *texture, unsigned int sub_resource_idx,
        struct wined3d_context *context, const RECT *src_rect, const RECT *dst_rect,
        enum wined3d_texture_filter_type filter)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct blt_info info;

    texture2d_get_blt_info(texture, sub_resource_idx, src_rect, &info);

    gl_info->gl_ops.gl.p_glEnable(info.bind_target);
    checkGLcall("glEnable(bind_target)");

    context_bind_texture(context, info.bind_target, texture->texture_rgb.name);

    /* Filtering for StretchRect */
    gl_info->gl_ops.gl.p_glTexParameteri(info.bind_target, GL_TEXTURE_MAG_FILTER, wined3d_gl_mag_filter(filter));
    checkGLcall("glTexParameteri");
    gl_info->gl_ops.gl.p_glTexParameteri(info.bind_target, GL_TEXTURE_MIN_FILTER,
            wined3d_gl_min_mip_filter(filter, WINED3D_TEXF_NONE));
    checkGLcall("glTexParameteri");
    gl_info->gl_ops.gl.p_glTexParameteri(info.bind_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    gl_info->gl_ops.gl.p_glTexParameteri(info.bind_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    if (context->gl_info->supported[EXT_TEXTURE_SRGB_DECODE])
        gl_info->gl_ops.gl.p_glTexParameteri(info.bind_target, GL_TEXTURE_SRGB_DECODE_EXT, GL_SKIP_DECODE_EXT);
    gl_info->gl_ops.gl.p_glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    checkGLcall("glTexEnvi");

    /* Draw a quad */
    gl_info->gl_ops.gl.p_glBegin(GL_TRIANGLE_STRIP);
    gl_info->gl_ops.gl.p_glTexCoord3fv(&info.texcoords[0].x);
    gl_info->gl_ops.gl.p_glVertex2i(dst_rect->left, dst_rect->top);

    gl_info->gl_ops.gl.p_glTexCoord3fv(&info.texcoords[1].x);
    gl_info->gl_ops.gl.p_glVertex2i(dst_rect->right, dst_rect->top);

    gl_info->gl_ops.gl.p_glTexCoord3fv(&info.texcoords[2].x);
    gl_info->gl_ops.gl.p_glVertex2i(dst_rect->left, dst_rect->bottom);

    gl_info->gl_ops.gl.p_glTexCoord3fv(&info.texcoords[3].x);
    gl_info->gl_ops.gl.p_glVertex2i(dst_rect->right, dst_rect->bottom);
    gl_info->gl_ops.gl.p_glEnd();

    /* Unbind the texture */
    context_bind_texture(context, info.bind_target, 0);

    /* We changed the filtering settings on the texture. Inform the
     * container about this to get the filters reset properly next draw. */
    texture->texture_rgb.sampler_desc.mag_filter = WINED3D_TEXF_POINT;
    texture->texture_rgb.sampler_desc.min_filter = WINED3D_TEXF_POINT;
    texture->texture_rgb.sampler_desc.mip_filter = WINED3D_TEXF_NONE;
    texture->texture_rgb.sampler_desc.srgb_decode = FALSE;
}