#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int (* qsort_comparator ) (void const*,void const*) ;
typedef  scalar_t__ list_sort_comparator ;
struct TYPE_5__ {int /*<<< orphan*/  elements; } ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  TYPE_1__ List ;

/* Variables and functions */
 int /*<<< orphan*/  check_list_invariants (TYPE_1__*) ; 
 int list_length (TYPE_1__*) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int,int,int (*) (void const*,void const*)) ; 

void
list_sort(List *list, list_sort_comparator cmp)
{
	typedef int (*qsort_comparator) (const void *a, const void *b);
	int			len;

	check_list_invariants(list);

	/* Nothing to do if there's less than two elements */
	len = list_length(list);
	if (len > 1)
		qsort(list->elements, len, sizeof(ListCell), (qsort_comparator) cmp);
}