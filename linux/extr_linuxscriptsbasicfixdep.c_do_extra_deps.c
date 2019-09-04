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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_dep (char*,int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int strlen (char*) ; 

__attribute__((used)) static void do_extra_deps(void)
{
	char buf[80];

	while (fgets(buf, sizeof(buf), stdin)) {
		int len = strlen(buf);

		if (len < 2 || buf[len - 1] != '\n') {
			fprintf(stderr, "fixdep: bad data on stdin\n");
			exit(1);
		}
		print_dep(buf, len - 1, "include/ksym");
	}
}