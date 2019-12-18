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
struct source_location {int dummy; } ;
struct hlsl_type {int dimx; int dimy; } ;
struct TYPE_4__ {int /*<<< orphan*/  col; int /*<<< orphan*/  line; int /*<<< orphan*/  file; } ;
struct hlsl_ir_node {TYPE_2__ loc; struct hlsl_type* data_type; } ;
struct TYPE_3__ {struct hlsl_type* data_type; struct source_location loc; int /*<<< orphan*/  type; } ;
struct hlsl_ir_expr {int op; struct hlsl_ir_node** operands; TYPE_1__ node; } ;
typedef  enum hlsl_ir_expr_op { ____Placeholder_hlsl_ir_expr_op } hlsl_ir_expr_op ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  HLSL_IR_EXPR ; 
 int /*<<< orphan*/  HLSL_LEVEL_WARNING ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ compare_hlsl_types (struct hlsl_type*,struct hlsl_type*) ; 
 struct hlsl_ir_expr* d3dcompiler_alloc (int) ; 
 int /*<<< orphan*/  d3dcompiler_free (struct hlsl_ir_expr*) ; 
 int /*<<< orphan*/  debug_hlsl_type (struct hlsl_type*) ; 
 struct hlsl_type* expr_common_type (struct hlsl_type*,struct hlsl_type*,struct source_location*) ; 
 int /*<<< orphan*/  hlsl_report_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct hlsl_ir_node* implicit_conversion (struct hlsl_ir_node*,struct hlsl_type*,TYPE_2__*) ; 

struct hlsl_ir_expr *new_expr(enum hlsl_ir_expr_op op, struct hlsl_ir_node **operands,
        struct source_location *loc)
{
    struct hlsl_ir_expr *expr = d3dcompiler_alloc(sizeof(*expr));
    struct hlsl_type *type;
    unsigned int i;

    if (!expr)
    {
        ERR("Out of memory\n");
        return NULL;
    }
    expr->node.type = HLSL_IR_EXPR;
    expr->node.loc = *loc;
    type = operands[0]->data_type;
    for (i = 1; i <= 2; ++i)
    {
        if (!operands[i])
            break;
        type = expr_common_type(type, operands[i]->data_type, loc);
        if (!type)
        {
            d3dcompiler_free(expr);
            return NULL;
        }
    }
    for (i = 0; i <= 2; ++i)
    {
        if (!operands[i])
            break;
        if (compare_hlsl_types(operands[i]->data_type, type))
            continue;
        TRACE("Implicitly converting %s into %s in an expression\n", debug_hlsl_type(operands[i]->data_type), debug_hlsl_type(type));
        if (operands[i]->data_type->dimx * operands[i]->data_type->dimy != 1
                && operands[i]->data_type->dimx * operands[i]->data_type->dimy != type->dimx * type->dimy)
        {
            hlsl_report_message(operands[i]->loc.file,
                    operands[i]->loc.line, operands[i]->loc.col, HLSL_LEVEL_WARNING,
                    "implicit truncation of vector/matrix type");
        }
        operands[i] = implicit_conversion(operands[i], type, &operands[i]->loc);
        if (!operands[i])
        {
            ERR("Impossible to convert expression operand %u to %s\n", i + 1, debug_hlsl_type(type));
            d3dcompiler_free(expr);
            return NULL;
        }
    }
    expr->node.data_type = type;
    expr->op = op;
    expr->operands[0] = operands[0];
    expr->operands[1] = operands[1];
    expr->operands[2] = operands[2];

    return expr;
}