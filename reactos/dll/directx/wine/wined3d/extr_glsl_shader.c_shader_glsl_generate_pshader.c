#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wined3d_string_buffer_list {int dummy; } ;
struct wined3d_string_buffer {int /*<<< orphan*/  buffer; } ;
struct wined3d_shader_version {int major; int /*<<< orphan*/  type; } ;
struct wined3d_shader_reg_maps {int bumpmat; unsigned int luminanceparams; int texcoord; struct wined3d_shader_version shader_version; scalar_t__ vpos; scalar_t__ usesdsy; scalar_t__ input_registers; TYPE_1__* resource_info; } ;
struct TYPE_11__ {scalar_t__ depth_output; scalar_t__ force_early_depth_stencil; int /*<<< orphan*/  interpolation_mode; } ;
struct TYPE_12__ {TYPE_5__ ps; } ;
struct wined3d_shader {int /*<<< orphan*/  input_signature; TYPE_6__ u; TYPE_2__* limits; struct wined3d_shader_reg_maps reg_maps; } ;
struct TYPE_9__ {int dual_buffers; unsigned int buffers; scalar_t__ glsl_ps_float_constants; } ;
struct wined3d_gl_info {scalar_t__* supported; TYPE_3__ limits; } ;
struct wined3d_context {TYPE_4__* d3d_info; struct wined3d_gl_info* gl_info; } ;
struct shader_glsl_ctx_priv {struct ps_np2fixup_info* cur_np2fixup_info; struct wined3d_string_buffer_list* string_buffers; struct ps_compile_args const* cur_ps_args; } ;
struct ps_np2fixup_info {unsigned int num_consts; unsigned int active; int /*<<< orphan*/ * idx; } ;
struct ps_compile_args {int np2_fixup; scalar_t__ vp_mode; scalar_t__ alpha_test_func; unsigned int texcoords_initialized; scalar_t__ pointsprite; scalar_t__ dual_source_blend; scalar_t__ render_offscreen; scalar_t__ srgb_correction; int /*<<< orphan*/  flatshading; } ;
typedef  int /*<<< orphan*/  priv_ctx ;
typedef  int WORD ;
struct TYPE_10__ {int wined3d_creation_flags; } ;
struct TYPE_8__ {unsigned int sampler; scalar_t__ constant_float; int /*<<< orphan*/  packed_input; } ;
struct TYPE_7__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t ARB_CONSERVATIVE_DEPTH ; 
 size_t ARB_DERIVATIVE_CONTROL ; 
 size_t ARB_FRAGMENT_COORD_CONVENTIONS ; 
 size_t ARB_FRAGMENT_LAYER_VIEWPORT ; 
 size_t ARB_SHADER_TEXTURE_LOD ; 
 size_t ARB_TEXTURE_RECTANGLE ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  MAX_TEXTURES ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ WINED3DSPR_DEPTHOUTGE ; 
 scalar_t__ WINED3DSPR_DEPTHOUTLE ; 
 scalar_t__ WINED3D_CMP_ALWAYS ; 
 int WINED3D_PIXEL_CENTER_INTEGER ; 
 scalar_t__ WINED3D_SHADER_RESOURCE_TEXTURE_2D ; 
 int /*<<< orphan*/  declare_in_varying (struct wined3d_gl_info const*,struct wined3d_string_buffer*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  glCreateShader (int /*<<< orphan*/ ) ; 
 scalar_t__ glsl_is_color_reg_read (struct wined3d_shader const*,int) ; 
 int /*<<< orphan*/  memset (struct shader_glsl_ctx_priv*,int /*<<< orphan*/ ,int) ; 
 unsigned int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ needs_legacy_glsl_syntax (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_generate_code (struct wined3d_shader const*,struct wined3d_string_buffer*,struct wined3d_shader_reg_maps const*,struct shader_glsl_ctx_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shader_generate_glsl_declarations (struct wined3d_context const*,struct wined3d_string_buffer*,struct wined3d_shader const*,struct wined3d_shader_reg_maps const*,struct shader_glsl_ctx_priv*) ; 
 int /*<<< orphan*/  shader_glsl_add_version_declaration (struct wined3d_string_buffer*,struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_glsl_append_imm_vec4 (struct wined3d_string_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_compile (struct wined3d_gl_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_declare_shader_inputs (struct wined3d_gl_info const*,struct wined3d_string_buffer*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  shader_glsl_enable_extensions (struct wined3d_string_buffer*,struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_glsl_generate_ps_epilogue (struct wined3d_gl_info const*,struct wined3d_string_buffer*,struct wined3d_shader const*,struct ps_compile_args const*) ; 
 char* shader_glsl_get_prefix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_input_pack (struct wined3d_shader const*,struct wined3d_string_buffer*,int /*<<< orphan*/ *,struct wined3d_shader_reg_maps const*,struct ps_compile_args const*,struct wined3d_gl_info const*,int) ; 
 scalar_t__ shader_glsl_use_explicit_attrib_location (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  vec4_varyings (int,struct wined3d_gl_info const*) ; 
 scalar_t__ vertexshader ; 
 int /*<<< orphan*/  wined3d_srgb_const0 ; 
 int /*<<< orphan*/  wined3d_srgb_const1 ; 

__attribute__((used)) static GLuint shader_glsl_generate_pshader(const struct wined3d_context *context,
        struct wined3d_string_buffer *buffer, struct wined3d_string_buffer_list *string_buffers,
        const struct wined3d_shader *shader,
        const struct ps_compile_args *args, struct ps_np2fixup_info *np2fixup_info)
{
    const struct wined3d_shader_reg_maps *reg_maps = &shader->reg_maps;
    const struct wined3d_shader_version *version = &reg_maps->shader_version;
    const char *prefix = shader_glsl_get_prefix(version->type);
    const struct wined3d_gl_info *gl_info = context->gl_info;
    const BOOL legacy_syntax = needs_legacy_glsl_syntax(gl_info);
    unsigned int i, extra_constants_needed = 0;
    struct shader_glsl_ctx_priv priv_ctx;
    GLuint shader_id;
    DWORD map;

    memset(&priv_ctx, 0, sizeof(priv_ctx));
    priv_ctx.cur_ps_args = args;
    priv_ctx.cur_np2fixup_info = np2fixup_info;
    priv_ctx.string_buffers = string_buffers;

    shader_glsl_add_version_declaration(buffer, gl_info);

    shader_glsl_enable_extensions(buffer, gl_info);
    if (gl_info->supported[ARB_CONSERVATIVE_DEPTH])
        shader_addline(buffer, "#extension GL_ARB_conservative_depth : enable\n");
    if (gl_info->supported[ARB_DERIVATIVE_CONTROL])
        shader_addline(buffer, "#extension GL_ARB_derivative_control : enable\n");
    if (shader_glsl_use_explicit_attrib_location(gl_info))
        shader_addline(buffer, "#extension GL_ARB_explicit_attrib_location : enable\n");
    if (gl_info->supported[ARB_FRAGMENT_COORD_CONVENTIONS])
        shader_addline(buffer, "#extension GL_ARB_fragment_coord_conventions : enable\n");
    if (gl_info->supported[ARB_FRAGMENT_LAYER_VIEWPORT])
        shader_addline(buffer, "#extension GL_ARB_fragment_layer_viewport : enable\n");
    if (gl_info->supported[ARB_SHADER_TEXTURE_LOD])
        shader_addline(buffer, "#extension GL_ARB_shader_texture_lod : enable\n");
    /* The spec says that it doesn't have to be explicitly enabled, but the
     * nvidia drivers write a warning if we don't do so. */
    if (gl_info->supported[ARB_TEXTURE_RECTANGLE])
        shader_addline(buffer, "#extension GL_ARB_texture_rectangle : enable\n");

    /* Base Declarations */
    shader_generate_glsl_declarations(context, buffer, shader, reg_maps, &priv_ctx);

    if (gl_info->supported[ARB_CONSERVATIVE_DEPTH])
    {
        if (shader->u.ps.depth_output == WINED3DSPR_DEPTHOUTGE)
            shader_addline(buffer, "layout (depth_greater) out float gl_FragDepth;\n");
        else if (shader->u.ps.depth_output == WINED3DSPR_DEPTHOUTLE)
            shader_addline(buffer, "layout (depth_less) out float gl_FragDepth;\n");
    }

    /* Declare uniforms for NP2 texcoord fixup:
     * This is NOT done inside the loop that declares the texture samplers
     * since the NP2 fixup code is currently only used for the GeforceFX
     * series and when forcing the ARB_npot extension off. Modern cards just
     * skip the code anyway, so put it inside a separate loop. */
    if (args->np2_fixup)
    {
        struct ps_np2fixup_info *fixup = priv_ctx.cur_np2fixup_info;
        unsigned int cur = 0;

        /* NP2/RECT textures in OpenGL use texcoords in the range [0,width]x[0,height]
         * while D3D has them in the (normalized) [0,1]x[0,1] range.
         * samplerNP2Fixup stores texture dimensions and is updated through
         * shader_glsl_load_np2fixup_constants when the sampler changes. */

        for (i = 0; i < shader->limits->sampler; ++i)
        {
            if (!reg_maps->resource_info[i].type || !(args->np2_fixup & (1u << i)))
                continue;

            if (reg_maps->resource_info[i].type != WINED3D_SHADER_RESOURCE_TEXTURE_2D)
            {
                FIXME("Non-2D texture is flagged for NP2 texcoord fixup.\n");
                continue;
            }

            fixup->idx[i] = cur++;
        }

        fixup->num_consts = (cur + 1) >> 1;
        fixup->active = args->np2_fixup;
        shader_addline(buffer, "uniform vec4 %s_samplerNP2Fixup[%u];\n", prefix, fixup->num_consts);
    }

    if (version->major < 3 || args->vp_mode != vertexshader)
    {
        shader_addline(buffer, "uniform struct\n{\n");
        shader_addline(buffer, "    vec4 color;\n");
        shader_addline(buffer, "    float density;\n");
        shader_addline(buffer, "    float end;\n");
        shader_addline(buffer, "    float scale;\n");
        shader_addline(buffer, "} ffp_fog;\n");

        if (needs_legacy_glsl_syntax(gl_info))
        {
            if (glsl_is_color_reg_read(shader, 0))
                shader_addline(buffer, "vec4 ffp_varying_diffuse;\n");
            if (glsl_is_color_reg_read(shader, 1))
                shader_addline(buffer, "vec4 ffp_varying_specular;\n");
            shader_addline(buffer, "vec4 ffp_texcoord[%u];\n", MAX_TEXTURES);
            shader_addline(buffer, "float ffp_varying_fogcoord;\n");
        }
        else
        {
            if (glsl_is_color_reg_read(shader, 0))
                declare_in_varying(gl_info, buffer, args->flatshading, "vec4 ffp_varying_diffuse;\n");
            if (glsl_is_color_reg_read(shader, 1))
                declare_in_varying(gl_info, buffer, args->flatshading, "vec4 ffp_varying_specular;\n");
            declare_in_varying(gl_info, buffer, FALSE, "vec4 ffp_varying_texcoord[%u];\n", MAX_TEXTURES);
            shader_addline(buffer, "vec4 ffp_texcoord[%u];\n", MAX_TEXTURES);
            declare_in_varying(gl_info, buffer, FALSE, "float ffp_varying_fogcoord;\n");
        }
    }

    if (version->major >= 3)
    {
        unsigned int in_count = min(vec4_varyings(version->major, gl_info), shader->limits->packed_input);

        if (args->vp_mode == vertexshader && reg_maps->input_registers)
            shader_glsl_declare_shader_inputs(gl_info, buffer, in_count,
                    shader->u.ps.interpolation_mode, version->major >= 4);
        shader_addline(buffer, "vec4 %s_in[%u];\n", prefix, in_count);
    }

    for (i = 0, map = reg_maps->bumpmat; map; map >>= 1, ++i)
    {
        if (!(map & 1))
            continue;

        shader_addline(buffer, "uniform mat2 bumpenv_mat%u;\n", i);

        if (reg_maps->luminanceparams & (1u << i))
        {
            shader_addline(buffer, "uniform float bumpenv_lum_scale%u;\n", i);
            shader_addline(buffer, "uniform float bumpenv_lum_offset%u;\n", i);
            extra_constants_needed++;
        }

        extra_constants_needed++;
    }

    if (args->srgb_correction)
    {
        shader_addline(buffer, "const vec4 srgb_const0 = ");
        shader_glsl_append_imm_vec4(buffer, wined3d_srgb_const0);
        shader_addline(buffer, ";\n");
        shader_addline(buffer, "const vec4 srgb_const1 = ");
        shader_glsl_append_imm_vec4(buffer, wined3d_srgb_const1);
        shader_addline(buffer, ";\n");
    }
    if (reg_maps->vpos || reg_maps->usesdsy)
    {
        if (reg_maps->usesdsy || !gl_info->supported[ARB_FRAGMENT_COORD_CONVENTIONS])
        {
            ++extra_constants_needed;
            shader_addline(buffer, "uniform vec4 ycorrection;\n");
        }
        if (reg_maps->vpos)
        {
            if (gl_info->supported[ARB_FRAGMENT_COORD_CONVENTIONS])
            {
                if (context->d3d_info->wined3d_creation_flags & WINED3D_PIXEL_CENTER_INTEGER)
                    shader_addline(buffer, "layout(%spixel_center_integer) in vec4 gl_FragCoord;\n",
                            args->render_offscreen ? "" : "origin_upper_left, ");
                else if (!args->render_offscreen)
                    shader_addline(buffer, "layout(origin_upper_left) in vec4 gl_FragCoord;\n");
            }
            shader_addline(buffer, "vec4 vpos;\n");
        }
    }

    if (args->alpha_test_func + 1 != WINED3D_CMP_ALWAYS)
        shader_addline(buffer, "uniform float alpha_test_ref;\n");

    if (!needs_legacy_glsl_syntax(gl_info))
    {
        if (args->dual_source_blend)
        {
            for (i = 0; i < gl_info->limits.dual_buffers * 2; i++)
            {
                if (shader_glsl_use_explicit_attrib_location(gl_info))
                    shader_addline(buffer, "layout(location = %u, index = %u) ", i / 2, i % 2);
                shader_addline(buffer, "out vec4 ps_out%u;\n", i);
            }
        }
        else
        {
            for (i = 0; i < gl_info->limits.buffers; i++)
            {
                if (shader_glsl_use_explicit_attrib_location(gl_info))
                    shader_addline(buffer, "layout(location = %u) ", i);
                shader_addline(buffer, "out vec4 ps_out%u;\n", i);
            }
        }
    }

    if (shader->limits->constant_float + extra_constants_needed >= gl_info->limits.glsl_ps_float_constants)
        FIXME("Insufficient uniforms to run this shader.\n");

    if (shader->u.ps.force_early_depth_stencil)
        shader_addline(buffer, "layout(early_fragment_tests) in;\n");

    shader_addline(buffer, "void main()\n{\n");

    /* Direct3D applications expect integer vPos values, while OpenGL drivers
     * add approximately 0.5. This causes off-by-one problems as spotted by
     * the vPos d3d9 visual test. Unfortunately ATI cards do not add exactly
     * 0.5, but rather something like 0.49999999 or 0.50000001, which still
     * causes precision troubles when we just subtract 0.5.
     *
     * To deal with that, just floor() the position. This will eliminate the
     * fraction on all cards.
     *
     * TODO: Test how this behaves with multisampling.
     *
     * An advantage of floor is that it works even if the driver doesn't add
     * 0.5. It is somewhat questionable if 1.5, 2.5, ... are the proper values
     * to return in gl_FragCoord, even though coordinates specify the pixel
     * centers instead of the pixel corners. This code will behave correctly
     * on drivers that returns integer values. */
    if (reg_maps->vpos)
    {
        if (gl_info->supported[ARB_FRAGMENT_COORD_CONVENTIONS])
            shader_addline(buffer, "vpos = gl_FragCoord;\n");
        else if (context->d3d_info->wined3d_creation_flags & WINED3D_PIXEL_CENTER_INTEGER)
            shader_addline(buffer,
                    "vpos = floor(vec4(0, ycorrection[0], 0, 0) + gl_FragCoord * vec4(1, ycorrection[1], 1, 1));\n");
        else
            shader_addline(buffer,
                    "vpos = vec4(0, ycorrection[0], 0, 0) + gl_FragCoord * vec4(1, ycorrection[1], 1, 1);\n");
    }

    if (reg_maps->shader_version.major < 3 || args->vp_mode != vertexshader)
    {
        unsigned int i;
        WORD map = reg_maps->texcoord;

        if (legacy_syntax)
        {
            if (glsl_is_color_reg_read(shader, 0))
                shader_addline(buffer, "ffp_varying_diffuse = gl_Color;\n");
            if (glsl_is_color_reg_read(shader, 1))
                shader_addline(buffer, "ffp_varying_specular = gl_SecondaryColor;\n");
        }

        for (i = 0; map; map >>= 1, ++i)
        {
            if (map & 1)
            {
                if (args->pointsprite)
                    shader_addline(buffer, "ffp_texcoord[%u] = vec4(gl_PointCoord.xy, 0.0, 0.0);\n", i);
                else if (args->texcoords_initialized & (1u << i))
                    shader_addline(buffer, "ffp_texcoord[%u] = %s[%u];\n", i,
                            legacy_syntax ? "gl_TexCoord" : "ffp_varying_texcoord", i);
                else
                    shader_addline(buffer, "ffp_texcoord[%u] = vec4(0.0);\n", i);
                shader_addline(buffer, "vec4 T%u = ffp_texcoord[%u];\n", i, i);
            }
        }

        if (legacy_syntax)
            shader_addline(buffer, "ffp_varying_fogcoord = gl_FogFragCoord;\n");
    }

    /* Pack 3.0 inputs */
    if (reg_maps->shader_version.major >= 3)
        shader_glsl_input_pack(shader, buffer, &shader->input_signature, reg_maps, args, gl_info,
                reg_maps->shader_version.major >= 4);

    /* Base Shader Body */
    if (FAILED(shader_generate_code(shader, buffer, reg_maps, &priv_ctx, NULL, NULL)))
        return 0;

    /* In SM4+ the shader epilogue is generated by the "ret" instruction. */
    if (reg_maps->shader_version.major < 4)
        shader_glsl_generate_ps_epilogue(gl_info, buffer, shader, args);

    shader_addline(buffer, "}\n");

    shader_id = GL_EXTCALL(glCreateShader(GL_FRAGMENT_SHADER));
    TRACE("Compiling shader object %u.\n", shader_id);
    shader_glsl_compile(gl_info, shader_id, buffer->buffer);

    return shader_id;
}