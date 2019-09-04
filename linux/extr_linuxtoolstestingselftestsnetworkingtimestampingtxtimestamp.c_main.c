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
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int cfg_payload_len ; 
 size_t cfg_proto ; 
 int dest_port ; 
 scalar_t__ do_ipv4 ; 
 scalar_t__ do_ipv6 ; 
 int /*<<< orphan*/  do_main (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  parse_opt (int,char**) ; 
 int /*<<< orphan*/  resolve_hostname (char*) ; 
 char** sock_names ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char **argv)
{
	if (argc == 1)
		usage(argv[0]);

	parse_opt(argc, argv);
	resolve_hostname(argv[argc - 1]);

	fprintf(stderr, "protocol:     %s\n", sock_names[cfg_proto]);
	fprintf(stderr, "payload:      %u\n", cfg_payload_len);
	fprintf(stderr, "server port:  %u\n", dest_port);
	fprintf(stderr, "\n");

	if (do_ipv4)
		do_main(PF_INET);
	if (do_ipv6)
		do_main(PF_INET6);

	return 0;
}