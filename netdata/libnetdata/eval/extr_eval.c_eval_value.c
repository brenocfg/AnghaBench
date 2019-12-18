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
struct TYPE_3__ {int type; int /*<<< orphan*/  variable; int /*<<< orphan*/  number; int /*<<< orphan*/  expression; } ;
typedef  TYPE_1__ EVAL_VALUE ;
typedef  int /*<<< orphan*/  EVAL_EXPRESSION ;

/* Variables and functions */
 int EVAL_ERROR_INVALID_VALUE ; 
#define  EVAL_VALUE_EXPRESSION 130 
#define  EVAL_VALUE_NUMBER 129 
#define  EVAL_VALUE_VARIABLE 128 
 int /*<<< orphan*/  eval_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  eval_variable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline calculated_number eval_value(EVAL_EXPRESSION *exp, EVAL_VALUE *v, int *error) {
    calculated_number n;

    switch(v->type) {
        case EVAL_VALUE_EXPRESSION:
            n = eval_node(exp, v->expression, error);
            break;

        case EVAL_VALUE_NUMBER:
            n = v->number;
            break;

        case EVAL_VALUE_VARIABLE:
            n = eval_variable(exp, v->variable, error);
            break;

        default:
            *error = EVAL_ERROR_INVALID_VALUE;
            n = 0;
            break;
    }

    return n;
}