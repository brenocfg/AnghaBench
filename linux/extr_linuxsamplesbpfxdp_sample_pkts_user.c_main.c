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
struct bpf_prog_load_attr {char* file; int /*<<< orphan*/  prog_type; } ;
struct bpf_object {int dummy; } ;
struct bpf_map {int dummy; } ;
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_TYPE_XDP ; 
 int MAX_CPUS ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int bpf_map__fd (struct bpf_map*) ; 
 struct bpf_map* bpf_map__next (int /*<<< orphan*/ *,struct bpf_object*) ; 
 scalar_t__ bpf_prog_load_xattr (struct bpf_prog_load_attr*,struct bpf_object**,int*) ; 
 int do_attach (scalar_t__,int,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int get_nprocs () ; 
 int /*<<< orphan*/ * headers ; 
 scalar_t__ if_idx ; 
 char* if_name ; 
 scalar_t__ if_nametoindex (char*) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ perf_event_mmap_header (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int perf_event_poller_multi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/ * pmu_fds ; 
 int /*<<< orphan*/  print_bpf_output ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sig_handler ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bpf_perf_event (int,int) ; 

int main(int argc, char **argv)
{
	struct bpf_prog_load_attr prog_load_attr = {
		.prog_type	= BPF_PROG_TYPE_XDP,
	};
	struct bpf_object *obj;
	struct bpf_map *map;
	int prog_fd, map_fd;
	char filename[256];
	int ret, err, i;
	int numcpus;

	if (argc < 2) {
		printf("Usage: %s <ifname>\n", argv[0]);
		return 1;
	}

	numcpus = get_nprocs();
	if (numcpus > MAX_CPUS)
		numcpus = MAX_CPUS;

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);
	prog_load_attr.file = filename;

	if (bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd))
		return 1;

	if (!prog_fd) {
		printf("load_bpf_file: %s\n", strerror(errno));
		return 1;
	}

	map = bpf_map__next(NULL, obj);
	if (!map) {
		printf("finding a map in obj file failed\n");
		return 1;
	}
	map_fd = bpf_map__fd(map);

	if_idx = if_nametoindex(argv[1]);
	if (!if_idx)
		if_idx = strtoul(argv[1], NULL, 0);

	if (!if_idx) {
		fprintf(stderr, "Invalid ifname\n");
		return 1;
	}
	if_name = argv[1];
	err = do_attach(if_idx, prog_fd, argv[1]);
	if (err)
		return err;

	if (signal(SIGINT, sig_handler) ||
	    signal(SIGHUP, sig_handler) ||
	    signal(SIGTERM, sig_handler)) {
		perror("signal");
		return 1;
	}

	test_bpf_perf_event(map_fd, numcpus);

	for (i = 0; i < numcpus; i++)
		if (perf_event_mmap_header(pmu_fds[i], &headers[i]) < 0)
			return 1;

	ret = perf_event_poller_multi(pmu_fds, headers, numcpus,
				      print_bpf_output);
	kill(0, SIGINT);
	return ret;
}