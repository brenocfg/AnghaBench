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
struct TYPE_7__ {unsigned int layer_idx; unsigned int layer_count; int /*<<< orphan*/  level_count; int /*<<< orphan*/  level_idx; } ;
struct TYPE_8__ {TYPE_2__ texture; } ;
struct wined3d_view_desc {TYPE_3__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  device; } ;
struct wined3d_texture {TYPE_1__ resource; } ;
struct wined3d_gl_view {scalar_t__ target; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* p_glTexParameteri ) (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glTexParameteriv ) (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ;int /*<<< orphan*/  (* p_glGenTextures ) (int,int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {TYPE_4__ gl; } ;
struct wined3d_gl_info {TYPE_5__ gl_ops; int /*<<< orphan*/ * supported; } ;
struct wined3d_format {int /*<<< orphan*/  glInternal; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  const GLint ;
typedef  scalar_t__ GLenum ;

/* Variables and functions */
 size_t ARB_STENCIL_TEXTURING ; 
 size_t ARB_TEXTURE_VIEW ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  GL_DEPTH_STENCIL_TEXTURE_MODE ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
#define  GL_RED 129 
 int /*<<< orphan*/  GL_STENCIL_INDEX ; 
 scalar_t__ GL_TEXTURE_3D ; 
 int /*<<< orphan*/  GL_TEXTURE_SWIZZLE_RGBA ; 
#define  GL_ZERO 128 
 int /*<<< orphan*/  STATE_COMPUTE_SHADER_RESOURCE_BINDING ; 
 int /*<<< orphan*/  STATE_GRAPHICS_SHADER_RESOURCE_BINDING ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 struct wined3d_context* context_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_bind_texture (struct wined3d_context*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_invalidate_compute_state (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_invalidate_state (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_release (struct wined3d_context*) ; 
 int /*<<< orphan*/  glTextureView (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 scalar_t__ is_stencil_view_format (struct wined3d_format const*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_get_texture_name (struct wined3d_texture*,struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_prepare_texture (struct wined3d_texture*,struct wined3d_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void create_texture_view(struct wined3d_gl_view *view, GLenum view_target,
        const struct wined3d_view_desc *desc, struct wined3d_texture *texture,
        const struct wined3d_format *view_format)
{
    const struct wined3d_gl_info *gl_info;
    unsigned int layer_idx, layer_count;
    struct wined3d_context *context;
    GLuint texture_name;

    view->target = view_target;

    context = context_acquire(texture->resource.device, NULL, 0);
    gl_info = context->gl_info;

    if (!gl_info->supported[ARB_TEXTURE_VIEW])
    {
        context_release(context);
        FIXME("OpenGL implementation does not support texture views.\n");
        return;
    }

    wined3d_texture_prepare_texture(texture, context, FALSE);
    texture_name = wined3d_texture_get_texture_name(texture, context, FALSE);

    layer_idx = desc->u.texture.layer_idx;
    layer_count = desc->u.texture.layer_count;
    if (view_target == GL_TEXTURE_3D && (layer_idx || layer_count != 1))
    {
        FIXME("Depth slice (%u-%u) not supported.\n", layer_idx, layer_count);
        layer_idx = 0;
        layer_count = 1;
    }

    gl_info->gl_ops.gl.p_glGenTextures(1, &view->name);
    GL_EXTCALL(glTextureView(view->name, view->target, texture_name, view_format->glInternal,
            desc->u.texture.level_idx, desc->u.texture.level_count,
            layer_idx, layer_count));
    checkGLcall("Create texture view");

    if (is_stencil_view_format(view_format))
    {
        static const GLint swizzle[] = {GL_ZERO, GL_RED, GL_ZERO, GL_ZERO};

        if (!gl_info->supported[ARB_STENCIL_TEXTURING])
        {
            context_release(context);
            FIXME("OpenGL implementation does not support stencil texturing.\n");
            return;
        }

        context_bind_texture(context, view->target, view->name);
        gl_info->gl_ops.gl.p_glTexParameteriv(view->target, GL_TEXTURE_SWIZZLE_RGBA, swizzle);
        gl_info->gl_ops.gl.p_glTexParameteri(view->target, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_STENCIL_INDEX);
        checkGLcall("Initialize stencil view");

        context_invalidate_compute_state(context, STATE_COMPUTE_SHADER_RESOURCE_BINDING);
        context_invalidate_state(context, STATE_GRAPHICS_SHADER_RESOURCE_BINDING);
    }

    context_release(context);
}