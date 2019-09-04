#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  parameters; } ;
struct TYPE_12__ {unsigned char operator; int precedence; int count; TYPE_1__* ops; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_2__* expression; } ;
typedef  TYPE_2__ EVAL_NODE ;

/* Variables and functions */
 int EVAL_ERROR_IF_THEN_ELSE_MISSING_ELSE ; 
 int EVAL_ERROR_MISSING_OPERATOR ; 
 unsigned char EVAL_OPERATOR_IF_THEN_ELSE ; 
 unsigned char EVAL_OPERATOR_NOP ; 
 scalar_t__ EVAL_VALUE_EXPRESSION ; 
 TYPE_2__* eval_node_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eval_node_free (TYPE_2__*) ; 
 int /*<<< orphan*/  eval_node_set_value_to_node (TYPE_2__*,int,TYPE_2__*) ; 
 TYPE_6__* operators ; 
 TYPE_2__* parse_one_full_operand (char const**,int*) ; 
 unsigned char parse_operator (char const**,int*) ; 
 int /*<<< orphan*/  skip_spaces (char const**) ; 

__attribute__((used)) static inline EVAL_NODE *parse_rest_of_expression(const char **string, int *error, EVAL_NODE *op1) {
    EVAL_NODE *op2 = NULL;
    unsigned char operator;
    int precedence;

    operator = parse_operator(string, &precedence);
    skip_spaces(string);

    if(operator != EVAL_OPERATOR_NOP) {
        op2 = parse_one_full_operand(string, error);
        if(!op2) {
            // error is already reported
            eval_node_free(op1);
            return NULL;
        }

        EVAL_NODE *op = eval_node_alloc(operators[operator].parameters);
        op->operator = operator;
        op->precedence = precedence;

        if(operator == EVAL_OPERATOR_IF_THEN_ELSE && op->count == 3) {
            skip_spaces(string);

            if(**string != ':') {
                eval_node_free(op);
                eval_node_free(op1);
                eval_node_free(op2);
                *error = EVAL_ERROR_IF_THEN_ELSE_MISSING_ELSE;
                return NULL;
            }
            (*string)++;

            skip_spaces(string);

            EVAL_NODE *op3 = parse_one_full_operand(string, error);
            if(!op3) {
                eval_node_free(op);
                eval_node_free(op1);
                eval_node_free(op2);
                // error is already reported
                return NULL;
            }

            eval_node_set_value_to_node(op, 2, op3);
        }

        eval_node_set_value_to_node(op, 1, op2);

        // precedence processing
        // if this operator has a higher precedence compared to its next
        // put the next operator on top of us (top = evaluated later)
        // function recursion does the rest...
        if(op->precedence > op1->precedence && op1->count == 2 && op1->operator != '(' && op1->ops[1].type == EVAL_VALUE_EXPRESSION) {
            eval_node_set_value_to_node(op, 0, op1->ops[1].expression);
            op1->ops[1].expression = op;
            op = op1;
        }
        else
            eval_node_set_value_to_node(op, 0, op1);

        return parse_rest_of_expression(string, error, op);
    }
    else if(**string == ')') {
        ;
    }
    else if(**string) {
        eval_node_free(op1);
        op1 = NULL;
        *error = EVAL_ERROR_MISSING_OPERATOR;
    }

    return op1;
}