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
typedef  enum parse_assign_op { ____Placeholder_parse_assign_op } parse_assign_op ;
typedef  enum hlsl_ir_expr_op { ____Placeholder_hlsl_ir_expr_op } hlsl_ir_expr_op ;

/* Variables and functions */
#define  HLSL_IR_BINOP_ADD 137 
#define  HLSL_IR_BINOP_BIT_AND 136 
#define  HLSL_IR_BINOP_BIT_OR 135 
#define  HLSL_IR_BINOP_BIT_XOR 134 
#define  HLSL_IR_BINOP_DIV 133 
#define  HLSL_IR_BINOP_LSHIFT 132 
#define  HLSL_IR_BINOP_MOD 131 
#define  HLSL_IR_BINOP_MUL 130 
#define  HLSL_IR_BINOP_RSHIFT 129 
#define  HLSL_IR_BINOP_SUB 128 

__attribute__((used)) static enum hlsl_ir_expr_op op_from_assignment(enum parse_assign_op op)
{
    static const enum hlsl_ir_expr_op ops[] =
    {
        0,
        HLSL_IR_BINOP_ADD,
        HLSL_IR_BINOP_SUB,
        HLSL_IR_BINOP_MUL,
        HLSL_IR_BINOP_DIV,
        HLSL_IR_BINOP_MOD,
        HLSL_IR_BINOP_LSHIFT,
        HLSL_IR_BINOP_RSHIFT,
        HLSL_IR_BINOP_BIT_AND,
        HLSL_IR_BINOP_BIT_OR,
        HLSL_IR_BINOP_BIT_XOR,
    };

    return ops[op];
}