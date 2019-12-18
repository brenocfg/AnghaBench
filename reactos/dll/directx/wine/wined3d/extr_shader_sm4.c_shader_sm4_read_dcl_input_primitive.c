#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wined3d_sm4_data {int dummy; } ;
struct TYPE_3__ {int patch_vertex_count; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__ primitive_type; } ;
struct wined3d_shader_instruction {TYPE_2__ declaration; } ;
typedef  enum wined3d_sm4_input_primitive_type { ____Placeholder_wined3d_sm4_input_primitive_type } wined3d_sm4_input_primitive_type ;
typedef  int DWORD ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  WINED3D_PT_PATCH ; 
 int /*<<< orphan*/  WINED3D_PT_UNDEFINED ; 
 int WINED3D_SM4_PRIMITIVE_TYPE_MASK ; 
 int WINED3D_SM4_PRIMITIVE_TYPE_SHIFT ; 
 int WINED3D_SM5_INPUT_PT_PATCH1 ; 
 int WINED3D_SM5_INPUT_PT_PATCH32 ; 
 int /*<<< orphan*/ * input_primitive_type_table ; 

__attribute__((used)) static void shader_sm4_read_dcl_input_primitive(struct wined3d_shader_instruction *ins,
        DWORD opcode, DWORD opcode_token, const DWORD *tokens, unsigned int token_count,
        struct wined3d_sm4_data *priv)
{
    enum wined3d_sm4_input_primitive_type primitive_type;

    primitive_type = (opcode_token & WINED3D_SM4_PRIMITIVE_TYPE_MASK) >> WINED3D_SM4_PRIMITIVE_TYPE_SHIFT;
    if (WINED3D_SM5_INPUT_PT_PATCH1 <= primitive_type && primitive_type <= WINED3D_SM5_INPUT_PT_PATCH32)
    {
        ins->declaration.primitive_type.type = WINED3D_PT_PATCH;
        ins->declaration.primitive_type.patch_vertex_count = primitive_type - WINED3D_SM5_INPUT_PT_PATCH1 + 1;
    }
    else if (primitive_type >= ARRAY_SIZE(input_primitive_type_table))
    {
        ins->declaration.primitive_type.type = WINED3D_PT_UNDEFINED;
    }
    else
    {
        ins->declaration.primitive_type.type = input_primitive_type_table[primitive_type];
    }

    if (ins->declaration.primitive_type.type == WINED3D_PT_UNDEFINED)
        FIXME("Unhandled input primitive type %#x.\n", primitive_type);
}