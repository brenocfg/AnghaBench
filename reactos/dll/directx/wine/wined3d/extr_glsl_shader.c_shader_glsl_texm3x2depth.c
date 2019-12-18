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
struct wined3d_shader_instruction {TYPE_1__* ctx; int /*<<< orphan*/ * src; TYPE_4__* dst; } ;
struct glsl_src_param {int /*<<< orphan*/  param_str; } ;
struct TYPE_7__ {TYPE_2__* idx; } ;
struct TYPE_8__ {TYPE_3__ reg; } ;
struct TYPE_6__ {int offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  buffer; } ;
typedef  int DWORD ;

/* Variables and functions */
 int WINED3DSP_WRITEMASK_0 ; 
 int WINED3DSP_WRITEMASK_1 ; 
 int WINED3DSP_WRITEMASK_2 ; 
 int /*<<< orphan*/  shader_addline (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int,struct glsl_src_param*) ; 

__attribute__((used)) static void shader_glsl_texm3x2depth(const struct wined3d_shader_instruction *ins)
{
    DWORD src_mask = WINED3DSP_WRITEMASK_0 | WINED3DSP_WRITEMASK_1 | WINED3DSP_WRITEMASK_2;
    DWORD dstreg = ins->dst[0].reg.idx[0].offset;
    struct glsl_src_param src0_param;

    shader_glsl_add_src_param(ins, &ins->src[0], src_mask, &src0_param);

    shader_addline(ins->ctx->buffer, "tmp0.y = dot(T%u.xyz, %s);\n", dstreg, src0_param.param_str);
    shader_addline(ins->ctx->buffer, "gl_FragDepth = (tmp0.y == 0.0) ? 1.0 : clamp(tmp0.x / tmp0.y, 0.0, 1.0);\n");
}