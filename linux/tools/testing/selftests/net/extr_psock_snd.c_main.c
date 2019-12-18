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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  parse_opts (int,char**) ; 
 int /*<<< orphan*/  run_test () ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ system (char*) ; 

int main(int argc, char **argv)
{
	parse_opts(argc, argv);

	if (system("ip link set dev lo mtu 1500"))
		error(1, errno, "ip link set mtu");
	if (system("ip addr add dev lo 172.17.0.1/24"))
		error(1, errno, "ip addr add");

	run_test();

	fprintf(stderr, "OK\n\n");
	return 0;
}