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
struct perf_hpp_list {int /*<<< orphan*/  sorts; } ;
struct perf_hpp_fmt {int /*<<< orphan*/  sort_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void perf_hpp_list__prepend_sort_field(struct perf_hpp_list *list,
				       struct perf_hpp_fmt *format)
{
	list_add(&format->sort_list, &list->sorts);
}