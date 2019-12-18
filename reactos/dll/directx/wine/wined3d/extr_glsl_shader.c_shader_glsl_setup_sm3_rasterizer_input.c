#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_signature_element {unsigned int register_idx; char* semantic_name; unsigned int semantic_idx; scalar_t__ sysval_semantic; int /*<<< orphan*/  mask; scalar_t__ stream_idx; } ;
struct wined3d_shader_signature {unsigned int element_count; struct wined3d_shader_signature_element* elements; } ;
struct TYPE_2__ {int major; } ;
struct wined3d_shader_reg_maps {unsigned int output_registers; TYPE_1__ shader_version; int /*<<< orphan*/  cull_distance_mask; int /*<<< orphan*/  clip_distance_mask; } ;
struct wined3d_gl_info {int dummy; } ;
struct shader_glsl_priv {struct wined3d_string_buffer shader_buffer; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINED3D_DECL_USAGE_PSIZE ; 
 scalar_t__ WINED3D_SV_CLIP_DISTANCE ; 
 scalar_t__ WINED3D_SV_CULL_DISTANCE ; 
 scalar_t__ WINED3D_SV_POSITION ; 
 scalar_t__ WINED3D_SV_RENDER_TARGET_ARRAY_INDEX ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_glsl_generate_clip_or_cull_distances (struct wined3d_string_buffer*,struct wined3d_shader_signature_element const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_setup_sm4_shader_output (struct shader_glsl_priv*,unsigned int,struct wined3d_shader_signature const*,struct wined3d_shader_reg_maps const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_setup_vs3_output (struct shader_glsl_priv*,struct wined3d_gl_info const*,int /*<<< orphan*/  const*,struct wined3d_shader_signature const*,struct wined3d_shader_reg_maps const*,struct wined3d_shader_signature const*,struct wined3d_shader_reg_maps const*) ; 
 int /*<<< orphan*/  shader_glsl_write_mask_to_str (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ shader_match_semantic (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shader_glsl_setup_sm3_rasterizer_input(struct shader_glsl_priv *priv,
        const struct wined3d_gl_info *gl_info, const DWORD *map,
        const struct wined3d_shader_signature *input_signature,
        const struct wined3d_shader_reg_maps *reg_maps_in, unsigned int input_count,
        const struct wined3d_shader_signature *output_signature,
        const struct wined3d_shader_reg_maps *reg_maps_out, BOOL per_vertex_point_size)
{
    struct wined3d_string_buffer *buffer = &priv->shader_buffer;
    const char *semantic_name;
    unsigned int semantic_idx;
    char reg_mask[6];
    unsigned int i;

    /* First, sort out position and point size system values. */
    for (i = 0; i < output_signature->element_count; ++i)
    {
        const struct wined3d_shader_signature_element *output = &output_signature->elements[i];

        if (!(reg_maps_out->output_registers & (1u << output->register_idx)))
            continue;

        if (output->stream_idx)
            continue;

        semantic_name = output->semantic_name;
        semantic_idx = output->semantic_idx;
        shader_glsl_write_mask_to_str(output->mask, reg_mask);

        if (output->sysval_semantic == WINED3D_SV_POSITION && !semantic_idx)
        {
            shader_addline(buffer, "gl_Position%s = outputs[%u]%s;\n",
                    reg_mask, output->register_idx, reg_mask);
        }
        else if (shader_match_semantic(semantic_name, WINED3D_DECL_USAGE_PSIZE) && per_vertex_point_size)
        {
            shader_addline(buffer, "gl_PointSize = clamp(outputs[%u].%c, "
                    "ffp_point.size_min, ffp_point.size_max);\n", output->register_idx, reg_mask[1]);
        }
        else if (output->sysval_semantic == WINED3D_SV_RENDER_TARGET_ARRAY_INDEX && !semantic_idx)
        {
            shader_addline(buffer, "gl_Layer = floatBitsToInt(outputs[%u])%s;\n",
                    output->register_idx, reg_mask);
        }
        else if (output->sysval_semantic == WINED3D_SV_CLIP_DISTANCE)
        {
            shader_glsl_generate_clip_or_cull_distances(buffer, output, reg_maps_out->clip_distance_mask);
        }
        else if (output->sysval_semantic == WINED3D_SV_CULL_DISTANCE)
        {
            shader_glsl_generate_clip_or_cull_distances(buffer, output, reg_maps_out->cull_distance_mask);
        }
        else if (output->sysval_semantic)
        {
            FIXME("Unhandled sysval semantic %#x.\n", output->sysval_semantic);
        }
    }

    /* Then, setup the pixel shader input. */
    if (reg_maps_out->shader_version.major < 4)
        shader_glsl_setup_vs3_output(priv, gl_info, map, input_signature, reg_maps_in,
                output_signature, reg_maps_out);
    else
        shader_glsl_setup_sm4_shader_output(priv, input_count, output_signature, reg_maps_out, "shader_out", TRUE);
}