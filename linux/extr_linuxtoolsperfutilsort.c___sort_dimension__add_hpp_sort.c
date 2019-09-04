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
struct sort_dimension {int dummy; } ;
struct perf_hpp_list {int dummy; } ;
struct hpp_sort_entry {int /*<<< orphan*/  hpp; } ;

/* Variables and functions */
 struct hpp_sort_entry* __sort_dimension__alloc_hpp (struct sort_dimension*,int) ; 
 int /*<<< orphan*/  perf_hpp_list__register_sort_field (struct perf_hpp_list*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __sort_dimension__add_hpp_sort(struct sort_dimension *sd,
					  struct perf_hpp_list *list,
					  int level)
{
	struct hpp_sort_entry *hse = __sort_dimension__alloc_hpp(sd, level);

	if (hse == NULL)
		return -1;

	perf_hpp_list__register_sort_field(list, &hse->hpp);
	return 0;
}