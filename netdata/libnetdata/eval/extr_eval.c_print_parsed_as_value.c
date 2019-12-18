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
struct TYPE_3__ {int type; int /*<<< orphan*/  variable; int /*<<< orphan*/  number; int /*<<< orphan*/  expression; } ;
typedef  TYPE_1__ EVAL_VALUE ;
typedef  int /*<<< orphan*/  BUFFER ;

/* Variables and functions */
 int EVAL_ERROR_INVALID_VALUE ; 
#define  EVAL_VALUE_EXPRESSION 130 
#define  EVAL_VALUE_NUMBER 129 
#define  EVAL_VALUE_VARIABLE 128 
 int /*<<< orphan*/  print_parsed_as_constant (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_parsed_as_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  print_parsed_as_variable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline void print_parsed_as_value(BUFFER *out, EVAL_VALUE *v, int *error) {
    switch(v->type) {
        case EVAL_VALUE_EXPRESSION:
            print_parsed_as_node(out, v->expression, error);
            break;

        case EVAL_VALUE_NUMBER:
            print_parsed_as_constant(out, v->number);
            break;

        case EVAL_VALUE_VARIABLE:
            print_parsed_as_variable(out, v->variable, error);
            break;

        default:
            *error = EVAL_ERROR_INVALID_VALUE;
            break;
    }
}