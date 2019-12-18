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
struct perf_tool {int dummy; } ;
struct mmap {int dummy; } ;
struct auxtrace_record {int dummy; } ;
typedef  int /*<<< orphan*/  process_auxtrace_t ;

/* Variables and functions */
 int __auxtrace_mmap__read (struct mmap*,struct auxtrace_record*,struct perf_tool*,int /*<<< orphan*/ ,int,size_t) ; 

int auxtrace_mmap__read_snapshot(struct mmap *map,
				 struct auxtrace_record *itr,
				 struct perf_tool *tool, process_auxtrace_t fn,
				 size_t snapshot_size)
{
	return __auxtrace_mmap__read(map, itr, tool, fn, true, snapshot_size);
}