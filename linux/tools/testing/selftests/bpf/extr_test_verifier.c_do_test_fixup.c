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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct test_val {int dummy; } ;
struct other_val {int dummy; } ;
struct bpf_test {int* fixup_map_hash_8b; int* fixup_map_hash_48b; int* fixup_map_hash_16b; int* fixup_map_array_48b; int* fixup_map_sockmap; int* fixup_map_sockhash; int* fixup_map_xskmap; int* fixup_map_stacktrace; int* fixup_prog1; int* fixup_prog2; int* fixup_map_in_map; int* fixup_cgroup_storage; int* fixup_percpu_cgroup_storage; int* fixup_map_spin_lock; int* fixup_map_array_ro; int* fixup_map_array_wo; int* fixup_map_array_small; int* fixup_sk_storage_map; int* fixup_map_event_output; int /*<<< orphan*/  (* fill_helper ) (struct bpf_test*) ;int /*<<< orphan*/  fill_insns; } ;
struct bpf_insn {int imm; } ;
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_F_RDONLY_PROG ; 
 int /*<<< orphan*/  BPF_F_WRONLY_PROG ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_ARRAY ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_HASH ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_PERF_EVENT_ARRAY ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_SOCKHASH ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_SOCKMAP ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_STACK_TRACE ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_XSKMAP ; 
 int /*<<< orphan*/  MAX_TEST_INSNS ; 
 int __create_map (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calloc (int /*<<< orphan*/ ,int) ; 
 int create_cgroup_storage (int) ; 
 int create_map (int /*<<< orphan*/ ,int,int,int) ; 
 int create_map_in_map () ; 
 int create_map_spin_lock () ; 
 int create_prog_array (int,int,int) ; 
 int create_sk_storage_map () ; 
 int /*<<< orphan*/  stub1 (struct bpf_test*) ; 
 int /*<<< orphan*/  update_map (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_test_fixup(struct bpf_test *test, enum bpf_prog_type prog_type,
			  struct bpf_insn *prog, int *map_fds)
{
	int *fixup_map_hash_8b = test->fixup_map_hash_8b;
	int *fixup_map_hash_48b = test->fixup_map_hash_48b;
	int *fixup_map_hash_16b = test->fixup_map_hash_16b;
	int *fixup_map_array_48b = test->fixup_map_array_48b;
	int *fixup_map_sockmap = test->fixup_map_sockmap;
	int *fixup_map_sockhash = test->fixup_map_sockhash;
	int *fixup_map_xskmap = test->fixup_map_xskmap;
	int *fixup_map_stacktrace = test->fixup_map_stacktrace;
	int *fixup_prog1 = test->fixup_prog1;
	int *fixup_prog2 = test->fixup_prog2;
	int *fixup_map_in_map = test->fixup_map_in_map;
	int *fixup_cgroup_storage = test->fixup_cgroup_storage;
	int *fixup_percpu_cgroup_storage = test->fixup_percpu_cgroup_storage;
	int *fixup_map_spin_lock = test->fixup_map_spin_lock;
	int *fixup_map_array_ro = test->fixup_map_array_ro;
	int *fixup_map_array_wo = test->fixup_map_array_wo;
	int *fixup_map_array_small = test->fixup_map_array_small;
	int *fixup_sk_storage_map = test->fixup_sk_storage_map;
	int *fixup_map_event_output = test->fixup_map_event_output;

	if (test->fill_helper) {
		test->fill_insns = calloc(MAX_TEST_INSNS, sizeof(struct bpf_insn));
		test->fill_helper(test);
	}

	/* Allocating HTs with 1 elem is fine here, since we only test
	 * for verifier and not do a runtime lookup, so the only thing
	 * that really matters is value size in this case.
	 */
	if (*fixup_map_hash_8b) {
		map_fds[0] = create_map(BPF_MAP_TYPE_HASH, sizeof(long long),
					sizeof(long long), 1);
		do {
			prog[*fixup_map_hash_8b].imm = map_fds[0];
			fixup_map_hash_8b++;
		} while (*fixup_map_hash_8b);
	}

	if (*fixup_map_hash_48b) {
		map_fds[1] = create_map(BPF_MAP_TYPE_HASH, sizeof(long long),
					sizeof(struct test_val), 1);
		do {
			prog[*fixup_map_hash_48b].imm = map_fds[1];
			fixup_map_hash_48b++;
		} while (*fixup_map_hash_48b);
	}

	if (*fixup_map_hash_16b) {
		map_fds[2] = create_map(BPF_MAP_TYPE_HASH, sizeof(long long),
					sizeof(struct other_val), 1);
		do {
			prog[*fixup_map_hash_16b].imm = map_fds[2];
			fixup_map_hash_16b++;
		} while (*fixup_map_hash_16b);
	}

	if (*fixup_map_array_48b) {
		map_fds[3] = create_map(BPF_MAP_TYPE_ARRAY, sizeof(int),
					sizeof(struct test_val), 1);
		update_map(map_fds[3], 0);
		do {
			prog[*fixup_map_array_48b].imm = map_fds[3];
			fixup_map_array_48b++;
		} while (*fixup_map_array_48b);
	}

	if (*fixup_prog1) {
		map_fds[4] = create_prog_array(prog_type, 4, 0);
		do {
			prog[*fixup_prog1].imm = map_fds[4];
			fixup_prog1++;
		} while (*fixup_prog1);
	}

	if (*fixup_prog2) {
		map_fds[5] = create_prog_array(prog_type, 8, 7);
		do {
			prog[*fixup_prog2].imm = map_fds[5];
			fixup_prog2++;
		} while (*fixup_prog2);
	}

	if (*fixup_map_in_map) {
		map_fds[6] = create_map_in_map();
		do {
			prog[*fixup_map_in_map].imm = map_fds[6];
			fixup_map_in_map++;
		} while (*fixup_map_in_map);
	}

	if (*fixup_cgroup_storage) {
		map_fds[7] = create_cgroup_storage(false);
		do {
			prog[*fixup_cgroup_storage].imm = map_fds[7];
			fixup_cgroup_storage++;
		} while (*fixup_cgroup_storage);
	}

	if (*fixup_percpu_cgroup_storage) {
		map_fds[8] = create_cgroup_storage(true);
		do {
			prog[*fixup_percpu_cgroup_storage].imm = map_fds[8];
			fixup_percpu_cgroup_storage++;
		} while (*fixup_percpu_cgroup_storage);
	}
	if (*fixup_map_sockmap) {
		map_fds[9] = create_map(BPF_MAP_TYPE_SOCKMAP, sizeof(int),
					sizeof(int), 1);
		do {
			prog[*fixup_map_sockmap].imm = map_fds[9];
			fixup_map_sockmap++;
		} while (*fixup_map_sockmap);
	}
	if (*fixup_map_sockhash) {
		map_fds[10] = create_map(BPF_MAP_TYPE_SOCKHASH, sizeof(int),
					sizeof(int), 1);
		do {
			prog[*fixup_map_sockhash].imm = map_fds[10];
			fixup_map_sockhash++;
		} while (*fixup_map_sockhash);
	}
	if (*fixup_map_xskmap) {
		map_fds[11] = create_map(BPF_MAP_TYPE_XSKMAP, sizeof(int),
					sizeof(int), 1);
		do {
			prog[*fixup_map_xskmap].imm = map_fds[11];
			fixup_map_xskmap++;
		} while (*fixup_map_xskmap);
	}
	if (*fixup_map_stacktrace) {
		map_fds[12] = create_map(BPF_MAP_TYPE_STACK_TRACE, sizeof(u32),
					 sizeof(u64), 1);
		do {
			prog[*fixup_map_stacktrace].imm = map_fds[12];
			fixup_map_stacktrace++;
		} while (*fixup_map_stacktrace);
	}
	if (*fixup_map_spin_lock) {
		map_fds[13] = create_map_spin_lock();
		do {
			prog[*fixup_map_spin_lock].imm = map_fds[13];
			fixup_map_spin_lock++;
		} while (*fixup_map_spin_lock);
	}
	if (*fixup_map_array_ro) {
		map_fds[14] = __create_map(BPF_MAP_TYPE_ARRAY, sizeof(int),
					   sizeof(struct test_val), 1,
					   BPF_F_RDONLY_PROG);
		update_map(map_fds[14], 0);
		do {
			prog[*fixup_map_array_ro].imm = map_fds[14];
			fixup_map_array_ro++;
		} while (*fixup_map_array_ro);
	}
	if (*fixup_map_array_wo) {
		map_fds[15] = __create_map(BPF_MAP_TYPE_ARRAY, sizeof(int),
					   sizeof(struct test_val), 1,
					   BPF_F_WRONLY_PROG);
		update_map(map_fds[15], 0);
		do {
			prog[*fixup_map_array_wo].imm = map_fds[15];
			fixup_map_array_wo++;
		} while (*fixup_map_array_wo);
	}
	if (*fixup_map_array_small) {
		map_fds[16] = __create_map(BPF_MAP_TYPE_ARRAY, sizeof(int),
					   1, 1, 0);
		update_map(map_fds[16], 0);
		do {
			prog[*fixup_map_array_small].imm = map_fds[16];
			fixup_map_array_small++;
		} while (*fixup_map_array_small);
	}
	if (*fixup_sk_storage_map) {
		map_fds[17] = create_sk_storage_map();
		do {
			prog[*fixup_sk_storage_map].imm = map_fds[17];
			fixup_sk_storage_map++;
		} while (*fixup_sk_storage_map);
	}
	if (*fixup_map_event_output) {
		map_fds[18] = __create_map(BPF_MAP_TYPE_PERF_EVENT_ARRAY,
					   sizeof(int), sizeof(int), 1, 0);
		do {
			prog[*fixup_map_event_output].imm = map_fds[18];
			fixup_map_event_output++;
		} while (*fixup_map_event_output);
	}
}