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
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wined3d_shader_reg_maps {TYPE_6__* resource_info; int /*<<< orphan*/  sampler_map; } ;
struct wined3d_shader_instruction {TYPE_3__* ctx; int /*<<< orphan*/  texel_offset; TYPE_5__* src; } ;
struct glsl_src_param {int /*<<< orphan*/ * param_str; } ;
struct glsl_sample_function {int /*<<< orphan*/  coord_mask; } ;
struct TYPE_11__ {int /*<<< orphan*/  type; } ;
struct TYPE_8__ {TYPE_1__* idx; } ;
struct TYPE_10__ {int /*<<< orphan*/  swizzle; TYPE_2__ reg; } ;
struct TYPE_9__ {struct wined3d_shader_reg_maps* reg_maps; } ;
struct TYPE_7__ {unsigned int offset; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_6__*) ; 
 int /*<<< orphan*/  ERR (char*,unsigned int) ; 
 int /*<<< orphan*/  WINED3DSP_WRITEMASK_0 ; 
 int /*<<< orphan*/  WINED3DSP_WRITEMASK_3 ; 
 int /*<<< orphan*/  WINED3D_GLSL_SAMPLE_LOAD ; 
 int /*<<< orphan*/  WINED3D_GLSL_SAMPLE_OFFSET ; 
 unsigned int WINED3D_SAMPLER_DEFAULT ; 
 scalar_t__ is_mipmapped (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multisampled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,TYPE_5__*,int /*<<< orphan*/ ,struct glsl_src_param*) ; 
 unsigned int shader_glsl_find_sampler (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  shader_glsl_gen_sample_code (struct wined3d_shader_instruction const*,unsigned int,struct glsl_sample_function*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  shader_glsl_get_sample_function (TYPE_3__*,unsigned int,unsigned int,int /*<<< orphan*/ ,struct glsl_sample_function*) ; 
 int /*<<< orphan*/  shader_glsl_release_sample_function (TYPE_3__*,struct glsl_sample_function*) ; 
 scalar_t__ wined3d_shader_instruction_has_texel_offset (struct wined3d_shader_instruction const*) ; 

__attribute__((used)) static void shader_glsl_ld(const struct wined3d_shader_instruction *ins)
{
    const struct wined3d_shader_reg_maps *reg_maps = ins->ctx->reg_maps;
    struct glsl_src_param coord_param, lod_param, sample_param;
    unsigned int resource_idx, sampler_idx, sampler_bind_idx;
    struct glsl_sample_function sample_function;
    DWORD flags = WINED3D_GLSL_SAMPLE_LOAD;
    BOOL has_lod_param;

    if (wined3d_shader_instruction_has_texel_offset(ins))
        flags |= WINED3D_GLSL_SAMPLE_OFFSET;

    resource_idx = ins->src[1].reg.idx[0].offset;
    sampler_idx = WINED3D_SAMPLER_DEFAULT;

    if (resource_idx >= ARRAY_SIZE(reg_maps->resource_info))
    {
        ERR("Invalid resource index %u.\n", resource_idx);
        return;
    }
    has_lod_param = is_mipmapped(reg_maps->resource_info[resource_idx].type);

    shader_glsl_get_sample_function(ins->ctx, resource_idx, sampler_idx, flags, &sample_function);
    shader_glsl_add_src_param(ins, &ins->src[0], sample_function.coord_mask, &coord_param);
    shader_glsl_add_src_param(ins, &ins->src[0], WINED3DSP_WRITEMASK_3, &lod_param);
    sampler_bind_idx = shader_glsl_find_sampler(&reg_maps->sampler_map, resource_idx, sampler_idx);
    if (is_multisampled(reg_maps->resource_info[resource_idx].type))
    {
        shader_glsl_add_src_param(ins, &ins->src[2], WINED3DSP_WRITEMASK_0, &sample_param);
        shader_glsl_gen_sample_code(ins, sampler_bind_idx, &sample_function, ins->src[1].swizzle,
                NULL, NULL, NULL, &ins->texel_offset, "%s, %s", coord_param.param_str, sample_param.param_str);
    }
    else
    {
        shader_glsl_gen_sample_code(ins, sampler_bind_idx, &sample_function, ins->src[1].swizzle,
                NULL, NULL, has_lod_param ? lod_param.param_str : NULL, &ins->texel_offset,
                "%s", coord_param.param_str);
    }
    shader_glsl_release_sample_function(ins->ctx, &sample_function);
}