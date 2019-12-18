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
typedef  int /*<<< orphan*/  LOCKTAG ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  WaitForLockersMultiple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_make1 (int /*<<< orphan*/ *) ; 

void
WaitForLockers(LOCKTAG heaplocktag, LOCKMODE lockmode, bool progress)
{
	List	   *l;

	l = list_make1(&heaplocktag);
	WaitForLockersMultiple(l, lockmode, progress);
	list_free(l);
}