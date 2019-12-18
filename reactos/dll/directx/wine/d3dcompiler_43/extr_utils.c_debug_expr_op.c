#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  data_type; } ;
struct hlsl_ir_expr {size_t op; TYPE_1__ node; } ;

/* Variables and functions */
 size_t HLSL_IR_UNOP_CAST ; 
 char const* debug_hlsl_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *debug_expr_op(const struct hlsl_ir_expr *expr)
{
    static const char * const op_names[] =
    {
        "~",
        "!",
        "-",
        "abs",
        "sign",
        "rcp",
        "rsq",
        "sqrt",
        "nrm",
        "exp2",
        "log2",

        "cast",

        "fract",

        "sin",
        "cos",
        "sin_reduced",
        "cos_reduced",

        "dsx",
        "dsy",

        "sat",

        "pre++",
        "pre--",
        "post++",
        "post--",

        "+",
        "-",
        "*",
        "/",

        "%",

        "<",
        ">",
        "<=",
        ">=",
        "==",
        "!=",

        "&&",
        "||",

        "<<",
        ">>",
        "&",
        "|",
        "^",

        "dot",
        "crs",
        "min",
        "max",

        "pow",

        "lerp",

        ",",
    };

    if (expr->op == HLSL_IR_UNOP_CAST)
        return debug_hlsl_type(expr->node.data_type);

    return op_names[expr->op];
}