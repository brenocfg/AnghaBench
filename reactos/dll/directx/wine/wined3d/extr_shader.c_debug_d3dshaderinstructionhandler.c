#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum WINED3D_SHADER_INSTRUCTION_HANDLER { ____Placeholder_WINED3D_SHADER_INSTRUCTION_HANDLER } WINED3D_SHADER_INSTRUCTION_HANDLER ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 char const** shader_opcode_names ; 
 char const* wine_dbg_sprintf (char*,int) ; 

const char *debug_d3dshaderinstructionhandler(enum WINED3D_SHADER_INSTRUCTION_HANDLER handler_idx)
{
    if (handler_idx >= ARRAY_SIZE(shader_opcode_names))
        return wine_dbg_sprintf("UNRECOGNIZED(%#x)", handler_idx);

    return shader_opcode_names[handler_idx];
}