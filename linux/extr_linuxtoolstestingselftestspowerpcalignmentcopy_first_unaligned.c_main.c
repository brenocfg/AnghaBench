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
 int /*<<< orphan*/  test_copy_first_unaligned ; 
 int test_harness (int /*<<< orphan*/ ,char*) ; 

int main(int argc, char *argv[])
{
	return test_harness(test_copy_first_unaligned, "test_copy_first_unaligned");
}