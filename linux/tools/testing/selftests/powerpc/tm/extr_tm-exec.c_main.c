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
 int after_exec () ; 
 char* path ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  test_exec ; 
 int test_harness (int /*<<< orphan*/ ,char*) ; 

int main(int argc, char *argv[])
{
	path = argv[0];

	if (argc > 1 && strcmp(argv[1], "--child") == 0)
		return after_exec();

	return test_harness(test_exec, "tm_exec");
}