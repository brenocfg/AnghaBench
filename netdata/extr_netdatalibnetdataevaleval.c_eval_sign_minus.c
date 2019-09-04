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
typedef  int /*<<< orphan*/  calculated_number ;
struct TYPE_3__ {int /*<<< orphan*/ * ops; } ;
typedef  TYPE_1__ EVAL_NODE ;
typedef  int /*<<< orphan*/  EVAL_EXPRESSION ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITY ; 
 int /*<<< orphan*/  NAN ; 
 int /*<<< orphan*/  eval_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ isinf (int /*<<< orphan*/ ) ; 
 scalar_t__ isnan (int /*<<< orphan*/ ) ; 

calculated_number eval_sign_minus(EVAL_EXPRESSION *exp, EVAL_NODE *op, int *error) {
    calculated_number n1 = eval_value(exp, &op->ops[0], error);
    if(isnan(n1)) return NAN;
    if(isinf(n1)) return INFINITY;
    return -n1;
}