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
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  run_bench_numa (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int system (char*) ; 
 int /*<<< orphan*/ ** tests ; 

__attribute__((used)) static int bench_all(void)
{
	int nr = ARRAY_SIZE(tests);
	int ret;
	int i;

	ret = system("echo ' #'; echo ' # Running test on: '$(uname -a); echo ' #'");
	BUG_ON(ret < 0);

	for (i = 0; i < nr; i++) {
		run_bench_numa(tests[i][0], tests[i] + 1);
	}

	printf("\n");

	return 0;
}