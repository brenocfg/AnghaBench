#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  calculated_number ;
struct TYPE_6__ {scalar_t__ parameters; int /*<<< orphan*/  (* eval ) (int /*<<< orphan*/ *,TYPE_1__*,int*) ;} ;
struct TYPE_5__ {scalar_t__ count; size_t operator; } ;
typedef  TYPE_1__ EVAL_NODE ;
typedef  int /*<<< orphan*/  EVAL_EXPRESSION ;

/* Variables and functions */
 int EVAL_ERROR_INVALID_NUMBER_OF_OPERANDS ; 
 TYPE_3__* operators ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*,int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline calculated_number eval_node(EVAL_EXPRESSION *exp, EVAL_NODE *op, int *error) {
    if(unlikely(op->count != operators[op->operator].parameters)) {
        *error = EVAL_ERROR_INVALID_NUMBER_OF_OPERANDS;
        return 0;
    }

    calculated_number n = operators[op->operator].eval(exp, op, error);

    return n;
}