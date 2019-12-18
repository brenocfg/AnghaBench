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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_F_LOCK ; 
 scalar_t__ CHECK_FAIL (int) ; 
 int bpf_map_lookup_elem_flags (int,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_exit (void*) ; 

__attribute__((used)) static void *parallel_map_access(void *arg)
{
	int err, map_fd = *(u32 *) arg;
	int vars[17], i, j, rnd, key = 0;

	for (i = 0; i < 10000; i++) {
		err = bpf_map_lookup_elem_flags(map_fd, &key, vars, BPF_F_LOCK);
		if (CHECK_FAIL(err)) {
			printf("lookup failed\n");
			goto out;
		}
		if (CHECK_FAIL(vars[0] != 0)) {
			printf("lookup #%d var[0]=%d\n", i, vars[0]);
			goto out;
		}
		rnd = vars[1];
		for (j = 2; j < 17; j++) {
			if (vars[j] == rnd)
				continue;
			printf("lookup #%d var[1]=%d var[%d]=%d\n",
			       i, rnd, j, vars[j]);
			CHECK_FAIL(vars[j] != rnd);
			goto out;
		}
	}
out:
	pthread_exit(arg);
}