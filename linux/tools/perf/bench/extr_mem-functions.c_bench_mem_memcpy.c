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
struct bench_mem_info {int alloc_src; int /*<<< orphan*/  usage; int /*<<< orphan*/  do_gettimeofday; int /*<<< orphan*/  do_cycles; int /*<<< orphan*/  functions; } ;

/* Variables and functions */
 int bench_mem_common (int,char const**,struct bench_mem_info*) ; 
 int /*<<< orphan*/  bench_mem_memcpy_usage ; 
 int /*<<< orphan*/  do_memcpy_cycles ; 
 int /*<<< orphan*/  do_memcpy_gettimeofday ; 
 int /*<<< orphan*/  memcpy_functions ; 

int bench_mem_memcpy(int argc, const char **argv)
{
	struct bench_mem_info info = {
		.functions		= memcpy_functions,
		.do_cycles		= do_memcpy_cycles,
		.do_gettimeofday	= do_memcpy_gettimeofday,
		.usage			= bench_mem_memcpy_usage,
		.alloc_src              = true,
	};

	return bench_mem_common(argc, argv, &info);
}