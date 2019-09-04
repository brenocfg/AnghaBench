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
struct hlsl_ir_expr {scalar_t__* operands; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  debug_dump_instr (scalar_t__) ; 
 int /*<<< orphan*/  debug_expr_op (struct hlsl_ir_expr const*) ; 

__attribute__((used)) static void debug_dump_ir_expr(const struct hlsl_ir_expr *expr)
{
    unsigned int i;

    TRACE("%s (", debug_expr_op(expr));
    for (i = 0; i < 3 && expr->operands[i]; ++i)
    {
        debug_dump_instr(expr->operands[i]);
        TRACE(" ");
    }
    TRACE(")");
}