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
struct TYPE_3__ {scalar_t__ run_all; } ;

/* Variables and functions */
 scalar_t__ __bench_numa (int /*<<< orphan*/ *) ; 
 int bench_all () ; 
 int /*<<< orphan*/  bench_numa_usage ; 
 int /*<<< orphan*/  init_params (TYPE_1__*,char*,int,char const**) ; 
 int /*<<< orphan*/  numa_usage ; 
 int /*<<< orphan*/  options ; 
 TYPE_1__ p0 ; 
 int parse_options (int,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int bench_numa(int argc, const char **argv)
{
	init_params(&p0, "main,", argc, argv);
	argc = parse_options(argc, argv, options, bench_numa_usage, 0);
	if (argc)
		goto err;

	if (p0.run_all)
		return bench_all();

	if (__bench_numa(NULL))
		goto err;

	return 0;

err:
	usage_with_options(numa_usage, options);
	return -1;
}