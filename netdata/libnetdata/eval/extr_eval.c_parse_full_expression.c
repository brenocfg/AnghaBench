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
typedef  int /*<<< orphan*/  EVAL_NODE ;

/* Variables and functions */
 int EVAL_ERROR_MISSING_OPERAND ; 
 int /*<<< orphan*/ * parse_one_full_operand (char const**,int*) ; 
 int /*<<< orphan*/ * parse_rest_of_expression (char const**,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline EVAL_NODE *parse_full_expression(const char **string, int *error) {
    EVAL_NODE *op1 = parse_one_full_operand(string, error);
    if(!op1) {
        *error = EVAL_ERROR_MISSING_OPERAND;
        return NULL;
    }

    return parse_rest_of_expression(string, error, op1);
}