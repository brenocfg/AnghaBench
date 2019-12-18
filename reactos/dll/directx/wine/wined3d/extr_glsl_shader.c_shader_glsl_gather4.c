#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_resource_info {scalar_t__ type; int /*<<< orphan*/  data_type; } ;
struct TYPE_8__ {int /*<<< orphan*/  type; } ;
struct wined3d_shader_reg_maps {int /*<<< orphan*/  sampler_map; TYPE_1__ shader_version; } ;
struct TYPE_11__ {int u; int v; int w; } ;
struct wined3d_shader_instruction {scalar_t__ handler_idx; TYPE_4__ texel_offset; TYPE_7__* src; TYPE_6__* dst; TYPE_2__* ctx; } ;
struct wined3d_gl_info {int /*<<< orphan*/ * supported; } ;
struct glsl_src_param {char* param_str; } ;
struct TYPE_12__ {TYPE_3__* idx; } ;
struct TYPE_14__ {int /*<<< orphan*/  swizzle; TYPE_5__ reg; } ;
struct TYPE_13__ {int /*<<< orphan*/  write_mask; } ;
struct TYPE_10__ {unsigned int offset; } ;
struct TYPE_9__ {struct wined3d_string_buffer* buffer; struct wined3d_gl_info* gl_info; struct wined3d_shader_reg_maps* reg_maps; } ;
typedef  int BOOL ;

/* Variables and functions */
 size_t ARB_TEXTURE_GATHER ; 
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ WINED3DSIH_GATHER4_C ; 
 scalar_t__ WINED3DSIH_GATHER4_PO ; 
 scalar_t__ WINED3DSIH_GATHER4_PO_C ; 
 unsigned int WINED3DSP_WRITEMASK_0 ; 
 int /*<<< orphan*/  resource_type_info ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,TYPE_7__*,unsigned int,struct glsl_src_param*) ; 
 int /*<<< orphan*/  shader_glsl_append_dst_ext (struct wined3d_string_buffer*,struct wined3d_shader_instruction const*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_append_imm_ivec (struct wined3d_string_buffer*,int*,unsigned int) ; 
 unsigned int shader_glsl_find_sampler (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  shader_glsl_get_coord_size (scalar_t__,unsigned int*,unsigned int*) ; 
 char* shader_glsl_get_prefix (int /*<<< orphan*/ ) ; 
 struct wined3d_shader_resource_info* shader_glsl_get_resource_info (struct wined3d_shader_instruction const*,TYPE_5__*) ; 
 unsigned int shader_glsl_swizzle_get_component (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_swizzle_to_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wined3d_shader_instruction_has_texel_offset (struct wined3d_shader_instruction const*) ; 

__attribute__((used)) static void shader_glsl_gather4(const struct wined3d_shader_instruction *ins)
{
    unsigned int resource_param_idx, resource_idx, sampler_idx, sampler_bind_idx, component_idx;
    const struct wined3d_shader_reg_maps *reg_maps = ins->ctx->reg_maps;
    const char *prefix = shader_glsl_get_prefix(reg_maps->shader_version.type);
    struct glsl_src_param coord_param, compare_param, offset_param;
    const struct wined3d_gl_info *gl_info = ins->ctx->gl_info;
    const struct wined3d_shader_resource_info *resource_info;
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    unsigned int coord_size, offset_size;
    char dst_swizzle[6];
    BOOL has_offset;

    if (!gl_info->supported[ARB_TEXTURE_GATHER])
    {
        FIXME("OpenGL implementation does not support textureGather.\n");
        return;
    }

    has_offset = ins->handler_idx == WINED3DSIH_GATHER4_PO
            || ins->handler_idx == WINED3DSIH_GATHER4_PO_C
            || wined3d_shader_instruction_has_texel_offset(ins);

    resource_param_idx =
            (ins->handler_idx == WINED3DSIH_GATHER4_PO || ins->handler_idx == WINED3DSIH_GATHER4_PO_C) ? 2 : 1;
    resource_idx = ins->src[resource_param_idx].reg.idx[0].offset;
    sampler_idx = ins->src[resource_param_idx + 1].reg.idx[0].offset;
    component_idx = shader_glsl_swizzle_get_component(ins->src[resource_param_idx + 1].swizzle, 0);
    sampler_bind_idx = shader_glsl_find_sampler(&reg_maps->sampler_map, resource_idx, sampler_idx);

    if (!(resource_info = shader_glsl_get_resource_info(ins, &ins->src[resource_param_idx].reg)))
        return;

    if (resource_info->type >= ARRAY_SIZE(resource_type_info))
    {
        ERR("Unexpected resource type %#x.\n", resource_info->type);
        return;
    }
    shader_glsl_get_coord_size(resource_info->type, &coord_size, &offset_size);

    shader_glsl_swizzle_to_str(ins->src[resource_param_idx].swizzle, FALSE, ins->dst[0].write_mask, dst_swizzle);
    shader_glsl_append_dst_ext(buffer, ins, &ins->dst[0], resource_info->data_type);

    shader_glsl_add_src_param(ins, &ins->src[0], (1u << coord_size) - 1, &coord_param);

    shader_addline(buffer, "textureGather%s(%s_sampler%u, %s",
            has_offset ? "Offset" : "", prefix, sampler_bind_idx, coord_param.param_str);
    if (ins->handler_idx == WINED3DSIH_GATHER4_C || ins->handler_idx == WINED3DSIH_GATHER4_PO_C)
    {
        shader_glsl_add_src_param(ins, &ins->src[resource_param_idx + 2], WINED3DSP_WRITEMASK_0, &compare_param);
        shader_addline(buffer, ", %s", compare_param.param_str);
    }
    if (ins->handler_idx == WINED3DSIH_GATHER4_PO || ins->handler_idx == WINED3DSIH_GATHER4_PO_C)
    {
        shader_glsl_add_src_param(ins, &ins->src[1], (1u << offset_size) - 1, &offset_param);
        shader_addline(buffer, ", %s", offset_param.param_str);
    }
    else if (has_offset)
    {
        int offset_immdata[4] = {ins->texel_offset.u, ins->texel_offset.v, ins->texel_offset.w};
        shader_addline(buffer, ", ");
        shader_glsl_append_imm_ivec(buffer, offset_immdata, offset_size);
    }
    if (component_idx)
        shader_addline(buffer, ", %u", component_idx);

    shader_addline(buffer, ")%s);\n", dst_swizzle);
}