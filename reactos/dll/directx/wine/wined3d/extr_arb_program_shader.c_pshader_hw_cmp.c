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
struct wined3d_shader_instruction {int /*<<< orphan*/ * src; TYPE_1__* ctx; struct wined3d_shader_dst_param* dst; } ;
struct wined3d_shader_dst_param {int dummy; } ;
struct TYPE_2__ {struct wined3d_string_buffer* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  shader_arb_get_dst_param (struct wined3d_shader_instruction const*,struct wined3d_shader_dst_param const*,char*) ; 
 int /*<<< orphan*/  shader_arb_get_modifier (struct wined3d_shader_instruction const*) ; 
 int /*<<< orphan*/  shader_arb_get_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static void pshader_hw_cmp(const struct wined3d_shader_instruction *ins)
{
    const struct wined3d_shader_dst_param *dst = &ins->dst[0];
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    char dst_name[50];
    char src_name[3][50];

    shader_arb_get_dst_param(ins, dst, dst_name);

    /* Generate input register names (with modifiers) */
    shader_arb_get_src_param(ins, &ins->src[0], 0, src_name[0]);
    shader_arb_get_src_param(ins, &ins->src[1], 1, src_name[1]);
    shader_arb_get_src_param(ins, &ins->src[2], 2, src_name[2]);

    shader_addline(buffer, "CMP%s %s, %s, %s, %s;\n", shader_arb_get_modifier(ins),
            dst_name, src_name[0], src_name[2], src_name[1]);
}