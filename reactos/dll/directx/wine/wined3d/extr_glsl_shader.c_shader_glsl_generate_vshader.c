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
struct wined3d_shader_version {int major; } ;
struct wined3d_shader_signature_element {int /*<<< orphan*/  register_idx; } ;
struct wined3d_shader_reg_maps {struct wined3d_shader_version shader_version; int /*<<< orphan*/  input_registers; scalar_t__ input_rel_addressing; } ;
struct TYPE_6__ {unsigned int element_count; struct wined3d_shader_signature_element* elements; } ;
struct wined3d_shader {TYPE_3__ input_signature; TYPE_2__* limits; struct wined3d_shader_reg_maps reg_maps; } ;
struct TYPE_4__ {int /*<<< orphan*/  user_clip_distances; } ;
struct wined3d_gl_info {scalar_t__* supported; TYPE_1__ limits; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct vs_compile_args {scalar_t__ next_shader_type; int /*<<< orphan*/  interpolation_mode; int /*<<< orphan*/  next_shader_input_count; int /*<<< orphan*/  flatshading; scalar_t__ clip_enabled; int /*<<< orphan*/  per_vertex_point_size; scalar_t__ point_size; } ;
struct shader_glsl_priv {struct wined3d_string_buffer shader_buffer; struct wined3d_string_buffer_list string_buffers; } ;
struct shader_glsl_ctx_priv {struct wined3d_string_buffer_list* string_buffers; struct vs_compile_args const* cur_vs_args; } ;
typedef  int /*<<< orphan*/  priv_ctx ;
struct TYPE_5__ {int /*<<< orphan*/  packed_output; } ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 size_t ARB_CLIP_CONTROL ; 
 size_t ARB_DRAW_INSTANCED ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 int /*<<< orphan*/  MAX_TEXTURES ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ WINED3D_SHADER_TYPE_PIXEL ; 
 int /*<<< orphan*/  declare_out_varying (struct wined3d_gl_info const*,struct wined3d_string_buffer*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  glCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct shader_glsl_ctx_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  needs_legacy_glsl_syntax (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_generate_code (struct wined3d_shader const*,struct wined3d_string_buffer*,struct wined3d_shader_reg_maps const*,struct shader_glsl_ctx_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shader_generate_glsl_declarations (struct wined3d_context const*,struct wined3d_string_buffer*,struct wined3d_shader const*,struct wined3d_shader_reg_maps const*,struct shader_glsl_ctx_priv*) ; 
 int /*<<< orphan*/  shader_glsl_add_version_declaration (struct wined3d_string_buffer*,struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_glsl_compile (struct wined3d_gl_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_declare_generic_vertex_attribute (struct wined3d_string_buffer*,struct wined3d_gl_info const*,struct wined3d_shader_signature_element*) ; 
 int /*<<< orphan*/  shader_glsl_enable_extensions (struct wined3d_string_buffer*,struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_glsl_generate_sm4_output_setup (struct shader_glsl_priv*,struct wined3d_shader const*,int /*<<< orphan*/ ,struct wined3d_gl_info const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_generate_vs_epilogue (struct wined3d_gl_info const*,struct wined3d_string_buffer*,struct wined3d_shader const*,struct vs_compile_args const*) ; 
 scalar_t__ shader_glsl_use_explicit_attrib_location (struct wined3d_gl_info const*) ; 
 unsigned int wined3d_log2i (int /*<<< orphan*/ ) ; 

__attribute__((used)) static GLuint shader_glsl_generate_vshader(const struct wined3d_context *context,
        struct shader_glsl_priv *priv, const struct wined3d_shader *shader, const struct vs_compile_args *args)
{
    struct wined3d_string_buffer_list *string_buffers = &priv->string_buffers;
    const struct wined3d_shader_reg_maps *reg_maps = &shader->reg_maps;
    const struct wined3d_shader_version *version = &reg_maps->shader_version;
    struct wined3d_string_buffer *buffer = &priv->shader_buffer;
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct shader_glsl_ctx_priv priv_ctx;
    GLuint shader_id;
    unsigned int i;

    memset(&priv_ctx, 0, sizeof(priv_ctx));
    priv_ctx.cur_vs_args = args;
    priv_ctx.string_buffers = string_buffers;

    shader_glsl_add_version_declaration(buffer, gl_info);

    shader_glsl_enable_extensions(buffer, gl_info);
    if (gl_info->supported[ARB_DRAW_INSTANCED])
        shader_addline(buffer, "#extension GL_ARB_draw_instanced : enable\n");
    if (shader_glsl_use_explicit_attrib_location(gl_info))
        shader_addline(buffer, "#extension GL_ARB_explicit_attrib_location : enable\n");

    /* Base Declarations */
    shader_generate_glsl_declarations(context, buffer, shader, reg_maps, &priv_ctx);

    for (i = 0; i < shader->input_signature.element_count; ++i)
        shader_glsl_declare_generic_vertex_attribute(buffer, gl_info, &shader->input_signature.elements[i]);

    if (args->point_size && !args->per_vertex_point_size)
    {
        shader_addline(buffer, "uniform struct\n{\n");
        shader_addline(buffer, "    float size;\n");
        shader_addline(buffer, "    float size_min;\n");
        shader_addline(buffer, "    float size_max;\n");
        shader_addline(buffer, "} ffp_point;\n");
    }

    if (!needs_legacy_glsl_syntax(gl_info))
    {
        if (args->clip_enabled)
            shader_addline(buffer, "uniform vec4 clip_planes[%u];\n", gl_info->limits.user_clip_distances);

        if (version->major < 3)
        {
            declare_out_varying(gl_info, buffer, args->flatshading, "vec4 ffp_varying_diffuse;\n");
            declare_out_varying(gl_info, buffer, args->flatshading, "vec4 ffp_varying_specular;\n");
            declare_out_varying(gl_info, buffer, FALSE, "vec4 ffp_varying_texcoord[%u];\n", MAX_TEXTURES);
            declare_out_varying(gl_info, buffer, FALSE, "float ffp_varying_fogcoord;\n");
        }
    }

    if (version->major < 4)
        shader_addline(buffer, "void setup_vs_output(in vec4[%u]);\n", shader->limits->packed_output);

    if (args->next_shader_type == WINED3D_SHADER_TYPE_PIXEL && !gl_info->supported[ARB_CLIP_CONTROL])
        shader_addline(buffer, "uniform vec4 pos_fixup;\n");

    if (reg_maps->shader_version.major >= 4)
        shader_glsl_generate_sm4_output_setup(priv, shader, args->next_shader_input_count,
                gl_info, args->next_shader_type == WINED3D_SHADER_TYPE_PIXEL, args->interpolation_mode);

    shader_addline(buffer, "void main()\n{\n");

    if (reg_maps->input_rel_addressing)
    {
        unsigned int highest_input_register = wined3d_log2i(reg_maps->input_registers);
        shader_addline(buffer, "vec4 vs_in[%u];\n", highest_input_register + 1);
        for (i = 0; i < shader->input_signature.element_count; ++i)
        {
            const struct wined3d_shader_signature_element *e = &shader->input_signature.elements[i];
            shader_addline(buffer, "vs_in[%u] = vs_in%u;\n", e->register_idx, e->register_idx);
        }
    }

    if (FAILED(shader_generate_code(shader, buffer, reg_maps, &priv_ctx, NULL, NULL)))
        return 0;

    /* In SM4+ the shader epilogue is generated by the "ret" instruction. */
    if (reg_maps->shader_version.major < 4)
        shader_glsl_generate_vs_epilogue(gl_info, buffer, shader, args);

    shader_addline(buffer, "}\n");

    shader_id = GL_EXTCALL(glCreateShader(GL_VERTEX_SHADER));
    TRACE("Compiling shader object %u.\n", shader_id);
    shader_glsl_compile(gl_info, shader_id, buffer->buffer);

    return shader_id;
}