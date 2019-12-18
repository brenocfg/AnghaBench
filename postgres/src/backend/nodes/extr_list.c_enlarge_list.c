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
struct TYPE_4__ {int max_length; int length; int /*<<< orphan*/ * elements; int /*<<< orphan*/ * initial_elements; } ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  TYPE_1__ List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GetMemoryChunkContext (TYPE_1__*) ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_NOACCESS (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 scalar_t__ repalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wipe_mem (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
enlarge_list(List *list, int min_size)
{
	int			new_max_len;

	Assert(min_size > list->max_length);	/* else we shouldn't be here */

#ifndef DEBUG_LIST_MEMORY_USAGE

	/*
	 * As above, we prefer power-of-two total allocations; but here we need
	 * not account for list header overhead.  The existing max length might
	 * not be a power of 2, so don't rely on that.
	 */
	new_max_len = 16;			/* semi-arbitrary small power of 2 */
	while (new_max_len < min_size)
		new_max_len *= 2;
#else
	/* As above, don't allocate anything extra */
	new_max_len = min_size;
#endif

	if (list->elements == list->initial_elements)
	{
		/*
		 * Replace original in-line allocation with a separate palloc block.
		 * Ensure it is in the same memory context as the List header.  (The
		 * previous List implementation did not offer any guarantees about
		 * keeping all list cells in the same context, but it seems reasonable
		 * to create such a guarantee now.)
		 */
		list->elements = (ListCell *)
			MemoryContextAlloc(GetMemoryChunkContext(list),
							   new_max_len * sizeof(ListCell));
		memcpy(list->elements, list->initial_elements,
			   list->length * sizeof(ListCell));

		/*
		 * We must not move the list header, so it's unsafe to try to reclaim
		 * the initial_elements[] space via repalloc.  In debugging builds,
		 * however, we can clear that space and/or mark it inaccessible.
		 * (wipe_mem includes VALGRIND_MAKE_MEM_NOACCESS.)
		 */
#ifdef CLOBBER_FREED_MEMORY
		wipe_mem(list->initial_elements,
				 list->max_length * sizeof(ListCell));
#else
		VALGRIND_MAKE_MEM_NOACCESS(list->initial_elements,
								   list->max_length * sizeof(ListCell));
#endif
	}
	else
	{
#ifndef DEBUG_LIST_MEMORY_USAGE
		/* Normally, let repalloc deal with enlargement */
		list->elements = (ListCell *) repalloc(list->elements,
											   new_max_len * sizeof(ListCell));
#else
		/*
		 * repalloc() might enlarge the space in-place, which we don't want
		 * for debugging purposes, so forcibly move the data somewhere else.
		 */
		ListCell   *newelements;

		newelements = (ListCell *)
			MemoryContextAlloc(GetMemoryChunkContext(list),
							   new_max_len * sizeof(ListCell));
		memcpy(newelements, list->elements,
			   list->length * sizeof(ListCell));
		pfree(list->elements);
		list->elements = newelements;
#endif
	}

	list->max_length = new_max_len;
}