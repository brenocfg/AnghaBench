#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ error; int /*<<< orphan*/  error_msg; int /*<<< orphan*/  result; scalar_t__ nodes; } ;
typedef  int /*<<< orphan*/  EVAL_NODE ;
typedef  TYPE_1__ EVAL_EXPRESSION ;

/* Variables and functions */
 scalar_t__ EVAL_ERROR_OK ; 
 scalar_t__ EVAL_ERROR_UNKNOWN_VARIABLE ; 
 scalar_t__ EVAL_ERROR_VALUE_IS_INFINITE ; 
 scalar_t__ EVAL_ERROR_VALUE_IS_NAN ; 
 int /*<<< orphan*/  NAN ; 
 int /*<<< orphan*/  buffer_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_sprintf (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_strcat (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ buffer_strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eval_node (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  expression_strerror (scalar_t__) ; 
 int isinf (int /*<<< orphan*/ ) ; 
 int isnan (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int expression_evaluate(EVAL_EXPRESSION *expression) {
    expression->error = EVAL_ERROR_OK;

    buffer_reset(expression->error_msg);
    expression->result = eval_node(expression, (EVAL_NODE *)expression->nodes, &expression->error);

    if(unlikely(isnan(expression->result))) {
        if(expression->error == EVAL_ERROR_OK)
            expression->error = EVAL_ERROR_VALUE_IS_NAN;
    }
    else if(unlikely(isinf(expression->result))) {
        if(expression->error == EVAL_ERROR_OK)
            expression->error = EVAL_ERROR_VALUE_IS_INFINITE;
    }
    else if(unlikely(expression->error == EVAL_ERROR_UNKNOWN_VARIABLE)) {
        // although there is an unknown variable
        // the expression was evaluated successfully
        expression->error = EVAL_ERROR_OK;
    }

    if(expression->error != EVAL_ERROR_OK) {
        expression->result = NAN;

        if(buffer_strlen(expression->error_msg))
            buffer_strcat(expression->error_msg, "; ");

        buffer_sprintf(expression->error_msg, "failed to evaluate expression with error %d (%s)", expression->error, expression_strerror(expression->error));
        return 0;
    }

    return 1;
}