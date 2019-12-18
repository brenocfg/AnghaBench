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
struct timespec {int member_1; int /*<<< orphan*/  member_0; } ;
struct perf_buffer_opts {int /*<<< orphan*/  sample_cb; } ;
struct perf_buffer {int dummy; } ;
struct bpf_program {int dummy; } ;
struct bpf_object {int dummy; } ;
struct bpf_map {int dummy; } ;
typedef  struct perf_buffer bpf_link ;
typedef  int /*<<< orphan*/  cpu_set_t ;
typedef  int /*<<< orphan*/  cpu_set ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_TYPE_RAW_TRACEPOINT ; 
 scalar_t__ CHECK (int,char*,char*,...) ; 
 int /*<<< orphan*/  CPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int IS_ERR (struct perf_buffer*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct perf_buffer*) ; 
 int MAX_CNT_RAWTP ; 
 int PTR_ERR (struct perf_buffer*) ; 
 int /*<<< orphan*/  bpf_link__destroy (struct perf_buffer*) ; 
 int /*<<< orphan*/  bpf_map__fd (struct bpf_map*) ; 
 int /*<<< orphan*/  bpf_object__close (struct bpf_object*) ; 
 struct bpf_map* bpf_object__find_map_by_name (struct bpf_object*,char*) ; 
 struct bpf_program* bpf_object__find_program_by_title (struct bpf_object*,char const*) ; 
 int bpf_prog_load (char const*,int /*<<< orphan*/ ,struct bpf_object**,int*) ; 
 struct perf_buffer* bpf_program__attach_raw_tracepoint (struct bpf_program*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  get_stack_print_output ; 
 int load_kallsyms () ; 
 int /*<<< orphan*/  nanosleep (struct timespec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_buffer__free (struct perf_buffer*) ; 
 struct perf_buffer* perf_buffer__new (int /*<<< orphan*/ ,int,struct perf_buffer_opts*) ; 
 int perf_buffer__poll (struct perf_buffer*,int) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int pthread_setaffinity_np (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void test_get_stack_raw_tp(void)
{
	const char *file = "./test_get_stack_rawtp.o";
	const char *prog_name = "raw_tracepoint/sys_enter";
	int i, err, prog_fd, exp_cnt = MAX_CNT_RAWTP;
	struct perf_buffer_opts pb_opts = {};
	struct perf_buffer *pb = NULL;
	struct bpf_link *link = NULL;
	struct timespec tv = {0, 10};
	struct bpf_program *prog;
	struct bpf_object *obj;
	struct bpf_map *map;
	cpu_set_t cpu_set;

	err = bpf_prog_load(file, BPF_PROG_TYPE_RAW_TRACEPOINT, &obj, &prog_fd);
	if (CHECK(err, "prog_load raw tp", "err %d errno %d\n", err, errno))
		return;

	prog = bpf_object__find_program_by_title(obj, prog_name);
	if (CHECK(!prog, "find_probe", "prog '%s' not found\n", prog_name))
		goto close_prog;

	map = bpf_object__find_map_by_name(obj, "perfmap");
	if (CHECK(!map, "bpf_find_map", "not found\n"))
		goto close_prog;

	err = load_kallsyms();
	if (CHECK(err < 0, "load_kallsyms", "err %d errno %d\n", err, errno))
		goto close_prog;

	CPU_ZERO(&cpu_set);
	CPU_SET(0, &cpu_set);
	err = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set), &cpu_set);
	if (CHECK(err, "set_affinity", "err %d, errno %d\n", err, errno))
		goto close_prog;

	link = bpf_program__attach_raw_tracepoint(prog, "sys_enter");
	if (CHECK(IS_ERR(link), "attach_raw_tp", "err %ld\n", PTR_ERR(link)))
		goto close_prog;

	pb_opts.sample_cb = get_stack_print_output;
	pb = perf_buffer__new(bpf_map__fd(map), 8, &pb_opts);
	if (CHECK(IS_ERR(pb), "perf_buf__new", "err %ld\n", PTR_ERR(pb)))
		goto close_prog;

	/* trigger some syscall action */
	for (i = 0; i < MAX_CNT_RAWTP; i++)
		nanosleep(&tv, NULL);

	while (exp_cnt > 0) {
		err = perf_buffer__poll(pb, 100);
		if (err < 0 && CHECK(err < 0, "pb__poll", "err %d\n", err))
			goto close_prog;
		exp_cnt -= err;
	}

close_prog:
	if (!IS_ERR_OR_NULL(link))
		bpf_link__destroy(link);
	if (!IS_ERR_OR_NULL(pb))
		perf_buffer__free(pb);
	bpf_object__close(obj);
}