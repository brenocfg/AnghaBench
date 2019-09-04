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
struct test_val {int dummy; } ;
struct other_val {int dummy; } ;
struct bpf_test {int* fixup_map1; int* fixup_map2; int* fixup_map3; int* fixup_map4; int* fixup_prog1; int* fixup_prog2; int* fixup_map_in_map; int* fixup_cgroup_storage; int /*<<< orphan*/  (* fill_helper ) (struct bpf_test*) ;} ;
struct bpf_insn {int imm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MAP_TYPE_ARRAY ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_HASH ; 
 int create_cgroup_storage () ; 
 int create_map (int /*<<< orphan*/ ,int,int,int) ; 
 int create_map_in_map () ; 
 int create_prog_array (int,int) ; 
 int /*<<< orphan*/  stub1 (struct bpf_test*) ; 

__attribute__((used)) static void do_test_fixup(struct bpf_test *test, struct bpf_insn *prog,
			  int *map_fds)
{
	int *fixup_map1 = test->fixup_map1;
	int *fixup_map2 = test->fixup_map2;
	int *fixup_map3 = test->fixup_map3;
	int *fixup_map4 = test->fixup_map4;
	int *fixup_prog1 = test->fixup_prog1;
	int *fixup_prog2 = test->fixup_prog2;
	int *fixup_map_in_map = test->fixup_map_in_map;
	int *fixup_cgroup_storage = test->fixup_cgroup_storage;

	if (test->fill_helper)
		test->fill_helper(test);

	/* Allocating HTs with 1 elem is fine here, since we only test
	 * for verifier and not do a runtime lookup, so the only thing
	 * that really matters is value size in this case.
	 */
	if (*fixup_map1) {
		map_fds[0] = create_map(BPF_MAP_TYPE_HASH, sizeof(long long),
					sizeof(long long), 1);
		do {
			prog[*fixup_map1].imm = map_fds[0];
			fixup_map1++;
		} while (*fixup_map1);
	}

	if (*fixup_map2) {
		map_fds[1] = create_map(BPF_MAP_TYPE_HASH, sizeof(long long),
					sizeof(struct test_val), 1);
		do {
			prog[*fixup_map2].imm = map_fds[1];
			fixup_map2++;
		} while (*fixup_map2);
	}

	if (*fixup_map3) {
		map_fds[2] = create_map(BPF_MAP_TYPE_HASH, sizeof(long long),
					sizeof(struct other_val), 1);
		do {
			prog[*fixup_map3].imm = map_fds[2];
			fixup_map3++;
		} while (*fixup_map3);
	}

	if (*fixup_map4) {
		map_fds[3] = create_map(BPF_MAP_TYPE_ARRAY, sizeof(int),
					sizeof(struct test_val), 1);
		do {
			prog[*fixup_map4].imm = map_fds[3];
			fixup_map4++;
		} while (*fixup_map4);
	}

	if (*fixup_prog1) {
		map_fds[4] = create_prog_array(4, 0);
		do {
			prog[*fixup_prog1].imm = map_fds[4];
			fixup_prog1++;
		} while (*fixup_prog1);
	}

	if (*fixup_prog2) {
		map_fds[5] = create_prog_array(8, 7);
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
		map_fds[7] = create_cgroup_storage();
		do {
			prog[*fixup_cgroup_storage].imm = map_fds[7];
			fixup_cgroup_storage++;
		} while (*fixup_cgroup_storage);
	}
}