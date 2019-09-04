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
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  parse_dep_file (void*,char const*,int) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 
 void* read_file (char const*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char *argv[])
{
	const char *depfile, *target, *cmdline;
	int insert_extra_deps = 0;
	void *buf;

	if (argc == 5 && !strcmp(argv[1], "-e")) {
		insert_extra_deps = 1;
		argv++;
	} else if (argc != 4)
		usage();

	depfile = argv[1];
	target = argv[2];
	cmdline = argv[3];

	printf("cmd_%s := %s\n\n", target, cmdline);

	buf = read_file(depfile);
	parse_dep_file(buf, target, insert_extra_deps);
	free(buf);

	return 0;
}