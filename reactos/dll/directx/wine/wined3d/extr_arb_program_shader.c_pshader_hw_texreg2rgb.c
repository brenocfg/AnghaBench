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
struct wined3d_shader_instruction {int /*<<< orphan*/ * src; TYPE_3__* dst; } ;
struct TYPE_5__ {TYPE_1__* idx; } ;
struct TYPE_6__ {TYPE_2__ reg; } ;
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  shader_arb_get_dst_param (struct wined3d_shader_instruction const*,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  shader_arb_get_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shader_hw_sample (struct wined3d_shader_instruction const*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pshader_hw_texreg2rgb(const struct wined3d_shader_instruction *ins)
{
    DWORD reg1 = ins->dst[0].reg.idx[0].offset;
    char dst_str[50];
    char src_str[50];

    /* Note that texreg2rg treats Tx as a temporary register, not as a varying */
    shader_arb_get_dst_param(ins, &ins->dst[0], dst_str);
    shader_arb_get_src_param(ins, &ins->src[0], 0, src_str);
    shader_hw_sample(ins, reg1, dst_str, src_str, 0, NULL, NULL);
}