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
struct source_location {int dummy; } ;
struct hlsl_ir_node {int dummy; } ;
typedef  enum hlsl_ir_expr_op { ____Placeholder_hlsl_ir_expr_op } hlsl_ir_expr_op ;
struct TYPE_2__ {struct hlsl_ir_node node; } ;

/* Variables and functions */
 TYPE_1__* new_expr (int,struct hlsl_ir_node**,struct source_location*) ; 

__attribute__((used)) static inline struct hlsl_ir_node *new_binary_expr(enum hlsl_ir_expr_op op,
        struct hlsl_ir_node *op1, struct hlsl_ir_node *op2, struct source_location loc)
{
    struct hlsl_ir_node *operands[3] = {op1, op2};
    return &new_expr(op, operands, &loc)->node;
}