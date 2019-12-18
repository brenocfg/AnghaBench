#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_instruction {struct wined3d_shader_dst_param* dst; int /*<<< orphan*/ * src; TYPE_3__* ctx; } ;
struct TYPE_10__ {TYPE_4__* idx; } ;
struct wined3d_shader_dst_param {TYPE_5__ reg; } ;
struct TYPE_9__ {char* offset; } ;
struct TYPE_8__ {TYPE_2__* reg_maps; struct wined3d_string_buffer* buffer; } ;
struct TYPE_6__ {int major; int minor; } ;
struct TYPE_7__ {TYPE_1__ shader_version; } ;
typedef  char* DWORD ;

/* Variables and functions */
 char* WINED3D_SHADER_VERSION (int,int) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char*,char*) ; 
 int /*<<< orphan*/  shader_arb_get_dst_param (struct wined3d_shader_instruction const*,struct wined3d_shader_dst_param*,char*) ; 
 int /*<<< orphan*/  shader_arb_get_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void pshader_hw_texcoord(const struct wined3d_shader_instruction *ins)
{
    const struct wined3d_shader_dst_param *dst = &ins->dst[0];
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    DWORD shader_version = WINED3D_SHADER_VERSION(ins->ctx->reg_maps->shader_version.major,
            ins->ctx->reg_maps->shader_version.minor);
    char dst_str[50];

    if (shader_version < WINED3D_SHADER_VERSION(1,4))
    {
        DWORD reg = dst->reg.idx[0].offset;

        shader_arb_get_dst_param(ins, &ins->dst[0], dst_str);
        shader_addline(buffer, "MOV_SAT %s, fragment.texcoord[%u];\n", dst_str, reg);
    } else {
        char reg_src[40];

        shader_arb_get_src_param(ins, &ins->src[0], 0, reg_src);
        shader_arb_get_dst_param(ins, &ins->dst[0], dst_str);
        shader_addline(buffer, "MOV %s, %s;\n", dst_str, reg_src);
    }
}