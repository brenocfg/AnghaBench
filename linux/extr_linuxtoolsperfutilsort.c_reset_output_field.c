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
struct TYPE_3__ {scalar_t__ dso; scalar_t__ sym; scalar_t__ parent; scalar_t__ need_collapse; } ;

/* Variables and functions */
 int /*<<< orphan*/ * field_order ; 
 int /*<<< orphan*/  perf_hpp__reset_output_field (TYPE_1__*) ; 
 TYPE_1__ perf_hpp_list ; 
 int /*<<< orphan*/  reset_dimensions () ; 
 int /*<<< orphan*/ * sort_order ; 

void reset_output_field(void)
{
	perf_hpp_list.need_collapse = 0;
	perf_hpp_list.parent = 0;
	perf_hpp_list.sym = 0;
	perf_hpp_list.dso = 0;

	field_order = NULL;
	sort_order = NULL;

	reset_dimensions();
	perf_hpp__reset_output_field(&perf_hpp_list);
}