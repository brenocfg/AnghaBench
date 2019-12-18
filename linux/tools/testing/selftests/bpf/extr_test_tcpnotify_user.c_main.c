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
struct tcpnotify_globals {int ncalls; int /*<<< orphan*/  member_0; } ;
struct perf_buffer_opts {int /*<<< orphan*/  sample_cb; } ;
struct perf_buffer {int dummy; } ;
struct bpf_object {int dummy; } ;
struct bpf_map {int dummy; } ;
typedef  int /*<<< orphan*/  cpu_set_t ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_CGROUP_SOCK_OPS ; 
 int /*<<< orphan*/  BPF_PROG_TYPE_SOCK_OPS ; 
 int /*<<< orphan*/  CPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int EXIT_FAILURE ; 
 scalar_t__ IS_ERR (struct perf_buffer*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct perf_buffer*) ; 
 int TESTPORT ; 
 int /*<<< orphan*/  bpf_map__fd (struct bpf_map*) ; 
 int bpf_map_lookup_elem (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tcpnotify_globals*) ; 
 struct bpf_map* bpf_object__find_map_by_name (struct bpf_object*,char*) ; 
 int bpf_prog_attach (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_detach (int,int /*<<< orphan*/ ) ; 
 scalar_t__ bpf_prog_load (char const*,int /*<<< orphan*/ ,struct bpf_object**,int*) ; 
 int /*<<< orphan*/  cleanup_cgroup_environment () ; 
 int /*<<< orphan*/  close (int) ; 
 int create_and_get_cgroup (char const*) ; 
 int /*<<< orphan*/  dummyfn ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ join_cgroup (char const*) ; 
 int /*<<< orphan*/  perf_buffer__free (struct perf_buffer*) ; 
 struct perf_buffer* perf_buffer__new (int /*<<< orphan*/ ,int,struct perf_buffer_opts*) ; 
 int /*<<< orphan*/  poller_thread ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct perf_buffer*) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  pthread_setaffinity_np (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int rx_callbacks ; 
 scalar_t__ setup_cgroup_environment () ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system (char*) ; 
 int /*<<< orphan*/  tid ; 
 scalar_t__ verify_result (struct tcpnotify_globals*) ; 

int main(int argc, char **argv)
{
	const char *file = "test_tcpnotify_kern.o";
	struct bpf_map *perf_map, *global_map;
	struct perf_buffer_opts pb_opts = {};
	struct tcpnotify_globals g = {0};
	struct perf_buffer *pb = NULL;
	const char *cg_path = "/foo";
	int prog_fd, rv, cg_fd = -1;
	int error = EXIT_FAILURE;
	struct bpf_object *obj;
	char test_script[80];
	cpu_set_t cpuset;
	__u32 key = 0;

	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);
	pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);

	if (setup_cgroup_environment())
		goto err;

	cg_fd = create_and_get_cgroup(cg_path);
	if (cg_fd < 0)
		goto err;

	if (join_cgroup(cg_path))
		goto err;

	if (bpf_prog_load(file, BPF_PROG_TYPE_SOCK_OPS, &obj, &prog_fd)) {
		printf("FAILED: load_bpf_file failed for: %s\n", file);
		goto err;
	}

	rv = bpf_prog_attach(prog_fd, cg_fd, BPF_CGROUP_SOCK_OPS, 0);
	if (rv) {
		printf("FAILED: bpf_prog_attach: %d (%s)\n",
		       error, strerror(errno));
		goto err;
	}

	perf_map = bpf_object__find_map_by_name(obj, "perf_event_map");
	if (!perf_map) {
		printf("FAIL:map '%s' not found\n", "perf_event_map");
		goto err;
	}

	global_map = bpf_object__find_map_by_name(obj, "global_map");
	if (!global_map) {
		printf("FAIL:map '%s' not found\n", "global_map");
		return -1;
	}

	pb_opts.sample_cb = dummyfn;
	pb = perf_buffer__new(bpf_map__fd(perf_map), 8, &pb_opts);
	if (IS_ERR(pb))
		goto err;

	pthread_create(&tid, NULL, poller_thread, pb);

	sprintf(test_script,
		"iptables -A INPUT -p tcp --dport %d -j DROP",
		TESTPORT);
	system(test_script);

	sprintf(test_script,
		"nc 127.0.0.1 %d < /etc/passwd > /dev/null 2>&1 ",
		TESTPORT);
	system(test_script);

	sprintf(test_script,
		"iptables -D INPUT -p tcp --dport %d -j DROP",
		TESTPORT);
	system(test_script);

	rv = bpf_map_lookup_elem(bpf_map__fd(global_map), &key, &g);
	if (rv != 0) {
		printf("FAILED: bpf_map_lookup_elem returns %d\n", rv);
		goto err;
	}

	sleep(10);

	if (verify_result(&g)) {
		printf("FAILED: Wrong stats Expected %d calls, got %d\n",
			g.ncalls, rx_callbacks);
		goto err;
	}

	printf("PASSED!\n");
	error = 0;
err:
	bpf_prog_detach(cg_fd, BPF_CGROUP_SOCK_OPS);
	close(cg_fd);
	cleanup_cgroup_environment();
	if (!IS_ERR_OR_NULL(pb))
		perf_buffer__free(pb);
	return error;
}