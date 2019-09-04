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
struct hlsl_ir_jump {int type; int /*<<< orphan*/  return_value; } ;

/* Variables and functions */
#define  HLSL_IR_JUMP_BREAK 131 
#define  HLSL_IR_JUMP_CONTINUE 130 
#define  HLSL_IR_JUMP_DISCARD 129 
#define  HLSL_IR_JUMP_RETURN 128 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  debug_dump_instr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void debug_dump_ir_jump(const struct hlsl_ir_jump *jump)
{
    switch (jump->type)
    {
        case HLSL_IR_JUMP_BREAK:
            TRACE("break");
            break;
        case HLSL_IR_JUMP_CONTINUE:
            TRACE("continue");
            break;
        case HLSL_IR_JUMP_DISCARD:
            TRACE("discard");
            break;
        case HLSL_IR_JUMP_RETURN:
            TRACE("return ");
            if (jump->return_value)
                debug_dump_instr(jump->return_value);
            TRACE(";");
            break;
    }
}