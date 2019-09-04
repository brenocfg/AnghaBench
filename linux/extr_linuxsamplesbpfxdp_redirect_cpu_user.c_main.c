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
struct rlimit {int member_0; int /*<<< orphan*/  member_1; } ;
typedef  int /*<<< orphan*/  filename ;
typedef  int __u32 ;

/* Variables and functions */
 int EXIT_FAIL ; 
 int EXIT_FAIL_OPTION ; 
 int EXIT_FAIL_XDP ; 
 int EXIT_OK ; 
 int /*<<< orphan*/  IF_NAMESIZE ; 
 int MAX_CPUS ; 
 int MAX_PROG ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  RLIM_INFINITY ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  XDP_FLAGS_SKB_MODE ; 
 void* atoi (int /*<<< orphan*/ ) ; 
 char* bpf_log_buf ; 
 scalar_t__ bpf_set_link_xdp_fd (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_cpu_entry (int,int,int,int) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int*) ; 
 int if_nametoindex (char*) ; 
 int ifindex ; 
 char* ifname ; 
 int /*<<< orphan*/  ifname_buf ; 
 int /*<<< orphan*/  int_exit ; 
 scalar_t__ load_bpf_file (char*) ; 
 int /*<<< orphan*/  long_options ; 
 int /*<<< orphan*/  mark_cpus_unavailable () ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * prog_fd ; 
 int /*<<< orphan*/  read_trace_pipe () ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stats_poll (int,int,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char**) ; 
 int /*<<< orphan*/  xdp_flags ; 

int main(int argc, char **argv)
{
	struct rlimit r = {10 * 1024 * 1024, RLIM_INFINITY};
	bool use_separators = true;
	bool stress_mode = false;
	char filename[256];
	bool debug = false;
	int added_cpus = 0;
	int longindex = 0;
	int interval = 2;
	int prog_num = 5;
	int add_cpu = -1;
	__u32 qsize;
	int opt;

	/* Notice: choosing he queue size is very important with the
	 * ixgbe driver, because it's driver page recycling trick is
	 * dependend on pages being returned quickly.  The number of
	 * out-standing packets in the system must be less-than 2x
	 * RX-ring size.
	 */
	qsize = 128+64;

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);

	if (setrlimit(RLIMIT_MEMLOCK, &r)) {
		perror("setrlimit(RLIMIT_MEMLOCK)");
		return 1;
	}

	if (load_bpf_file(filename)) {
		fprintf(stderr, "ERR in load_bpf_file(): %s", bpf_log_buf);
		return EXIT_FAIL;
	}

	if (!prog_fd[0]) {
		fprintf(stderr, "ERR: load_bpf_file: %s\n", strerror(errno));
		return EXIT_FAIL;
	}

	mark_cpus_unavailable();

	/* Parse commands line args */
	while ((opt = getopt_long(argc, argv, "hSd:",
				  long_options, &longindex)) != -1) {
		switch (opt) {
		case 'd':
			if (strlen(optarg) >= IF_NAMESIZE) {
				fprintf(stderr, "ERR: --dev name too long\n");
				goto error;
			}
			ifname = (char *)&ifname_buf;
			strncpy(ifname, optarg, IF_NAMESIZE);
			ifindex = if_nametoindex(ifname);
			if (ifindex == 0) {
				fprintf(stderr,
					"ERR: --dev name unknown err(%d):%s\n",
					errno, strerror(errno));
				goto error;
			}
			break;
		case 's':
			interval = atoi(optarg);
			break;
		case 'S':
			xdp_flags |= XDP_FLAGS_SKB_MODE;
			break;
		case 'D':
			debug = true;
			break;
		case 'x':
			stress_mode = true;
			break;
		case 'z':
			use_separators = false;
			break;
		case 'p':
			/* Selecting eBPF prog to load */
			prog_num = atoi(optarg);
			if (prog_num < 0 || prog_num >= MAX_PROG) {
				fprintf(stderr,
					"--prognum too large err(%d):%s\n",
					errno, strerror(errno));
				goto error;
			}
			break;
		case 'c':
			/* Add multiple CPUs */
			add_cpu = strtoul(optarg, NULL, 0);
			if (add_cpu >= MAX_CPUS) {
				fprintf(stderr,
				"--cpu nr too large for cpumap err(%d):%s\n",
					errno, strerror(errno));
				goto error;
			}
			create_cpu_entry(add_cpu, qsize, added_cpus, true);
			added_cpus++;
			break;
		case 'q':
			qsize = atoi(optarg);
			break;
		case 'h':
		error:
		default:
			usage(argv);
			return EXIT_FAIL_OPTION;
		}
	}
	/* Required option */
	if (ifindex == -1) {
		fprintf(stderr, "ERR: required option --dev missing\n");
		usage(argv);
		return EXIT_FAIL_OPTION;
	}
	/* Required option */
	if (add_cpu == -1) {
		fprintf(stderr, "ERR: required option --cpu missing\n");
		fprintf(stderr, " Specify multiple --cpu option to add more\n");
		usage(argv);
		return EXIT_FAIL_OPTION;
	}

	/* Remove XDP program when program is interrupted or killed */
	signal(SIGINT, int_exit);
	signal(SIGTERM, int_exit);

	if (bpf_set_link_xdp_fd(ifindex, prog_fd[prog_num], xdp_flags) < 0) {
		fprintf(stderr, "link set xdp fd failed\n");
		return EXIT_FAIL_XDP;
	}

	if (debug) {
		printf("Debug-mode reading trace pipe (fix #define DEBUG)\n");
		read_trace_pipe();
	}

	stats_poll(interval, use_separators, prog_num, stress_mode);
	return EXIT_OK;
}