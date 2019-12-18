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
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  basename (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  interval ; 
 scalar_t__ list ; 
 scalar_t__ mode ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  print_wrong_arg_exit () ; 
 int /*<<< orphan*/  progname ; 
 scalar_t__ show ; 
 scalar_t__ show_all ; 
 int /*<<< orphan*/  show_monitors_param ; 
 int wake_cpus ; 

__attribute__((used)) static void cmdline(int argc, char *argv[])
{
	int opt;
	progname = basename(argv[0]);

	while ((opt = getopt(argc, argv, "+lci:m:")) != -1) {
		switch (opt) {
		case 'l':
			if (mode)
				print_wrong_arg_exit();
			mode = list;
			break;
		case 'i':
			/* only allow -i with -m or no option */
			if (mode && mode != show)
				print_wrong_arg_exit();
			interval = atoi(optarg);
			break;
		case 'm':
			if (mode)
				print_wrong_arg_exit();
			mode = show;
			show_monitors_param = optarg;
			break;
		case 'c':
			wake_cpus = 1;
			break;
		default:
			print_wrong_arg_exit();
		}
	}
	if (!mode)
		mode = show_all;
}