#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int length; } ;
typedef  TYPE_1__ List ;

/* Variables and functions */
 TYPE_1__* NIL ; 
 int list_length (TYPE_1__*) ; 

List *
list_truncate(List *list, int new_size)
{
	if (new_size <= 0)
		return NIL;				/* truncate to zero length */

	/* If asked to effectively extend the list, do nothing */
	if (new_size < list_length(list))
		list->length = new_size;

	/*
	 * Note: unlike the individual-list-cell deletion functions, we don't move
	 * the list cells to new storage, even in DEBUG_LIST_MEMORY_USAGE mode.
	 * This is because none of them can move in this operation, so just like
	 * in the old cons-cell-based implementation, this function doesn't
	 * invalidate any pointers to cells of the list.  This is also the reason
	 * for not wiping the memory of the deleted cells: the old code didn't
	 * free them either.  Perhaps later we'll tighten this up.
	 */

	return list;
}