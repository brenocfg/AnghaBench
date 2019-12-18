#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned char operator; } ;
typedef  TYPE_1__ EVAL_NODE ;

/* Variables and functions */
 TYPE_1__* eval_node_alloc (int) ; 
 int /*<<< orphan*/  eval_node_set_value_to_node (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* parse_one_full_operand (char const**,int*) ; 

__attribute__((used)) static inline EVAL_NODE *parse_next_operand_given_its_operator(const char **string, unsigned char operator_type, int *error) {
    EVAL_NODE *sub = parse_one_full_operand(string, error);
    if(!sub) return NULL;

    EVAL_NODE *op = eval_node_alloc(1);
    op->operator = operator_type;
    eval_node_set_value_to_node(op, 0, sub);
    return op;
}