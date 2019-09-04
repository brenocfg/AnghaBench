#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  calc_number_t ;
struct TYPE_7__ {scalar_t__ operation; int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ calc_node_t ;
struct TYPE_8__ {scalar_t__ is_nan; } ;

/* Variables and functions */
 scalar_t__ RPN_OPERATOR_PARENT ; 
 TYPE_6__ calc ; 
 int /*<<< orphan*/  flush_postfix () ; 
 int /*<<< orphan*/  is_stack_empty () ; 
 TYPE_1__* pop () ; 
 int /*<<< orphan*/  rpn_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpn_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpn_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_operator (TYPE_1__*,TYPE_1__*,TYPE_1__*,scalar_t__) ; 

void exec_closeparent(calc_number_t *number)
{
    calc_node_t *op, ip;

    rpn_alloc(&ip.number);
    rpn_copy(&ip.number, number);
    while (!is_stack_empty()) {
        op = pop();

        if (op->operation == RPN_OPERATOR_PARENT)
            break;

        run_operator(&ip, op, &ip, op->operation);
        if (calc.is_nan) {
            flush_postfix();
            return;
        }
    }
    rpn_copy(number, &ip.number);
    rpn_free(&ip.number);
}