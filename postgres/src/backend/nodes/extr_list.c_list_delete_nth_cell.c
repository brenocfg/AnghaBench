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
struct TYPE_8__ {int length; int max_length; int /*<<< orphan*/ * elements; int /*<<< orphan*/ * initial_elements; } ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  TYPE_1__ List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GetMemoryChunkContext (TYPE_1__*) ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* NIL ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_NOACCESS (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  check_list_invariants (TYPE_1__*) ; 
 int /*<<< orphan*/  list_free (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wipe_mem (int /*<<< orphan*/ *,int) ; 

List *
list_delete_nth_cell(List *list, int n)
{
	check_list_invariants(list);

	Assert(n >= 0 && n < list->length);

	/*
	 * If we're about to delete the last node from the list, free the whole
	 * list instead and return NIL, which is the only valid representation of
	 * a zero-length list.
	 */
	if (list->length == 1)
	{
		list_free(list);
		return NIL;
	}

	/*
	 * Otherwise, we normally just collapse out the removed element.  But for
	 * debugging purposes, move the whole list contents someplace else.
	 *
	 * (Note that we *must* keep the contents in the same memory context.)
	 */
#ifndef DEBUG_LIST_MEMORY_USAGE
	memmove(&list->elements[n], &list->elements[n + 1],
			(list->length - 1 - n) * sizeof(ListCell));
	list->length--;
#else
	{
		ListCell   *newelems;
		int			newmaxlen = list->length - 1;

		newelems = (ListCell *)
			MemoryContextAlloc(GetMemoryChunkContext(list),
							   newmaxlen * sizeof(ListCell));
		memcpy(newelems, list->elements, n * sizeof(ListCell));
		memcpy(&newelems[n], &list->elements[n + 1],
			   (list->length - 1 - n) * sizeof(ListCell));
		if (list->elements != list->initial_elements)
			pfree(list->elements);
		else
		{
			/*
			 * As in enlarge_list(), clear the initial_elements[] space and/or
			 * mark it inaccessible.
			 */
#ifdef CLOBBER_FREED_MEMORY
			wipe_mem(list->initial_elements,
					 list->max_length * sizeof(ListCell));
#else
			VALGRIND_MAKE_MEM_NOACCESS(list->initial_elements,
									   list->max_length * sizeof(ListCell));
#endif
		}
		list->elements = newelems;
		list->max_length = newmaxlen;
		list->length--;
		check_list_invariants(list);
	}
#endif

	return list;
}