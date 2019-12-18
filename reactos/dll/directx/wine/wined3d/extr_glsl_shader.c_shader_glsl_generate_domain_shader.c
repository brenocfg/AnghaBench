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
struct TYPE_4__ {int tessellator_domain; } ;
struct TYPE_5__ {TYPE_1__ ds; } ;
struct wined3d_shader {int /*<<< orphan*/  patch_constant_signature; TYPE_3__* limits; TYPE_2__ u; struct wined3d_shader_reg_maps reg_maps; } ;
struct wined3d_gl_info {int /*<<< orphan*/ * supported; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct shader_glsl_priv {struct wined3d_string_buffer shader_buffer; struct wined3d_string_buffer_list string_buffers; } ;
struct shader_glsl_ctx_priv {struct wined3d_string_buffer_list* string_buffers; struct ds_compile_args const* cur_ds_args; } ;
struct ds_compile_args {int tessellator_output_primitive; int tessellator_partitioning; scalar_t__ next_shader_type; int /*<<< orphan*/  interpolation_mode; int /*<<< orphan*/  output_count; int /*<<< orphan*/  render_offscreen; } ;
typedef  int /*<<< orphan*/  priv_ctx ;
struct TYPE_6__ {int /*<<< orphan*/  packed_input; } ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 size_t ARB_CLIP_CONTROL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_TESS_EVALUATION_SHADER ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WINED3D_SHADER_TYPE_PIXEL ; 
#define  WINED3D_TESSELLATOR_DOMAIN_LINE 138 
#define  WINED3D_TESSELLATOR_DOMAIN_QUAD 137 
#define  WINED3D_TESSELLATOR_DOMAIN_TRIANGLE 136 
#define  WINED3D_TESSELLATOR_OUTPUT_LINE 135 
#define  WINED3D_TESSELLATOR_OUTPUT_POINT 134 
#define  WINED3D_TESSELLATOR_OUTPUT_TRIANGLE_CCW 133 
#define  WINED3D_TESSELLATOR_OUTPUT_TRIANGLE_CW 132 
#define  WINED3D_TESSELLATOR_PARTITIONING_FRACTIONAL_EVEN 131 
#define  WINED3D_TESSELLATOR_PARTITIONING_FRACTIONAL_ODD 130 
#define  WINED3D_TESSELLATOR_PARTITIONING_INTEGER 129 
#define  WINED3D_TESSELLATOR_PARTITIONING_POW2 128 
 int /*<<< orphan*/  glCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct shader_glsl_ctx_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_generate_code (struct wined3d_shader const*,struct wined3d_string_buffer*,struct wined3d_shader_reg_maps const*,struct shader_glsl_ctx_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shader_generate_glsl_declarations (struct wined3d_context const*,struct wined3d_string_buffer*,struct wined3d_shader const*,struct wined3d_shader_reg_maps const*,struct shader_glsl_ctx_priv*) ; 
 int /*<<< orphan*/  shader_glsl_add_version_declaration (struct wined3d_string_buffer*,struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_glsl_compile (struct wined3d_gl_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_enable_extensions (struct wined3d_string_buffer*,struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_glsl_generate_patch_constant_setup (struct wined3d_string_buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_generate_sm4_output_setup (struct shader_glsl_priv*,struct wined3d_shader const*,int /*<<< orphan*/ ,struct wined3d_gl_info const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static GLuint shader_glsl_generate_domain_shader(const struct wined3d_context *context,
        struct shader_glsl_priv *priv, const struct wined3d_shader *shader, const struct ds_compile_args *args)
{
    struct wined3d_string_buffer_list *string_buffers = &priv->string_buffers;
    const struct wined3d_shader_reg_maps *reg_maps = &shader->reg_maps;
    struct wined3d_string_buffer *buffer = &priv->shader_buffer;
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct shader_glsl_ctx_priv priv_ctx;
    GLuint shader_id;

    memset(&priv_ctx, 0, sizeof(priv_ctx));
    priv_ctx.cur_ds_args = args;
    priv_ctx.string_buffers = string_buffers;

    shader_glsl_add_version_declaration(buffer, gl_info);

    shader_glsl_enable_extensions(buffer, gl_info);
    shader_addline(buffer, "#extension GL_ARB_tessellation_shader : enable\n");

    shader_generate_glsl_declarations(context, buffer, shader, reg_maps, &priv_ctx);

    shader_addline(buffer, "layout(");
    switch (shader->u.ds.tessellator_domain)
    {
        case WINED3D_TESSELLATOR_DOMAIN_LINE:
            shader_addline(buffer, "isolines");
            break;
        case WINED3D_TESSELLATOR_DOMAIN_QUAD:
            shader_addline(buffer, "quads");
            break;
        case WINED3D_TESSELLATOR_DOMAIN_TRIANGLE:
            shader_addline(buffer, "triangles");
            break;
    }
    switch (args->tessellator_output_primitive)
    {
        case WINED3D_TESSELLATOR_OUTPUT_TRIANGLE_CW:
            if (args->render_offscreen)
                shader_addline(buffer, ", ccw");
            else
                shader_addline(buffer, ", cw");
            break;
        case WINED3D_TESSELLATOR_OUTPUT_TRIANGLE_CCW:
            if (args->render_offscreen)
                shader_addline(buffer, ", cw");
            else
                shader_addline(buffer, ", ccw");
            break;
        case WINED3D_TESSELLATOR_OUTPUT_POINT:
            shader_addline(buffer, ", point_mode");
            break;
        case WINED3D_TESSELLATOR_OUTPUT_LINE:
            break;
    }
    switch (args->tessellator_partitioning)
    {
        case WINED3D_TESSELLATOR_PARTITIONING_FRACTIONAL_ODD:
            shader_addline(buffer, ", fractional_odd_spacing");
            break;
        case WINED3D_TESSELLATOR_PARTITIONING_FRACTIONAL_EVEN:
            shader_addline(buffer, ", fractional_even_spacing");
            break;
        case WINED3D_TESSELLATOR_PARTITIONING_INTEGER:
        case WINED3D_TESSELLATOR_PARTITIONING_POW2:
            shader_addline(buffer, ", equal_spacing");
            break;
    }
    shader_addline(buffer, ") in;\n");

    shader_addline(buffer, "in shader_in_out { vec4 reg[%u]; } shader_in[];\n", shader->limits->packed_input);

    if (args->next_shader_type == WINED3D_SHADER_TYPE_PIXEL && !gl_info->supported[ARB_CLIP_CONTROL])
        shader_addline(buffer, "uniform vec4 pos_fixup;\n");

    shader_glsl_generate_sm4_output_setup(priv, shader, args->output_count, gl_info,
            args->next_shader_type == WINED3D_SHADER_TYPE_PIXEL, args->interpolation_mode);
    shader_glsl_generate_patch_constant_setup(buffer, &shader->patch_constant_signature, TRUE);

    shader_addline(buffer, "void main()\n{\n");
    shader_addline(buffer, "setup_patch_constant_input();\n");

    if (FAILED(shader_generate_code(shader, buffer, reg_maps, &priv_ctx, NULL, NULL)))
        return 0;

    shader_addline(buffer, "}\n");

    shader_id = GL_EXTCALL(glCreateShader(GL_TESS_EVALUATION_SHADER));
    TRACE("Compiling shader object %u.\n", shader_id);
    shader_glsl_compile(gl_info, shader_id, buffer->buffer);

    return shader_id;
}