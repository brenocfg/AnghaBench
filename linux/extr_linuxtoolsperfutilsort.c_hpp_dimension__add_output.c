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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int PERF_HPP__MAX_INDEX ; 
 int __hpp_dimension__add_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hpp_sort_dimensions ; 
 int /*<<< orphan*/  perf_hpp_list ; 

int hpp_dimension__add_output(unsigned col)
{
	BUG_ON(col >= PERF_HPP__MAX_INDEX);
	return __hpp_dimension__add_output(&perf_hpp_list, &hpp_sort_dimensions[col]);
}