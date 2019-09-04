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
 scalar_t__ __bench_numa (char const*) ; 
 int /*<<< orphan*/  bench_numa_usage ; 
 int command_size (char const**) ; 
 int /*<<< orphan*/  init_params (int /*<<< orphan*/ *,char const*,int,char const**) ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  p0 ; 
 int parse_options (int,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run_bench_numa(const char *name, const char **argv)
{
	int argc = command_size(argv);

	init_params(&p0, name, argc, argv);
	argc = parse_options(argc, argv, options, bench_numa_usage, 0);
	if (argc)
		goto err;

	if (__bench_numa(name))
		goto err;

	return 0;

err:
	return -1;
}