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
struct hlsl_ir_node {int type; } ;

/* Variables and functions */
#define  HLSL_IR_ASSIGNMENT 135 
#define  HLSL_IR_CONSTANT 134 
#define  HLSL_IR_CONSTRUCTOR 133 
#define  HLSL_IR_DEREF 132 
#define  HLSL_IR_EXPR 131 
#define  HLSL_IR_IF 130 
#define  HLSL_IR_JUMP 129 
#define  HLSL_IR_SWIZZLE 128 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assignment_from_node (struct hlsl_ir_node const*) ; 
 int /*<<< orphan*/  constant_from_node (struct hlsl_ir_node const*) ; 
 int /*<<< orphan*/  constructor_from_node (struct hlsl_ir_node const*) ; 
 int /*<<< orphan*/  debug_dump_ir_assignment (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_dump_ir_constant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_dump_ir_constructor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_dump_ir_deref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_dump_ir_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_dump_ir_if (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_dump_ir_jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_dump_ir_swizzle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_node_type (int) ; 
 int /*<<< orphan*/  deref_from_node (struct hlsl_ir_node const*) ; 
 int /*<<< orphan*/  expr_from_node (struct hlsl_ir_node const*) ; 
 int /*<<< orphan*/  if_from_node (struct hlsl_ir_node const*) ; 
 int /*<<< orphan*/  jump_from_node (struct hlsl_ir_node const*) ; 
 int /*<<< orphan*/  swizzle_from_node (struct hlsl_ir_node const*) ; 

__attribute__((used)) static void debug_dump_instr(const struct hlsl_ir_node *instr)
{
    switch (instr->type)
    {
        case HLSL_IR_EXPR:
            debug_dump_ir_expr(expr_from_node(instr));
            break;
        case HLSL_IR_DEREF:
            debug_dump_ir_deref(deref_from_node(instr));
            break;
        case HLSL_IR_CONSTANT:
            debug_dump_ir_constant(constant_from_node(instr));
            break;
        case HLSL_IR_ASSIGNMENT:
            debug_dump_ir_assignment(assignment_from_node(instr));
            break;
        case HLSL_IR_SWIZZLE:
            debug_dump_ir_swizzle(swizzle_from_node(instr));
            break;
        case HLSL_IR_CONSTRUCTOR:
            debug_dump_ir_constructor(constructor_from_node(instr));
            break;
        case HLSL_IR_JUMP:
            debug_dump_ir_jump(jump_from_node(instr));
            break;
        case HLSL_IR_IF:
            debug_dump_ir_if(if_from_node(instr));
            break;
        default:
            TRACE("<No dump function for %s>", debug_node_type(instr->type));
    }
}