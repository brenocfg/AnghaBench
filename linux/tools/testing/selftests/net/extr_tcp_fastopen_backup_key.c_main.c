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
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  O_RDWR ; 
 char* PROC_FASTOPEN_KEY ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 scalar_t__ do_ipv6 ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_opts (int,char**) ; 
 scalar_t__ proc_fd ; 
 int /*<<< orphan*/  run_one_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int main(int argc, char **argv)
{
	parse_opts(argc, argv);
	proc_fd = open(PROC_FASTOPEN_KEY, O_RDWR);
	if (proc_fd < 0)
		error(1, errno, "Unable to open %s", PROC_FASTOPEN_KEY);
	srand(time(NULL));
	if (do_ipv6)
		run_one_test(AF_INET6);
	else
		run_one_test(AF_INET);
	close(proc_fd);
	fprintf(stderr, "PASS\n");
	return 0;
}