#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int count; TYPE_1__* ops; } ;
struct TYPE_5__ {TYPE_2__* expression; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ EVAL_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  EVAL_VALUE_EXPRESSION ; 
 int /*<<< orphan*/  fatal (char*,int,int) ; 

__attribute__((used)) static inline void eval_node_set_value_to_node(EVAL_NODE *op, int pos, EVAL_NODE *value) {
    if(pos >= op->count)
        fatal("Invalid request to set position %d of OPERAND that has only %d values", pos + 1, op->count + 1);

    op->ops[pos].type = EVAL_VALUE_EXPRESSION;
    op->ops[pos].expression = value;
}