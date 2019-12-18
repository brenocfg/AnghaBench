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
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_context {struct wined3d_shader* shader; struct wined3d_string_buffer* buffer; struct wined3d_gl_info* gl_info; struct shader_glsl_ctx_priv* backend_data; } ;
struct TYPE_3__ {int type; } ;
struct TYPE_4__ {TYPE_1__ shader_version; } ;
struct wined3d_shader {TYPE_2__ reg_maps; } ;
struct wined3d_gl_info {int dummy; } ;
struct shader_glsl_ctx_priv {int /*<<< orphan*/  cur_ds_args; int /*<<< orphan*/  cur_vs_args; int /*<<< orphan*/  cur_ps_args; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  WINED3D_SHADER_TYPE_COMPUTE 132 
#define  WINED3D_SHADER_TYPE_DOMAIN 131 
#define  WINED3D_SHADER_TYPE_GEOMETRY 130 
#define  WINED3D_SHADER_TYPE_PIXEL 129 
#define  WINED3D_SHADER_TYPE_VERTEX 128 
 int /*<<< orphan*/  shader_glsl_generate_ds_epilogue (struct wined3d_gl_info const*,struct wined3d_string_buffer*,struct wined3d_shader const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_generate_ps_epilogue (struct wined3d_gl_info const*,struct wined3d_string_buffer*,struct wined3d_shader const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_generate_vs_epilogue (struct wined3d_gl_info const*,struct wined3d_string_buffer*,struct wined3d_shader const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shader_glsl_generate_shader_epilogue(const struct wined3d_shader_context *ctx)
{
    const struct shader_glsl_ctx_priv *priv = ctx->backend_data;
    const struct wined3d_gl_info *gl_info = ctx->gl_info;
    struct wined3d_string_buffer *buffer = ctx->buffer;
    const struct wined3d_shader *shader = ctx->shader;

    switch (shader->reg_maps.shader_version.type)
    {
        case WINED3D_SHADER_TYPE_PIXEL:
            shader_glsl_generate_ps_epilogue(gl_info, buffer, shader, priv->cur_ps_args);
            break;
        case WINED3D_SHADER_TYPE_VERTEX:
            shader_glsl_generate_vs_epilogue(gl_info, buffer, shader, priv->cur_vs_args);
            break;
        case WINED3D_SHADER_TYPE_DOMAIN:
            shader_glsl_generate_ds_epilogue(gl_info, buffer, shader, priv->cur_ds_args);
            break;
        case WINED3D_SHADER_TYPE_GEOMETRY:
        case WINED3D_SHADER_TYPE_COMPUTE:
            break;
        default:
            FIXME("Unhandled shader type %#x.\n", shader->reg_maps.shader_version.type);
            break;
    }
}