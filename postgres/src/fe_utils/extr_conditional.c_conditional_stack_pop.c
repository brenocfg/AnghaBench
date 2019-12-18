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
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ IfStackElem ;
typedef  TYPE_2__* ConditionalStack ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

bool
conditional_stack_pop(ConditionalStack cstack)
{
	IfStackElem *p = cstack->head;

	if (!p)
		return false;
	cstack->head = cstack->head->next;
	free(p);
	return true;
}