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
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  finish ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  map_fd ; 
 int /*<<< orphan*/  maps_create () ; 
 int /*<<< orphan*/  print_table () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  prog_attach_iptables (char*) ; 
 int /*<<< orphan*/  prog_fd ; 
 int /*<<< orphan*/  prog_load () ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  test_finish ; 
 int /*<<< orphan*/  udp_client () ; 
 int usage () ; 

int main(int argc, char *argv[])
{
	int opt;
	bool cfg_test_traffic = false;
	bool cfg_test_cookie = false;

	if (argc != 3)
		return usage();
	while ((opt = getopt(argc, argv, "ts")) != -1) {
		switch (opt) {
		case 't':
			cfg_test_traffic = true;
			break;
		case 's':
			cfg_test_cookie = true;
			break;

		default:
			printf("unknown option %c\n", opt);
			usage();
			return -1;
		}
	}
	maps_create();
	prog_load();
	prog_attach_iptables(argv[2]);
	if (cfg_test_traffic) {
		if (signal(SIGINT, finish) == SIG_ERR)
			error(1, errno, "register SIGINT handler failed");
		if (signal(SIGTERM, finish) == SIG_ERR)
			error(1, errno, "register SIGTERM handler failed");
		while (!test_finish) {
			print_table();
			printf("\n");
			sleep(1);
		};
	} else if (cfg_test_cookie) {
		udp_client();
	}
	close(prog_fd);
	close(map_fd);
	return 0;
}