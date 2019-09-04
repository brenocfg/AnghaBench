#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  calculated_number ;
struct TYPE_11__ {void* operator; void* precedence; } ;
typedef  TYPE_1__ EVAL_NODE ;

/* Variables and functions */
 int EVAL_ERROR_MISSING_CLOSE_SUBEXPRESSION ; 
 int EVAL_ERROR_MISSING_OPERAND ; 
 int EVAL_ERROR_OK ; 
 int EVAL_ERROR_UNKNOWN_OPERAND ; 
 int /*<<< orphan*/  EVAL_MAX_VARIABLE_NAME_LENGTH ; 
 void* EVAL_OPERATOR_ABS ; 
 void* EVAL_OPERATOR_EXPRESSION_OPEN ; 
 void* EVAL_OPERATOR_NOP ; 
 void* EVAL_OPERATOR_NOT ; 
 void* EVAL_OPERATOR_SIGN_MINUS ; 
 void* EVAL_OPERATOR_SIGN_PLUS ; 
 TYPE_1__* eval_node_alloc (int) ; 
 int /*<<< orphan*/  eval_node_free (TYPE_1__*) ; 
 int /*<<< orphan*/  eval_node_set_value_to_constant (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eval_node_set_value_to_node (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  eval_node_set_value_to_variable (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 void* eval_precedence (void*) ; 
 scalar_t__ parse_abs (char const**) ; 
 int /*<<< orphan*/  parse_close_subexpression (char const**) ; 
 scalar_t__ parse_constant (char const**,int /*<<< orphan*/ *) ; 
 TYPE_1__* parse_full_expression (char const**,int*) ; 
 scalar_t__ parse_minus (char const**) ; 
 TYPE_1__* parse_next_operand_given_its_operator (char const**,void*,int*) ; 
 scalar_t__ parse_not (char const**) ; 
 scalar_t__ parse_open_subexpression (char const**) ; 
 scalar_t__ parse_plus (char const**) ; 
 scalar_t__ parse_variable (char const**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_spaces (char const**) ; 

__attribute__((used)) static inline EVAL_NODE *parse_one_full_operand(const char **string, int *error) {
    char variable_buffer[EVAL_MAX_VARIABLE_NAME_LENGTH + 1];
    EVAL_NODE *op1 = NULL;
    calculated_number number;

    *error = EVAL_ERROR_OK;

    skip_spaces(string);
    if(!(**string)) {
        *error = EVAL_ERROR_MISSING_OPERAND;
        return NULL;
    }

    if(parse_not(string)) {
        op1 = parse_next_operand_given_its_operator(string, EVAL_OPERATOR_NOT, error);
        op1->precedence = eval_precedence(EVAL_OPERATOR_NOT);
    }
    else if(parse_plus(string)) {
        op1 = parse_next_operand_given_its_operator(string, EVAL_OPERATOR_SIGN_PLUS, error);
        op1->precedence = eval_precedence(EVAL_OPERATOR_SIGN_PLUS);
    }
    else if(parse_minus(string)) {
        op1 = parse_next_operand_given_its_operator(string, EVAL_OPERATOR_SIGN_MINUS, error);
        op1->precedence = eval_precedence(EVAL_OPERATOR_SIGN_MINUS);
    }
    else if(parse_abs(string)) {
        op1 = parse_next_operand_given_its_operator(string, EVAL_OPERATOR_ABS, error);
        op1->precedence = eval_precedence(EVAL_OPERATOR_ABS);
    }
    else if(parse_open_subexpression(string)) {
        EVAL_NODE *sub = parse_full_expression(string, error);
        if(sub) {
            op1 = eval_node_alloc(1);
            op1->operator = EVAL_OPERATOR_EXPRESSION_OPEN;
            op1->precedence = eval_precedence(EVAL_OPERATOR_EXPRESSION_OPEN);
            eval_node_set_value_to_node(op1, 0, sub);
            if(!parse_close_subexpression(string)) {
                *error = EVAL_ERROR_MISSING_CLOSE_SUBEXPRESSION;
                eval_node_free(op1);
                return NULL;
            }
        }
    }
    else if(parse_variable(string, variable_buffer, EVAL_MAX_VARIABLE_NAME_LENGTH)) {
        op1 = eval_node_alloc(1);
        op1->operator = EVAL_OPERATOR_NOP;
        eval_node_set_value_to_variable(op1, 0, variable_buffer);
    }
    else if(parse_constant(string, &number)) {
        op1 = eval_node_alloc(1);
        op1->operator = EVAL_OPERATOR_NOP;
        eval_node_set_value_to_constant(op1, 0, number);
    }
    else if(**string)
        *error = EVAL_ERROR_UNKNOWN_OPERAND;
    else
        *error = EVAL_ERROR_MISSING_OPERAND;

    return op1;
}