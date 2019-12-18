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
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_instruction {int /*<<< orphan*/ * src; int /*<<< orphan*/  flags; TYPE_3__* ctx; } ;
struct TYPE_8__ {int /*<<< orphan*/  loop; } ;
struct control_frame {TYPE_4__ no; } ;
struct TYPE_7__ {int /*<<< orphan*/  backend_data; TYPE_2__* reg_maps; struct wined3d_string_buffer* buffer; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {TYPE_1__ shader_version; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 struct control_frame* find_last_loop (int /*<<< orphan*/ ) ; 
 char* get_compare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char const*,...) ; 
 int /*<<< orphan*/  shader_arb_get_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ shader_is_vshader_version (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shader_hw_breakc(const struct wined3d_shader_instruction *ins)
{
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    BOOL vshader = shader_is_vshader_version(ins->ctx->reg_maps->shader_version.type);
    const struct control_frame *control_frame = find_last_loop(ins->ctx->backend_data);
    char src_name0[50];
    char src_name1[50];
    const char *comp = get_compare(ins->flags);

    shader_arb_get_src_param(ins, &ins->src[0], 0, src_name0);
    shader_arb_get_src_param(ins, &ins->src[1], 1, src_name1);

    if(vshader)
    {
        /* SUBC CC, src0, src1" works only in pixel shaders, so use TA to throw
         * away the subtraction result
         */
        shader_addline(buffer, "SUBC TA, %s, %s;\n", src_name0, src_name1);
        shader_addline(buffer, "BRA loop_%u_end (%s.x);\n", control_frame->no.loop, comp);
    }
    else
    {
        shader_addline(buffer, "SUBC TA, %s, %s;\n", src_name0, src_name1);
        shader_addline(buffer, "BRK (%s.x);\n", comp);
    }
}