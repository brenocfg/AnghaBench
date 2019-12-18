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
 int /*<<< orphan*/  printf (char*,unsigned long,unsigned long,float) ; 
 scalar_t__ test_method1 () ; 
 scalar_t__ test_netdata_internal () ; 

int main(int argc, char **argv)
{
	(void)argc; (void)argv;

	int i, max = 1000000;

	unsigned long c1 = 0;
	test_netdata_internal();
	for(i = 0; i < max ; i++)
		c1 += test_netdata_internal();

	unsigned long c2 = 0;
	test_method1();
	for(i = 0; i < max ; i++)
		c2 += test_method1();

	printf("netdata internal: completed in %lu cycles, %lu cycles per read, %0.2f %%.\n", c1, c1 / max, (float)c1 * 100.0 / (float)c1);
	printf("method1         : completed in %lu cycles, %lu cycles per read, %0.2f %%.\n", c2, c2 / max, (float)c2 * 100.0 / (float)c1);

	return 0;
}