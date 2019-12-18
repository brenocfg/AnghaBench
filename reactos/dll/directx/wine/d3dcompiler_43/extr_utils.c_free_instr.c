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
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
#define  HLSL_IR_ASSIGNMENT 135 
#define  HLSL_IR_CONSTANT 134 
#define  HLSL_IR_CONSTRUCTOR 133 
#define  HLSL_IR_DEREF 132 
#define  HLSL_IR_EXPR 131 
#define  HLSL_IR_IF 130 
#define  HLSL_IR_JUMP 129 
#define  HLSL_IR_SWIZZLE 128 
 int /*<<< orphan*/  assignment_from_node (struct hlsl_ir_node*) ; 
 int /*<<< orphan*/  constant_from_node (struct hlsl_ir_node*) ; 
 int /*<<< orphan*/  constructor_from_node (struct hlsl_ir_node*) ; 
 int /*<<< orphan*/  debug_node_type (int) ; 
 int /*<<< orphan*/  deref_from_node (struct hlsl_ir_node*) ; 
 int /*<<< orphan*/  expr_from_node (struct hlsl_ir_node*) ; 
 int /*<<< orphan*/  free_ir_assignment (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_ir_constant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_ir_constructor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_ir_deref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_ir_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_ir_if (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_ir_jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_ir_swizzle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_from_node (struct hlsl_ir_node*) ; 
 int /*<<< orphan*/  jump_from_node (struct hlsl_ir_node*) ; 
 int /*<<< orphan*/  swizzle_from_node (struct hlsl_ir_node*) ; 

void free_instr(struct hlsl_ir_node *node)
{
    switch (node->type)
    {
        case HLSL_IR_CONSTANT:
            free_ir_constant(constant_from_node(node));
            break;
        case HLSL_IR_DEREF:
            free_ir_deref(deref_from_node(node));
            break;
        case HLSL_IR_SWIZZLE:
            free_ir_swizzle(swizzle_from_node(node));
            break;
        case HLSL_IR_CONSTRUCTOR:
            free_ir_constructor(constructor_from_node(node));
            break;
        case HLSL_IR_EXPR:
            free_ir_expr(expr_from_node(node));
            break;
        case HLSL_IR_ASSIGNMENT:
            free_ir_assignment(assignment_from_node(node));
            break;
        case HLSL_IR_IF:
            free_ir_if(if_from_node(node));
            break;
        case HLSL_IR_JUMP:
            free_ir_jump(jump_from_node(node));
            break;
        default:
            FIXME("Unsupported node type %s\n", debug_node_type(node->type));
    }
}