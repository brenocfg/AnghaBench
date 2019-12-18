#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wined3d_string_buffer_list {int dummy; } ;
struct wined3d_string_buffer {int /*<<< orphan*/  buffer; } ;
struct wined3d_shader_reg_maps {int dummy; } ;
struct TYPE_5__ {int instance_count; int /*<<< orphan*/  so_desc; int /*<<< orphan*/  vertices_out; int /*<<< orphan*/  output_type; int /*<<< orphan*/  input_type; } ;
struct TYPE_6__ {TYPE_2__ gs; } ;
struct wined3d_shader {TYPE_3__ u; TYPE_1__* limits; struct wined3d_shader_reg_maps reg_maps; } ;
struct wined3d_gl_info {int /*<<< orphan*/ * supported; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct shader_glsl_priv {struct wined3d_string_buffer shader_buffer; struct wined3d_string_buffer_list string_buffers; } ;
struct shader_glsl_ctx_priv {struct wined3d_string_buffer_list* string_buffers; } ;
struct gs_compile_args {int /*<<< orphan*/  interpolation_mode; int /*<<< orphan*/  output_count; } ;
typedef  int /*<<< orphan*/  priv_ctx ;
struct TYPE_4__ {int /*<<< orphan*/  packed_input; } ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 size_t ARB_CLIP_CONTROL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_GEOMETRY_SHADER ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  glCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glsl_primitive_type_from_d3d (int /*<<< orphan*/ ) ; 
 scalar_t__ is_rasterization_disabled (struct wined3d_shader const*) ; 
 int /*<<< orphan*/  memset (struct shader_glsl_ctx_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_generate_code (struct wined3d_shader const*,struct wined3d_string_buffer*,struct wined3d_shader_reg_maps const*,struct shader_glsl_ctx_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shader_generate_glsl_declarations (struct wined3d_context const*,struct wined3d_string_buffer*,struct wined3d_shader const*,struct wined3d_shader_reg_maps const*,struct shader_glsl_ctx_priv*) ; 
 int /*<<< orphan*/  shader_glsl_add_version_declaration (struct wined3d_string_buffer*,struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_glsl_compile (struct wined3d_gl_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_enable_extensions (struct wined3d_string_buffer*,struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_glsl_generate_sm4_output_setup (struct shader_glsl_priv*,struct wined3d_shader const*,int /*<<< orphan*/ ,struct wined3d_gl_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_generate_stream_output_setup (struct shader_glsl_priv*,struct wined3d_shader const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static GLuint shader_glsl_generate_geometry_shader(const struct wined3d_context *context,
        struct shader_glsl_priv *priv, const struct wined3d_shader *shader, const struct gs_compile_args *args)
{
    struct wined3d_string_buffer_list *string_buffers = &priv->string_buffers;
    const struct wined3d_shader_reg_maps *reg_maps = &shader->reg_maps;
    struct wined3d_string_buffer *buffer = &priv->shader_buffer;
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct shader_glsl_ctx_priv priv_ctx;
    GLuint shader_id;

    memset(&priv_ctx, 0, sizeof(priv_ctx));
    priv_ctx.string_buffers = string_buffers;

    shader_glsl_add_version_declaration(buffer, gl_info);

    shader_glsl_enable_extensions(buffer, gl_info);

    shader_generate_glsl_declarations(context, buffer, shader, reg_maps, &priv_ctx);

    shader_addline(buffer, "layout(%s", glsl_primitive_type_from_d3d(shader->u.gs.input_type));
    if (shader->u.gs.instance_count > 1)
        shader_addline(buffer, ", invocations = %u", shader->u.gs.instance_count);
    shader_addline(buffer, ") in;\n");
    shader_addline(buffer, "layout(%s, max_vertices = %u) out;\n",
            glsl_primitive_type_from_d3d(shader->u.gs.output_type), shader->u.gs.vertices_out);
    shader_addline(buffer, "in shader_in_out { vec4 reg[%u]; } shader_in[];\n", shader->limits->packed_input);

    if (!gl_info->supported[ARB_CLIP_CONTROL])
        shader_addline(buffer, "uniform vec4 pos_fixup;\n");

    if (is_rasterization_disabled(shader))
    {
        shader_glsl_generate_stream_output_setup(priv, shader, &shader->u.gs.so_desc);
    }
    else
    {
        shader_glsl_generate_sm4_output_setup(priv, shader, args->output_count,
                gl_info, TRUE, args->interpolation_mode);
    }
    shader_addline(buffer, "void main()\n{\n");
    if (FAILED(shader_generate_code(shader, buffer, reg_maps, &priv_ctx, NULL, NULL)))
        return 0;
    shader_addline(buffer, "}\n");

    shader_id = GL_EXTCALL(glCreateShader(GL_GEOMETRY_SHADER));
    TRACE("Compiling shader object %u.\n", shader_id);
    shader_glsl_compile(gl_info, shader_id, buffer->buffer);

    return shader_id;
}