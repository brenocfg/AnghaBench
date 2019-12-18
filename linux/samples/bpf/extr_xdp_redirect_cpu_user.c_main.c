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
struct bpf_program {int dummy; } ;
struct bpf_prog_load_attr {char* file; int /*<<< orphan*/  prog_type; } ;
struct bpf_prog_info {int /*<<< orphan*/  id; } ;
struct bpf_object {int dummy; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  filename ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_TYPE_UNSPEC ; 
 int EXIT_FAIL ; 
 int EXIT_FAIL_OPTION ; 
 int EXIT_FAIL_XDP ; 
 int EXIT_OK ; 
 int /*<<< orphan*/  IF_NAMESIZE ; 
 int MAX_CPUS ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  RLIM_INFINITY ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  XDP_FLAGS_SKB_MODE ; 
 int /*<<< orphan*/  XDP_FLAGS_UPDATE_IF_NOEXIST ; 
 void* atoi (char*) ; 
 int bpf_obj_get_info_by_fd (int,struct bpf_prog_info*,int*) ; 
 struct bpf_program* bpf_object__find_program_by_title (struct bpf_object*,char*) ; 
 scalar_t__ bpf_prog_load_xattr (struct bpf_prog_load_attr*,struct bpf_object**,int*) ; 
 int bpf_program__fd (struct bpf_program*) ; 
 scalar_t__ bpf_set_link_xdp_fd (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_cpu_entry (int,int,int,int) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int*) ; 
 int if_nametoindex (char*) ; 
 int ifindex ; 
 char* ifname ; 
 int /*<<< orphan*/  ifname_buf ; 
 scalar_t__ init_map_fds (struct bpf_object*) ; 
 int /*<<< orphan*/  int_exit ; 
 int /*<<< orphan*/  long_options ; 
 int /*<<< orphan*/  mark_cpus_unavailable () ; 
 char* optarg ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  prog_id ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stats_poll (int,int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int /*<<< orphan*/ ) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char**,struct bpf_object*) ; 
 int /*<<< orphan*/  xdp_flags ; 

int main(int argc, char **argv)
{
	struct rlimit r = {10 * 1024 * 1024, RLIM_INFINITY};
	char *prog_name = "xdp_cpu_map5_lb_hash_ip_pairs";
	struct bpf_prog_load_attr prog_load_attr = {
		.prog_type	= BPF_PROG_TYPE_UNSPEC,
	};
	struct bpf_prog_info info = {};
	__u32 info_len = sizeof(info);
	bool use_separators = true;
	bool stress_mode = false;
	struct bpf_program *prog;
	struct bpf_object *obj;
	char filename[256];
	int added_cpus = 0;
	int longindex = 0;
	int interval = 2;
	int add_cpu = -1;
	int opt, err;
	int prog_fd;
	__u32 qsize;

	/* Notice: choosing he queue size is very important with the
	 * ixgbe driver, because it's driver page recycling trick is
	 * dependend on pages being returned quickly.  The number of
	 * out-standing packets in the system must be less-than 2x
	 * RX-ring size.
	 */
	qsize = 128+64;

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);
	prog_load_attr.file = filename;

	if (setrlimit(RLIMIT_MEMLOCK, &r)) {
		perror("setrlimit(RLIMIT_MEMLOCK)");
		return 1;
	}

	if (bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd))
		return EXIT_FAIL;

	if (prog_fd < 0) {
		fprintf(stderr, "ERR: bpf_prog_load_xattr: %s\n",
			strerror(errno));
		return EXIT_FAIL;
	}
	if (init_map_fds(obj) < 0) {
		fprintf(stderr, "bpf_object__find_map_fd_by_name failed\n");
		return EXIT_FAIL;
	}
	mark_cpus_unavailable();

	/* Parse commands line args */
	while ((opt = getopt_long(argc, argv, "hSd:s:p:q:c:xzF",
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
		case 'x':
			stress_mode = true;
			break;
		case 'z':
			use_separators = false;
			break;
		case 'p':
			/* Selecting eBPF prog to load */
			prog_name = optarg;
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
		case 'F':
			xdp_flags &= ~XDP_FLAGS_UPDATE_IF_NOEXIST;
			break;
		case 'h':
		error:
		default:
			usage(argv, obj);
			return EXIT_FAIL_OPTION;
		}
	}
	/* Required option */
	if (ifindex == -1) {
		fprintf(stderr, "ERR: required option --dev missing\n");
		usage(argv, obj);
		return EXIT_FAIL_OPTION;
	}
	/* Required option */
	if (add_cpu == -1) {
		fprintf(stderr, "ERR: required option --cpu missing\n");
		fprintf(stderr, " Specify multiple --cpu option to add more\n");
		usage(argv, obj);
		return EXIT_FAIL_OPTION;
	}

	/* Remove XDP program when program is interrupted or killed */
	signal(SIGINT, int_exit);
	signal(SIGTERM, int_exit);

	prog = bpf_object__find_program_by_title(obj, prog_name);
	if (!prog) {
		fprintf(stderr, "bpf_object__find_program_by_title failed\n");
		return EXIT_FAIL;
	}

	prog_fd = bpf_program__fd(prog);
	if (prog_fd < 0) {
		fprintf(stderr, "bpf_program__fd failed\n");
		return EXIT_FAIL;
	}

	if (bpf_set_link_xdp_fd(ifindex, prog_fd, xdp_flags) < 0) {
		fprintf(stderr, "link set xdp fd failed\n");
		return EXIT_FAIL_XDP;
	}

	err = bpf_obj_get_info_by_fd(prog_fd, &info, &info_len);
	if (err) {
		printf("can't get prog info - %s\n", strerror(errno));
		return err;
	}
	prog_id = info.id;

	stats_poll(interval, use_separators, prog_name, stress_mode);
	return EXIT_OK;
}