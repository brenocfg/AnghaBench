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
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_register {TYPE_3__* idx; } ;
struct wined3d_shader_instruction {int /*<<< orphan*/ * src; TYPE_2__* dst; TYPE_1__* ctx; } ;
struct TYPE_6__ {scalar_t__ offset; } ;
struct TYPE_5__ {struct wined3d_shader_register reg; } ;
struct TYPE_4__ {struct wined3d_string_buffer* buffer; } ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  shader_arb_get_register_name (struct wined3d_shader_instruction const*,struct wined3d_shader_register*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shader_arb_get_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void pshader_hw_texm3x2pad(const struct wined3d_shader_instruction *ins)
{
    DWORD reg = ins->dst[0].reg.idx[0].offset;
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    char src0_name[50], dst_name[50];
    BOOL is_color;
    struct wined3d_shader_register tmp_reg = ins->dst[0].reg;

    shader_arb_get_src_param(ins, &ins->src[0], 0, src0_name);
    /* The next instruction will be a texm3x2tex or texm3x2depth that writes to the uninitialized
     * T<reg+1> register. Use this register to store the calculated vector
     */
    tmp_reg.idx[0].offset = reg + 1;
    shader_arb_get_register_name(ins, &tmp_reg, dst_name, &is_color);
    shader_addline(buffer, "DP3 %s.x, fragment.texcoord[%u], %s;\n", dst_name, reg, src0_name);
}