#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wined3d_shader_tex_mx {scalar_t__ current_row; } ;
struct wined3d_shader_instruction {TYPE_3__* ctx; TYPE_4__* dst; int /*<<< orphan*/ * src; } ;
struct glsl_src_param {int /*<<< orphan*/  param_str; } ;
struct TYPE_6__ {TYPE_1__* idx; } ;
struct TYPE_8__ {TYPE_2__ reg; } ;
struct TYPE_7__ {int /*<<< orphan*/  buffer; struct wined3d_shader_tex_mx* tex_mx; } ;
struct TYPE_5__ {int offset; } ;
typedef  int DWORD ;

/* Variables and functions */
 int WINED3DSP_WRITEMASK_0 ; 
 int WINED3DSP_WRITEMASK_1 ; 
 int WINED3DSP_WRITEMASK_2 ; 
 int /*<<< orphan*/  shader_addline (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int,struct glsl_src_param*) ; 
 int /*<<< orphan*/  shader_glsl_append_dst (int /*<<< orphan*/ ,struct wined3d_shader_instruction const*) ; 
 int /*<<< orphan*/  shader_glsl_get_write_mask (TYPE_4__*,char*) ; 

__attribute__((used)) static void shader_glsl_texm3x3(const struct wined3d_shader_instruction *ins)
{
    DWORD src_mask = WINED3DSP_WRITEMASK_0 | WINED3DSP_WRITEMASK_1 | WINED3DSP_WRITEMASK_2;
    struct wined3d_shader_tex_mx *tex_mx = ins->ctx->tex_mx;
    DWORD reg = ins->dst[0].reg.idx[0].offset;
    struct glsl_src_param src0_param;
    char dst_mask[6];

    shader_glsl_add_src_param(ins, &ins->src[0], src_mask, &src0_param);

    shader_glsl_append_dst(ins->ctx->buffer, ins);
    shader_glsl_get_write_mask(&ins->dst[0], dst_mask);
    shader_addline(ins->ctx->buffer, "vec4(tmp0.xy, dot(T%u.xyz, %s), 1.0)%s);\n", reg, src0_param.param_str, dst_mask);

    tex_mx->current_row = 0;
}