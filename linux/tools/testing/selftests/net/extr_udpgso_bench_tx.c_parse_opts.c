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
struct udphdr {int dummy; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct iphdr {int dummy; } ;
struct ip6_hdr {int dummy; } ;

/* Variables and functions */
 int ETH_DATA_LEN ; 
 int ETH_MAX_MTU ; 
 scalar_t__ PF_INET ; 
 scalar_t__ PF_INET6 ; 
 scalar_t__ PF_UNSPEC ; 
 int /*<<< orphan*/  SOF_TIMESTAMPING_TX_HARDWARE ; 
 int cfg_alen ; 
 int cfg_audit ; 
 int cfg_cache_trash ; 
 int cfg_connected ; 
 int /*<<< orphan*/  cfg_cpu ; 
 int /*<<< orphan*/  cfg_dst_addr ; 
 scalar_t__ cfg_family ; 
 int cfg_gso_size ; 
 int cfg_msg_nr ; 
 int cfg_mss ; 
 int cfg_payload_len ; 
 int cfg_poll ; 
 int cfg_port ; 
 int cfg_runtime_ms ; 
 int cfg_segment ; 
 int cfg_sendmmsg ; 
 int cfg_tcp ; 
 int /*<<< orphan*/  cfg_tx_ts ; 
 int cfg_tx_tstamp ; 
 int cfg_verbose ; 
 int cfg_zerocopy ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  setup_sockaddr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usage (char*) ; 

__attribute__((used)) static void parse_opts(int argc, char **argv)
{
	int max_len, hdrlen;
	int c;

	while ((c = getopt(argc, argv, "46acC:D:Hl:mM:p:s:PS:tTuvz")) != -1) {
		switch (c) {
		case '4':
			if (cfg_family != PF_UNSPEC)
				error(1, 0, "Pass one of -4 or -6");
			cfg_family = PF_INET;
			cfg_alen = sizeof(struct sockaddr_in);
			break;
		case '6':
			if (cfg_family != PF_UNSPEC)
				error(1, 0, "Pass one of -4 or -6");
			cfg_family = PF_INET6;
			cfg_alen = sizeof(struct sockaddr_in6);
			break;
		case 'a':
			cfg_audit = true;
			break;
		case 'c':
			cfg_cache_trash = true;
			break;
		case 'C':
			cfg_cpu = strtol(optarg, NULL, 0);
			break;
		case 'D':
			setup_sockaddr(cfg_family, optarg, &cfg_dst_addr);
			break;
		case 'l':
			cfg_runtime_ms = strtoul(optarg, NULL, 10) * 1000;
			break;
		case 'm':
			cfg_sendmmsg = true;
			break;
		case 'M':
			cfg_msg_nr = strtoul(optarg, NULL, 10);
			break;
		case 'p':
			cfg_port = strtoul(optarg, NULL, 0);
			break;
		case 'P':
			cfg_poll = true;
			break;
		case 's':
			cfg_payload_len = strtoul(optarg, NULL, 0);
			break;
		case 'S':
			cfg_gso_size = strtoul(optarg, NULL, 0);
			cfg_segment = true;
			break;
		case 'H':
			cfg_tx_ts = SOF_TIMESTAMPING_TX_HARDWARE;
			cfg_tx_tstamp = true;
			break;
		case 't':
			cfg_tcp = true;
			break;
		case 'T':
			cfg_tx_tstamp = true;
			break;
		case 'u':
			cfg_connected = false;
			break;
		case 'v':
			cfg_verbose = true;
			break;
		case 'z':
			cfg_zerocopy = true;
			break;
		}
	}

	if (optind != argc)
		usage(argv[0]);

	if (cfg_family == PF_UNSPEC)
		error(1, 0, "must pass one of -4 or -6");
	if (cfg_tcp && !cfg_connected)
		error(1, 0, "connectionless tcp makes no sense");
	if (cfg_segment && cfg_sendmmsg)
		error(1, 0, "cannot combine segment offload and sendmmsg");
	if (cfg_tx_tstamp && !(cfg_segment || cfg_sendmmsg))
		error(1, 0, "Options -T and -H require either -S or -m option");

	if (cfg_family == PF_INET)
		hdrlen = sizeof(struct iphdr) + sizeof(struct udphdr);
	else
		hdrlen = sizeof(struct ip6_hdr) + sizeof(struct udphdr);

	cfg_mss = ETH_DATA_LEN - hdrlen;
	max_len = ETH_MAX_MTU - hdrlen;
	if (!cfg_gso_size)
		cfg_gso_size = cfg_mss;

	if (cfg_payload_len > max_len)
		error(1, 0, "payload length %u exceeds max %u",
		      cfg_payload_len, max_len);
}