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
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wined3d_shader_instruction {int handler_idx; TYPE_4__* ctx; int /*<<< orphan*/  texel_offset; TYPE_6__* src; } ;
struct glsl_src_param {char* param_str; } ;
struct glsl_sample_function {int /*<<< orphan*/  deriv_mask; int /*<<< orphan*/  coord_mask; } ;
struct TYPE_8__ {TYPE_1__* idx; } ;
struct TYPE_11__ {int /*<<< orphan*/  swizzle; TYPE_2__ reg; } ;
struct TYPE_10__ {TYPE_3__* reg_maps; } ;
struct TYPE_9__ {int /*<<< orphan*/  sampler_map; } ;
struct TYPE_7__ {unsigned int offset; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
#define  WINED3DSIH_SAMPLE 131 
#define  WINED3DSIH_SAMPLE_B 130 
#define  WINED3DSIH_SAMPLE_GRAD 129 
#define  WINED3DSIH_SAMPLE_LOD 128 
 int /*<<< orphan*/  WINED3DSP_WRITEMASK_0 ; 
 int /*<<< orphan*/  WINED3D_GLSL_SAMPLE_GRAD ; 
 int /*<<< orphan*/  WINED3D_GLSL_SAMPLE_LOD ; 
 int /*<<< orphan*/  WINED3D_GLSL_SAMPLE_OFFSET ; 
 int /*<<< orphan*/  debug_d3dshaderinstructionhandler (int) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,TYPE_6__*,int /*<<< orphan*/ ,struct glsl_src_param*) ; 
 unsigned int shader_glsl_find_sampler (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  shader_glsl_gen_sample_code (struct wined3d_shader_instruction const*,unsigned int,struct glsl_sample_function*,int /*<<< orphan*/ ,char const*,char const*,char const*,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  shader_glsl_get_sample_function (TYPE_4__*,unsigned int,unsigned int,int /*<<< orphan*/ ,struct glsl_sample_function*) ; 
 int /*<<< orphan*/  shader_glsl_release_sample_function (TYPE_4__*,struct glsl_sample_function*) ; 
 scalar_t__ wined3d_shader_instruction_has_texel_offset (struct wined3d_shader_instruction const*) ; 

__attribute__((used)) static void shader_glsl_sample(const struct wined3d_shader_instruction *ins)
{
    const char *lod_param_str = NULL, *dx_param_str = NULL, *dy_param_str = NULL;
    struct glsl_src_param coord_param, lod_param, dx_param, dy_param;
    unsigned int resource_idx, sampler_idx, sampler_bind_idx;
    struct glsl_sample_function sample_function;
    DWORD flags = 0;

    if (ins->handler_idx == WINED3DSIH_SAMPLE_GRAD)
        flags |= WINED3D_GLSL_SAMPLE_GRAD;
    if (ins->handler_idx == WINED3DSIH_SAMPLE_LOD)
        flags |= WINED3D_GLSL_SAMPLE_LOD;
    if (wined3d_shader_instruction_has_texel_offset(ins))
        flags |= WINED3D_GLSL_SAMPLE_OFFSET;

    resource_idx = ins->src[1].reg.idx[0].offset;
    sampler_idx = ins->src[2].reg.idx[0].offset;

    shader_glsl_get_sample_function(ins->ctx, resource_idx, sampler_idx, flags, &sample_function);
    shader_glsl_add_src_param(ins, &ins->src[0], sample_function.coord_mask, &coord_param);

    switch (ins->handler_idx)
    {
        case WINED3DSIH_SAMPLE:
            break;
        case WINED3DSIH_SAMPLE_B:
            shader_glsl_add_src_param(ins, &ins->src[3], WINED3DSP_WRITEMASK_0, &lod_param);
            lod_param_str = lod_param.param_str;
            break;
        case WINED3DSIH_SAMPLE_GRAD:
            shader_glsl_add_src_param(ins, &ins->src[3], sample_function.deriv_mask, &dx_param);
            shader_glsl_add_src_param(ins, &ins->src[4], sample_function.deriv_mask, &dy_param);
            dx_param_str = dx_param.param_str;
            dy_param_str = dy_param.param_str;
            break;
        case WINED3DSIH_SAMPLE_LOD:
            shader_glsl_add_src_param(ins, &ins->src[3], WINED3DSP_WRITEMASK_0, &lod_param);
            lod_param_str = lod_param.param_str;
            break;
        default:
            ERR("Unhandled opcode %s.\n", debug_d3dshaderinstructionhandler(ins->handler_idx));
            break;
    }

    sampler_bind_idx = shader_glsl_find_sampler(&ins->ctx->reg_maps->sampler_map, resource_idx, sampler_idx);
    shader_glsl_gen_sample_code(ins, sampler_bind_idx, &sample_function, ins->src[1].swizzle,
            dx_param_str, dy_param_str, lod_param_str, &ins->texel_offset, "%s", coord_param.param_str);
    shader_glsl_release_sample_function(ins->ctx, &sample_function);
}