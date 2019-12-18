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
typedef  int calculated_number ;
typedef  int /*<<< orphan*/  EVAL_NODE ;
typedef  int /*<<< orphan*/  EVAL_EXPRESSION ;

/* Variables and functions */
 int /*<<< orphan*/  eval_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

calculated_number eval_not_equal(EVAL_EXPRESSION *exp, EVAL_NODE *op, int *error) {
    return !eval_equal(exp, op, error);
}