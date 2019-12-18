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
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  dump_trace ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char** intel_pt_info_fmts ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void intel_pt_print_info(__u64 *arr, int start, int finish)
{
	int i;

	if (!dump_trace)
		return;

	for (i = start; i <= finish; i++)
		fprintf(stdout, intel_pt_info_fmts[i], arr[i]);
}