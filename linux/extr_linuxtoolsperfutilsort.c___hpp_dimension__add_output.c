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
struct perf_hpp_list {int dummy; } ;
struct perf_hpp_fmt {int dummy; } ;
struct hpp_dimension {int taken; } ;

/* Variables and functions */
 struct perf_hpp_fmt* __hpp_dimension__alloc_hpp (struct hpp_dimension*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_hpp_list__column_register (struct perf_hpp_list*,struct perf_hpp_fmt*) ; 

__attribute__((used)) static int __hpp_dimension__add_output(struct perf_hpp_list *list,
				       struct hpp_dimension *hd)
{
	struct perf_hpp_fmt *fmt;

	if (hd->taken)
		return 0;

	fmt = __hpp_dimension__alloc_hpp(hd, 0);
	if (!fmt)
		return -1;

	hd->taken = 1;
	perf_hpp_list__column_register(list, fmt);
	return 0;
}