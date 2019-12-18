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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_F_NO_PREALLOC ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_HASH ; 
 int /*<<< orphan*/  assert (int) ; 
 int bpf_create_map (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_gen_imm_prog ; 
 int /*<<< orphan*/  bpf_gen_map_prog ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  do_test (int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int main(void)
{
	uint32_t tests = 0;
	int i, fd_map;

	fd_map = bpf_create_map(BPF_MAP_TYPE_HASH, sizeof(int),
				sizeof(int), 1, BPF_F_NO_PREALLOC);
	assert(fd_map > 0);

	for (i = 0; i < 5; i++) {
		do_test(&tests, 2, -1,     bpf_gen_imm_prog);
		do_test(&tests, 3, fd_map, bpf_gen_map_prog);
	}

	printf("test_tag: OK (%u tests)\n", tests);
	close(fd_map);
	return 0;
}