#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int length; struct TYPE_8__* elements; struct TYPE_8__* initial_elements; } ;
typedef  TYPE_1__ List ;

/* Variables and functions */
 TYPE_1__* NIL ; 
 int /*<<< orphan*/  check_list_invariants (TYPE_1__*) ; 
 TYPE_1__* lfirst (TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

__attribute__((used)) static void
list_free_private(List *list, bool deep)
{
	if (list == NIL)
		return;					/* nothing to do */

	check_list_invariants(list);

	if (deep)
	{
		for (int i = 0; i < list->length; i++)
			pfree(lfirst(&list->elements[i]));
	}
	if (list->elements != list->initial_elements)
		pfree(list->elements);
	pfree(list);
}