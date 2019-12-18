#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ifState ;
struct TYPE_5__ {TYPE_1__* head; } ;
struct TYPE_4__ {int query_len; int paren_depth; struct TYPE_4__* next; int /*<<< orphan*/  if_state; } ;
typedef  TYPE_1__ IfStackElem ;
typedef  TYPE_2__* ConditionalStack ;

/* Variables and functions */
 scalar_t__ pg_malloc (int) ; 

void
conditional_stack_push(ConditionalStack cstack, ifState new_state)
{
	IfStackElem *p = (IfStackElem *) pg_malloc(sizeof(IfStackElem));

	p->if_state = new_state;
	p->query_len = -1;
	p->paren_depth = -1;
	p->next = cstack->head;
	cstack->head = p;
}