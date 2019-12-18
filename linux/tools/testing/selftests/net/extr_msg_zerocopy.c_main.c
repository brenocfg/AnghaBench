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
 int /*<<< orphan*/  IPPROTO_EGP ; 
 int /*<<< orphan*/  IPPROTO_RAW ; 
 int /*<<< orphan*/  PF_PACKET ; 
 int /*<<< orphan*/  PF_RDS ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  SOCK_SEQPACKET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  cfg_family ; 
 int /*<<< orphan*/  do_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  parse_opts (int,char**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int main(int argc, char **argv)
{
	const char *cfg_test;

	parse_opts(argc, argv);

	cfg_test = argv[argc - 1];

	if (!strcmp(cfg_test, "packet"))
		do_test(PF_PACKET, SOCK_RAW, 0);
	else if (!strcmp(cfg_test, "packet_dgram"))
		do_test(PF_PACKET, SOCK_DGRAM, 0);
	else if (!strcmp(cfg_test, "raw"))
		do_test(cfg_family, SOCK_RAW, IPPROTO_EGP);
	else if (!strcmp(cfg_test, "raw_hdrincl"))
		do_test(cfg_family, SOCK_RAW, IPPROTO_RAW);
	else if (!strcmp(cfg_test, "tcp"))
		do_test(cfg_family, SOCK_STREAM, 0);
	else if (!strcmp(cfg_test, "udp"))
		do_test(cfg_family, SOCK_DGRAM, 0);
	else if (!strcmp(cfg_test, "rds"))
		do_test(PF_RDS, SOCK_SEQPACKET, 0);
	else
		error(1, 0, "unknown cfg_test %s", cfg_test);

	return 0;
}