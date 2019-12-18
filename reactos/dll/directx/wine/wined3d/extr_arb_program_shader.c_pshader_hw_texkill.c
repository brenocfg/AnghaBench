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
struct wined3d_shader_instruction {TYPE_3__* ctx; struct wined3d_shader_dst_param* dst; } ;
struct TYPE_10__ {TYPE_4__* idx; } ;
struct wined3d_shader_dst_param {int write_mask; TYPE_5__ reg; } ;
struct TYPE_9__ {int offset; } ;
struct TYPE_8__ {TYPE_2__* reg_maps; struct wined3d_string_buffer* buffer; } ;
struct TYPE_6__ {int major; int minor; } ;
struct TYPE_7__ {TYPE_1__ shader_version; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int WINED3DSP_WRITEMASK_0 ; 
 int WINED3DSP_WRITEMASK_1 ; 
 int WINED3DSP_WRITEMASK_2 ; 
 int WINED3DSP_WRITEMASK_3 ; 
 int WINED3DSP_WRITEMASK_ALL ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_arb_get_dst_param (struct wined3d_shader_instruction const*,struct wined3d_shader_dst_param const*,char*) ; 
 int /*<<< orphan*/  shader_arb_get_register_name (struct wined3d_shader_instruction const*,TYPE_5__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void pshader_hw_texkill(const struct wined3d_shader_instruction *ins)
{
    const struct wined3d_shader_dst_param *dst = &ins->dst[0];
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    char reg_dest[40];

    /* No swizzles are allowed in d3d's texkill. PS 1.x ignores the 4th component as documented,
     * but >= 2.0 honors it (undocumented, but tested by the d3d9 testsuite)
     */
    shader_arb_get_dst_param(ins, dst, reg_dest);

    if (ins->ctx->reg_maps->shader_version.major >= 2)
    {
        const char *kilsrc = "TA";
        BOOL is_color;

        shader_arb_get_register_name(ins, &dst->reg, reg_dest, &is_color);
        if(dst->write_mask == WINED3DSP_WRITEMASK_ALL)
        {
            kilsrc = reg_dest;
        }
        else
        {
            /* Sigh. KIL doesn't support swizzles/writemasks. KIL passes a writemask, but ".xy" for example
             * is not valid as a swizzle in ARB (needs ".xyyy"). Use SWZ to load the register properly, and set
             * masked out components to 0(won't kill)
             */
            char x = '0', y = '0', z = '0', w = '0';
            if(dst->write_mask & WINED3DSP_WRITEMASK_0) x = 'x';
            if(dst->write_mask & WINED3DSP_WRITEMASK_1) y = 'y';
            if(dst->write_mask & WINED3DSP_WRITEMASK_2) z = 'z';
            if(dst->write_mask & WINED3DSP_WRITEMASK_3) w = 'w';
            shader_addline(buffer, "SWZ TA, %s, %c, %c, %c, %c;\n", reg_dest, x, y, z, w);
        }
        shader_addline(buffer, "KIL %s;\n", kilsrc);
    }
    else
    {
        /* ARB fp doesn't like swizzles on the parameter of the KIL instruction. To mask the 4th component,
         * copy the register into our general purpose TMP variable, overwrite .w and pass TMP to KIL
         *
         * ps_1_3 shaders use the texcoord incarnation of the Tx register. ps_1_4 shaders can use the same,
         * or pass in any temporary register(in shader phase 2)
         */
        if (ins->ctx->reg_maps->shader_version.minor <= 3)
            sprintf(reg_dest, "fragment.texcoord[%u]", dst->reg.idx[0].offset);
        else
            shader_arb_get_dst_param(ins, dst, reg_dest);
        shader_addline(buffer, "SWZ TA, %s, x, y, z, 1;\n", reg_dest);
        shader_addline(buffer, "KIL TA;\n");
    }
}