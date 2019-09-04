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
 int /*<<< orphan*/  BENCH_L2FWD ; 
 int /*<<< orphan*/  BENCH_RXDROP ; 
 int /*<<< orphan*/  BENCH_TXONLY ; 
 int /*<<< orphan*/  XDP_COPY ; 
 int /*<<< orphan*/  XDP_FLAGS_DRV_MODE ; 
 int /*<<< orphan*/  XDP_FLAGS_SKB_MODE ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  basename (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  if_nametoindex (char*) ; 
 int /*<<< orphan*/  long_options ; 
 int /*<<< orphan*/  opt_bench ; 
 char* opt_if ; 
 int /*<<< orphan*/  opt_ifindex ; 
 void* opt_interval ; 
 int opt_poll ; 
 void* opt_queue ; 
 int opt_shared_packet_buffer ; 
 int /*<<< orphan*/  opt_xdp_bind_flags ; 
 int /*<<< orphan*/  opt_xdp_flags ; 
 char* optarg ; 
 scalar_t__ opterr ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_command_line(int argc, char **argv)
{
	int option_index, c;

	opterr = 0;

	for (;;) {
		c = getopt_long(argc, argv, "rtli:q:psSNn:", long_options,
				&option_index);
		if (c == -1)
			break;

		switch (c) {
		case 'r':
			opt_bench = BENCH_RXDROP;
			break;
		case 't':
			opt_bench = BENCH_TXONLY;
			break;
		case 'l':
			opt_bench = BENCH_L2FWD;
			break;
		case 'i':
			opt_if = optarg;
			break;
		case 'q':
			opt_queue = atoi(optarg);
			break;
		case 's':
			opt_shared_packet_buffer = 1;
			break;
		case 'p':
			opt_poll = 1;
			break;
		case 'S':
			opt_xdp_flags |= XDP_FLAGS_SKB_MODE;
			opt_xdp_bind_flags |= XDP_COPY;
			break;
		case 'N':
			opt_xdp_flags |= XDP_FLAGS_DRV_MODE;
			break;
		case 'n':
			opt_interval = atoi(optarg);
			break;
		default:
			usage(basename(argv[0]));
		}
	}

	opt_ifindex = if_nametoindex(opt_if);
	if (!opt_ifindex) {
		fprintf(stderr, "ERROR: interface \"%s\" does not exist\n",
			opt_if);
		usage(basename(argv[0]));
	}
}