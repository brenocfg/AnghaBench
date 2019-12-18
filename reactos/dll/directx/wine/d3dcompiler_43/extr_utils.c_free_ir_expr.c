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
struct hlsl_ir_expr {int /*<<< orphan*/  subexpressions; int /*<<< orphan*/ * operands; } ;

/* Variables and functions */
 int /*<<< orphan*/  d3dcompiler_free (struct hlsl_ir_expr*) ; 
 int /*<<< orphan*/  free_instr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_instr_list (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_ir_expr(struct hlsl_ir_expr *expr)
{
    unsigned int i;

    for (i = 0; i < 3; ++i)
    {
        if (!expr->operands[i])
            break;
        free_instr(expr->operands[i]);
    }
    free_instr_list(expr->subexpressions);
    d3dcompiler_free(expr);
}