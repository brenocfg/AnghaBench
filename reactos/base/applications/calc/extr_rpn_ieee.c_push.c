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
struct TYPE_3__ {struct TYPE_3__* next; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ stack_node_t ;
typedef  int /*<<< orphan*/  calc_node_t ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 TYPE_1__* stack ; 

__attribute__((used)) static void push(calc_node_t *op)
{
    stack_node_t *z = (stack_node_t *)malloc(sizeof(stack_node_t));

    z->node = *op;
    z->next = stack;
    stack = z;
}