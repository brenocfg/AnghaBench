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
 int test_harness (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_wild_bctr ; 

int main(void)
{
	return test_harness(test_wild_bctr, "wild_bctr");
}