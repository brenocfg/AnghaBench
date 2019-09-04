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
struct TYPE_4__ {int count; int /*<<< orphan*/ * ops; } ;
typedef  TYPE_1__ EVAL_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  eval_value_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freez (TYPE_1__*) ; 

__attribute__((used)) static inline void eval_node_free(EVAL_NODE *op) {
    if(op->count) {
        int i;
        for(i = op->count - 1; i >= 0 ;i--)
            eval_value_free(&op->ops[i]);
    }

    freez(op);
}