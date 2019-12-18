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
struct TYPE_3__ {int last_te; int sorted; scalar_t__ first_te; int /*<<< orphan*/ ** tes; } ;
typedef  TYPE_1__ ParallelReadyList ;

/* Variables and functions */
 scalar_t__ pg_malloc (int) ; 

__attribute__((used)) static void
ready_list_init(ParallelReadyList *ready_list, int tocCount)
{
	ready_list->tes = (TocEntry **)
		pg_malloc(tocCount * sizeof(TocEntry *));
	ready_list->first_te = 0;
	ready_list->last_te = -1;
	ready_list->sorted = false;
}