#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int calculated_number ;
struct TYPE_3__ {int /*<<< orphan*/ * ops; } ;
typedef  TYPE_1__ EVAL_NODE ;
typedef  int /*<<< orphan*/  EVAL_EXPRESSION ;

/* Variables and functions */
 int calculated_number_equal (int,int) ; 
 int eval_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ isinf (int) ; 
 scalar_t__ isnan (int) ; 

calculated_number eval_equal(EVAL_EXPRESSION *exp, EVAL_NODE *op, int *error) {
    calculated_number n1 = eval_value(exp, &op->ops[0], error);
    calculated_number n2 = eval_value(exp, &op->ops[1], error);
    if(isnan(n1) && isnan(n2)) return 1;
    if(isinf(n1) && isinf(n2)) return 1;
    if(isnan(n1) || isnan(n2)) return 0;
    if(isinf(n1) || isinf(n2)) return 0;
    return calculated_number_equal(n1, n2);
}