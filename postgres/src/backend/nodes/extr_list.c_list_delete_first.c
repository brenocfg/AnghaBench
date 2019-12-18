#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  check_list_invariants (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_delete_nth_cell (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

List *
list_delete_first(List *list)
{
	check_list_invariants(list);

	if (list == NIL)
		return NIL;				/* would an error be better? */

	return list_delete_nth_cell(list, 0);
}