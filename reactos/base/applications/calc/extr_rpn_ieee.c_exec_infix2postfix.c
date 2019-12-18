#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  calc_number_t ;
struct TYPE_4__ {unsigned int operation; int /*<<< orphan*/  base; int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ calc_node_t ;
struct TYPE_5__ {unsigned int last_operator; int /*<<< orphan*/  base; scalar_t__ sci_in; } ;

/* Variables and functions */
 unsigned int RPN_OPERATOR_EQUAL ; 
 unsigned int RPN_OPERATOR_NONE ; 
 unsigned int RPN_OPERATOR_PARENT ; 
 unsigned int RPN_OPERATOR_PERCENT ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__ calc ; 
 int /*<<< orphan*/  evalStack (int /*<<< orphan*/ *) ; 
 scalar_t__ is_stack_empty () ; 
 int /*<<< orphan*/  percent_mode ; 
 int /*<<< orphan*/  push (TYPE_1__*) ; 

int exec_infix2postfix(calc_number_t *number, unsigned int func)
{
    calc_node_t tmp;

    if (is_stack_empty() && func == RPN_OPERATOR_EQUAL) {
        /* if a number has been entered with exponential */
        /* notation, I may update it with normal mode */
        if (calc.sci_in)
            return 1;
        return 0;
    }

    if (func == RPN_OPERATOR_PERCENT)
        percent_mode = TRUE;

    tmp.number = *number;
    tmp.base = calc.base;
    tmp.operation = func;

    push(&tmp);

    if (func == RPN_OPERATOR_NONE)
        return 0;

    if (func != RPN_OPERATOR_PARENT) {
        calc.last_operator = func;
        evalStack(number);
    }
    return 1;
}