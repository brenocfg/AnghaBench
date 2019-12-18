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
 unsigned long atoi (char*) ; 
 int /*<<< orphan*/  do_exec (unsigned long) ; 
 int /*<<< orphan*/  dscr_inherit_exec ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* prog ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int test_harness (int /*<<< orphan*/ ,char*) ; 

int main(int argc, char *argv[])
{
	if (argc == 3 && !strcmp(argv[1], "exec")) {
		unsigned long parent_dscr;

		parent_dscr = atoi(argv[2]);
		do_exec(parent_dscr);
	} else if (argc != 1) {
		fprintf(stderr, "Usage: %s\n", argv[0]);
		exit(1);
	}

	prog = argv[0];
	return test_harness(dscr_inherit_exec, "dscr_inherit_exec_test");
}