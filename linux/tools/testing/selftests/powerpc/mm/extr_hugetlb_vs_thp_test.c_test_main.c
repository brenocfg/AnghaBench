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
 scalar_t__ test_body () ; 

__attribute__((used)) static int test_main(void)
{
	int i;

	/* 10,000 because it's a "bunch", and completes reasonably quickly */
	for (i = 0; i < 10000; i++)
		if (test_body())
			return 1;

	return 0;
}