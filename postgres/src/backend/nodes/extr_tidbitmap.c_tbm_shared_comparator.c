#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ blockno; } ;
typedef  TYPE_1__ PagetableEntry ;

/* Variables and functions */

__attribute__((used)) static int
tbm_shared_comparator(const void *left, const void *right, void *arg)
{
	PagetableEntry *base = (PagetableEntry *) arg;
	PagetableEntry *lpage = &base[*(int *) left];
	PagetableEntry *rpage = &base[*(int *) right];

	if (lpage->blockno < rpage->blockno)
		return -1;
	else if (lpage->blockno > rpage->blockno)
		return 1;
	return 0;
}