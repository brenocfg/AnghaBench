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
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsPointerList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_free_private (int /*<<< orphan*/ *,int) ; 

void
list_free_deep(List *list)
{
	/*
	 * A "deep" free operation only makes sense on a list of pointers.
	 */
	Assert(IsPointerList(list));
	list_free_private(list, true);
}