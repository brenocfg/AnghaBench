#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TocEntry ;
struct TYPE_3__ {int sorted; int last_te; int first_te; int tes; } ;
typedef  TYPE_1__ ParallelReadyList ;

/* Variables and functions */
 int /*<<< orphan*/  TocEntrySizeCompare ; 
 int /*<<< orphan*/  qsort (int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ready_list_sort(ParallelReadyList *ready_list)
{
	if (!ready_list->sorted)
	{
		int			n = ready_list->last_te - ready_list->first_te + 1;

		if (n > 1)
			qsort(ready_list->tes + ready_list->first_te, n,
				  sizeof(TocEntry *),
				  TocEntrySizeCompare);
		ready_list->sorted = true;
	}
}