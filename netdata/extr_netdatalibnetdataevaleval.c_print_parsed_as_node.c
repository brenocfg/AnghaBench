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
struct TYPE_5__ {int parameters; scalar_t__ isfunction; scalar_t__ print_as; } ;
struct TYPE_4__ {int count; size_t operator; int /*<<< orphan*/ * ops; } ;
typedef  TYPE_1__ EVAL_NODE ;
typedef  int /*<<< orphan*/  BUFFER ;

/* Variables and functions */
 int EVAL_ERROR_INVALID_NUMBER_OF_OPERANDS ; 
 size_t EVAL_OPERATOR_IF_THEN_ELSE ; 
 int /*<<< orphan*/  buffer_sprintf (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  buffer_strcat (int /*<<< orphan*/ *,char*) ; 
 TYPE_3__* operators ; 
 int /*<<< orphan*/  print_parsed_as_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void print_parsed_as_node(BUFFER *out, EVAL_NODE *op, int *error) {
    if(unlikely(op->count != operators[op->operator].parameters)) {
        *error = EVAL_ERROR_INVALID_NUMBER_OF_OPERANDS;
        return;
    }

    if(operators[op->operator].parameters == 1) {

        if(operators[op->operator].print_as)
            buffer_sprintf(out, "%s", operators[op->operator].print_as);

        //if(op->operator == EVAL_OPERATOR_EXPRESSION_OPEN)
        //    buffer_strcat(out, "(");

        print_parsed_as_value(out, &op->ops[0], error);

        //if(op->operator == EVAL_OPERATOR_EXPRESSION_OPEN)
        //    buffer_strcat(out, ")");
    }

    else if(operators[op->operator].parameters == 2) {
        buffer_strcat(out, "(");
        print_parsed_as_value(out, &op->ops[0], error);

        if(operators[op->operator].print_as)
            buffer_sprintf(out, " %s ", operators[op->operator].print_as);

        print_parsed_as_value(out, &op->ops[1], error);
        buffer_strcat(out, ")");
    }
    else if(op->operator == EVAL_OPERATOR_IF_THEN_ELSE && operators[op->operator].parameters == 3) {
        buffer_strcat(out, "(");
        print_parsed_as_value(out, &op->ops[0], error);

        if(operators[op->operator].print_as)
            buffer_sprintf(out, " %s ", operators[op->operator].print_as);

        print_parsed_as_value(out, &op->ops[1], error);
        buffer_strcat(out, " : ");
        print_parsed_as_value(out, &op->ops[2], error);
        buffer_strcat(out, ")");
    }

    if(operators[op->operator].isfunction)
        buffer_strcat(out, ")");
}