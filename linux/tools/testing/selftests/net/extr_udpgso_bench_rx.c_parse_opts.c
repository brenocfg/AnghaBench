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
struct sockaddr_in {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int cfg_alen ; 
 int /*<<< orphan*/  cfg_bind_addr ; 
 void* cfg_connect_timeout_ms ; 
 int /*<<< orphan*/  cfg_expected_gso_size ; 
 void* cfg_expected_pkt_len ; 
 void* cfg_expected_pkt_nr ; 
 int /*<<< orphan*/  cfg_family ; 
 int cfg_gro_segment ; 
 void* cfg_port ; 
 void* cfg_rcv_timeout_ms ; 
 int cfg_read_all ; 
 int cfg_tcp ; 
 int cfg_verify ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  setup_sockaddr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*) ; 

__attribute__((used)) static void parse_opts(int argc, char **argv)
{
	int c;

	/* bind to any by default */
	setup_sockaddr(PF_INET6, "::", &cfg_bind_addr);
	while ((c = getopt(argc, argv, "4b:C:Gl:n:p:rR:S:tv")) != -1) {
		switch (c) {
		case '4':
			cfg_family = PF_INET;
			cfg_alen = sizeof(struct sockaddr_in);
			setup_sockaddr(PF_INET, "0.0.0.0", &cfg_bind_addr);
			break;
		case 'b':
			setup_sockaddr(cfg_family, optarg, &cfg_bind_addr);
			break;
		case 'C':
			cfg_connect_timeout_ms = strtoul(optarg, NULL, 0);
			break;
		case 'G':
			cfg_gro_segment = true;
			break;
		case 'l':
			cfg_expected_pkt_len = strtoul(optarg, NULL, 0);
			break;
		case 'n':
			cfg_expected_pkt_nr = strtoul(optarg, NULL, 0);
			break;
		case 'p':
			cfg_port = strtoul(optarg, NULL, 0);
			break;
		case 'r':
			cfg_read_all = true;
			break;
		case 'R':
			cfg_rcv_timeout_ms = strtoul(optarg, NULL, 0);
			break;
		case 'S':
			cfg_expected_gso_size = strtol(optarg, NULL, 0);
			break;
		case 't':
			cfg_tcp = true;
			break;
		case 'v':
			cfg_verify = true;
			cfg_read_all = true;
			break;
		}
	}

	if (optind != argc)
		usage(argv[0]);

	if (cfg_tcp && cfg_verify)
		error(1, 0, "TODO: implement verify mode for tcp");
}