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
struct wined3d_shader_signature_element {unsigned int register_idx; char* semantic_name; unsigned int semantic_idx; scalar_t__ sysval_semantic; int /*<<< orphan*/  mask; } ;
struct wined3d_shader_signature {unsigned int element_count; struct wined3d_shader_signature_element* elements; } ;
struct wined3d_shader_reg_maps {unsigned int input_registers; } ;
struct TYPE_3__ {int /*<<< orphan*/ * input_reg_map; } ;
struct TYPE_4__ {TYPE_1__ ps; } ;
struct wined3d_shader {TYPE_2__ u; } ;
struct wined3d_gl_info {scalar_t__* supported; } ;
struct ps_compile_args {scalar_t__ vp_mode; unsigned int texcoords_initialized; scalar_t__ pointsprite; } ;
typedef  unsigned int UINT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t ARB_FRAGMENT_LAYER_VIEWPORT ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  WINED3D_DECL_USAGE_COLOR ; 
 int /*<<< orphan*/  WINED3D_DECL_USAGE_TEXCOORD ; 
 scalar_t__ WINED3D_SV_IS_FRONT_FACE ; 
 scalar_t__ WINED3D_SV_POSITION ; 
 scalar_t__ WINED3D_SV_RENDER_TARGET_ARRAY_INDEX ; 
 scalar_t__ needs_legacy_glsl_syntax (struct wined3d_gl_info const*) ; 
 scalar_t__ pretransformed ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,size_t,...) ; 
 int /*<<< orphan*/  shader_glsl_shader_input_name (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_glsl_write_mask_to_str (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ shader_match_semantic (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ vertexshader ; 

__attribute__((used)) static void shader_glsl_input_pack(const struct wined3d_shader *shader, struct wined3d_string_buffer *buffer,
        const struct wined3d_shader_signature *input_signature,
        const struct wined3d_shader_reg_maps *reg_maps,
        const struct ps_compile_args *args, const struct wined3d_gl_info *gl_info, BOOL unroll)
{
    unsigned int i;

    for (i = 0; i < input_signature->element_count; ++i)
    {
        const struct wined3d_shader_signature_element *input = &input_signature->elements[i];
        const char *semantic_name;
        UINT semantic_idx;
        char reg_mask[6];

        /* Unused */
        if (!(reg_maps->input_registers & (1u << input->register_idx)))
            continue;

        semantic_name = input->semantic_name;
        semantic_idx = input->semantic_idx;
        shader_glsl_write_mask_to_str(input->mask, reg_mask);

        if (args->vp_mode == vertexshader)
        {
            if (input->sysval_semantic == WINED3D_SV_POSITION && !semantic_idx)
            {
                shader_addline(buffer, "ps_in[%u]%s = vpos%s;\n",
                        shader->u.ps.input_reg_map[input->register_idx], reg_mask, reg_mask);
            }
            else if (args->pointsprite && shader_match_semantic(semantic_name, WINED3D_DECL_USAGE_TEXCOORD))
            {
                shader_addline(buffer, "ps_in[%u] = vec4(gl_PointCoord.xy, 0.0, 0.0);\n", input->register_idx);
            }
            else if (input->sysval_semantic == WINED3D_SV_IS_FRONT_FACE)
            {
                shader_addline(buffer, "ps_in[%u]%s = uintBitsToFloat(gl_FrontFacing ? 0xffffffffu : 0u);\n",
                        input->register_idx, reg_mask);
            }
            else if (input->sysval_semantic == WINED3D_SV_RENDER_TARGET_ARRAY_INDEX && !semantic_idx)
            {
                if (gl_info->supported[ARB_FRAGMENT_LAYER_VIEWPORT])
                    shader_addline(buffer, "ps_in[%u]%s = intBitsToFloat(gl_Layer);\n",
                            input->register_idx, reg_mask);
                else
                    FIXME("ARB_fragment_layer_viewport is not supported.\n");
            }
            else
            {
                if (input->sysval_semantic)
                    FIXME("Unhandled sysval semantic %#x.\n", input->sysval_semantic);
                shader_addline(buffer, unroll ? "ps_in[%u]%s = %s%u%s;\n" : "ps_in[%u]%s = %s[%u]%s;\n",
                        shader->u.ps.input_reg_map[input->register_idx], reg_mask,
                        shader_glsl_shader_input_name(gl_info),
                        shader->u.ps.input_reg_map[input->register_idx], reg_mask);
            }
        }
        else if (shader_match_semantic(semantic_name, WINED3D_DECL_USAGE_TEXCOORD))
        {
            if (args->pointsprite)
                shader_addline(buffer, "ps_in[%u] = vec4(gl_PointCoord.xy, 0.0, 0.0);\n",
                        shader->u.ps.input_reg_map[input->register_idx]);
            else if (args->vp_mode == pretransformed && args->texcoords_initialized & (1u << semantic_idx))
                shader_addline(buffer, "ps_in[%u]%s = %s[%u]%s;\n",
                        shader->u.ps.input_reg_map[input->register_idx], reg_mask,
                        needs_legacy_glsl_syntax(gl_info)
                        ? "gl_TexCoord" : "ffp_varying_texcoord", semantic_idx, reg_mask);
            else
                shader_addline(buffer, "ps_in[%u]%s = vec4(0.0, 0.0, 0.0, 0.0)%s;\n",
                        shader->u.ps.input_reg_map[input->register_idx], reg_mask, reg_mask);
        }
        else if (shader_match_semantic(semantic_name, WINED3D_DECL_USAGE_COLOR))
        {
            if (!semantic_idx)
                shader_addline(buffer, "ps_in[%u]%s = vec4(ffp_varying_diffuse)%s;\n",
                        shader->u.ps.input_reg_map[input->register_idx], reg_mask, reg_mask);
            else if (semantic_idx == 1)
                shader_addline(buffer, "ps_in[%u]%s = vec4(ffp_varying_specular)%s;\n",
                        shader->u.ps.input_reg_map[input->register_idx], reg_mask, reg_mask);
            else
                shader_addline(buffer, "ps_in[%u]%s = vec4(0.0, 0.0, 0.0, 0.0)%s;\n",
                        shader->u.ps.input_reg_map[input->register_idx], reg_mask, reg_mask);
        }
        else
        {
            shader_addline(buffer, "ps_in[%u]%s = vec4(0.0, 0.0, 0.0, 0.0)%s;\n",
                    shader->u.ps.input_reg_map[input->register_idx], reg_mask, reg_mask);
        }
    }
}