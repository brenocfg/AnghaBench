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
struct TYPE_6__ {TYPE_1__* head; } ;
struct TYPE_5__ {int paren_depth; } ;
typedef  TYPE_2__* ConditionalStack ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  conditional_stack_empty (TYPE_2__*) ; 

void
conditional_stack_set_paren_depth(ConditionalStack cstack, int depth)
{
	Assert(!conditional_stack_empty(cstack));
	cstack->head->paren_depth = depth;
}