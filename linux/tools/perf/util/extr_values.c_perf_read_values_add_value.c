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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct perf_read_values {int /*<<< orphan*/ ** value; } ;

/* Variables and functions */
 int perf_read_values__findnew_counter (struct perf_read_values*,scalar_t__,char const*) ; 
 int perf_read_values__findnew_thread (struct perf_read_values*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int perf_read_values_add_value(struct perf_read_values *values,
				u32 pid, u32 tid,
				u64 rawid, const char *name, u64 value)
{
	int tindex, cindex;

	tindex = perf_read_values__findnew_thread(values, pid, tid);
	if (tindex < 0)
		return tindex;
	cindex = perf_read_values__findnew_counter(values, rawid, name);
	if (cindex < 0)
		return cindex;

	values->value[tindex][cindex] += value;
	return 0;
}