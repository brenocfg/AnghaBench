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
 int /*<<< orphan*/  BPF_EXIST ; 
 int /*<<< orphan*/  BPF_NOEXIST ; 
 int MAP_SIZE ; 
 scalar_t__ TASKS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bpf_map_delete_elem (int,int*) ; 
 scalar_t__ bpf_map_update_elem (int,int*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_update_delete(unsigned int fn, void *data)
{
	int do_update = ((int *)data)[1];
	int fd = ((int *)data)[0];
	int i, key, value;

	for (i = fn; i < MAP_SIZE; i += TASKS) {
		key = value = i;

		if (do_update) {
			assert(bpf_map_update_elem(fd, &key, &value,
						   BPF_NOEXIST) == 0);
			assert(bpf_map_update_elem(fd, &key, &value,
						   BPF_EXIST) == 0);
		} else {
			assert(bpf_map_delete_elem(fd, &key) == 0);
		}
	}
}