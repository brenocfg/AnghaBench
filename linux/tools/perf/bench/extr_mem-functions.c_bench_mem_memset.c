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
struct bench_mem_info {int /*<<< orphan*/  usage; int /*<<< orphan*/  do_gettimeofday; int /*<<< orphan*/  do_cycles; int /*<<< orphan*/  functions; } ;

/* Variables and functions */
 int bench_mem_common (int,char const**,struct bench_mem_info*) ; 
 int /*<<< orphan*/  bench_mem_memset_usage ; 
 int /*<<< orphan*/  do_memset_cycles ; 
 int /*<<< orphan*/  do_memset_gettimeofday ; 
 int /*<<< orphan*/  memset_functions ; 

int bench_mem_memset(int argc, const char **argv)
{
	struct bench_mem_info info = {
		.functions		= memset_functions,
		.do_cycles		= do_memset_cycles,
		.do_gettimeofday	= do_memset_gettimeofday,
		.usage			= bench_mem_memset_usage,
	};

	return bench_mem_common(argc, argv, &info);
}