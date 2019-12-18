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
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  num_loops ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int test_harness (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_tmspr ; 

int main(int argc, char *argv[])
{
	if (argc > 1) {
		if (strcmp(argv[1], "-h") == 0) {
			printf("Syntax:\t [<num loops>]\n");
			return 0;
		} else {
			num_loops = atoi(argv[1]);
		}
	}
	return test_harness(test_tmspr, "tm_tmspr");
}