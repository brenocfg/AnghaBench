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
struct wined3d_shader_instruction {TYPE_4__* src; TYPE_1__* ctx; } ;
struct glsl_src_param {int /*<<< orphan*/  param_str; } ;
struct TYPE_7__ {TYPE_2__* idx; } ;
struct TYPE_8__ {TYPE_3__ reg; } ;
struct TYPE_6__ {int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  WINED3DSP_WRITEMASK_0 ; 
 int /*<<< orphan*/  shader_addline (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,TYPE_4__*,int /*<<< orphan*/ ,struct glsl_src_param*) ; 

__attribute__((used)) static void shader_glsl_callnz(const struct wined3d_shader_instruction *ins)
{
    struct glsl_src_param src1_param;

    shader_glsl_add_src_param(ins, &ins->src[1], WINED3DSP_WRITEMASK_0, &src1_param);
    shader_addline(ins->ctx->buffer, "if (%s) subroutine%u();\n",
            src1_param.param_str, ins->src[0].reg.idx[0].offset);
}