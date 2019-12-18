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
typedef  int /*<<< orphan*/  calc_node_t ;
struct TYPE_3__ {void* next; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* stack ; 
 int /*<<< orphan*/  temp ; 

__attribute__((used)) static calc_node_t *pop(void)
{
    void *next;

    if (stack == NULL)
        return NULL;

    /* copy the node */
    temp = stack->node;
    next = stack->next;

    /* free the node */
    free(stack);
    stack = next;

    return &temp;
}