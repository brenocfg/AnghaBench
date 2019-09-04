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
struct source_location {int dummy; } ;
struct hlsl_ir_node {int dummy; } ;
struct hlsl_ir_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HLSL_IR_BINOP_ADD ; 
 struct hlsl_ir_expr* new_expr (int /*<<< orphan*/ ,struct hlsl_ir_node**,struct source_location*) ; 

struct hlsl_ir_expr *hlsl_add(struct hlsl_ir_node *op1, struct hlsl_ir_node *op2,
        struct source_location *loc)
{
    struct hlsl_ir_expr *expr;
    struct hlsl_ir_node *ops[3];

    ops[0] = op1;
    ops[1] = op2;
    ops[2] = NULL;
    expr = new_expr(HLSL_IR_BINOP_ADD, ops, loc);
    return expr;
}