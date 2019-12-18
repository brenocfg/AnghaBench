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
struct sort_dimension {int taken; TYPE_1__* entry; } ;
struct perf_hpp_list {int need_collapse; } ;
struct TYPE_2__ {scalar_t__ se_collapse; } ;

/* Variables and functions */
 scalar_t__ __sort_dimension__add_hpp_sort (struct sort_dimension*,struct perf_hpp_list*,int) ; 

__attribute__((used)) static int __sort_dimension__add(struct sort_dimension *sd,
				 struct perf_hpp_list *list,
				 int level)
{
	if (sd->taken)
		return 0;

	if (__sort_dimension__add_hpp_sort(sd, list, level) < 0)
		return -1;

	if (sd->entry->se_collapse)
		list->need_collapse = 1;

	sd->taken = 1;

	return 0;
}