#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ operation; } ;
struct TYPE_5__ {TYPE_1__ node; } ;
typedef  TYPE_2__ stack_node_t ;

/* Variables and functions */
 scalar_t__ RPN_OPERATOR_EQUAL ; 
 scalar_t__ RPN_OPERATOR_PARENT ; 
 scalar_t__ RPN_OPERATOR_PERCENT ; 
 int /*<<< orphan*/  pop () ; 
 TYPE_2__* stack ; 

void exec_change_infix(void)
{
    stack_node_t *op = stack;

    if (op == NULL)
        return;
    if (op->node.operation == RPN_OPERATOR_PARENT ||
        op->node.operation == RPN_OPERATOR_PERCENT ||
        op->node.operation == RPN_OPERATOR_EQUAL)
        return;
    /* remove the head, it will be re-inserted with new operator */
    pop();
}