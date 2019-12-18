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
 scalar_t__ cfg_do_ipv4 ; 
 scalar_t__ cfg_do_ipv6 ; 
 int /*<<< orphan*/  parse_opts (int,char**) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  run_test_v4 () ; 
 int /*<<< orphan*/  run_test_v6 () ; 
 int seed ; 
 int /*<<< orphan*/  srand (int) ; 
 int time (int /*<<< orphan*/ *) ; 

int main(int argc, char **argv)
{
	parse_opts(argc, argv);
	seed = time(NULL);
	srand(seed);
	/* Print the seed to track/reproduce potential failures. */
	printf("seed = %d\n", seed);

	if (cfg_do_ipv4)
		run_test_v4();
	if (cfg_do_ipv6)
		run_test_v6();

	return 0;
}