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
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_ANY ; 
 scalar_t__ SLOTS ; 
 int /*<<< orphan*/  bpf_map_update_elem (int,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int bpf_num_possible_cpus () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_stats(int fd)
{
	unsigned int nr_cpus = bpf_num_possible_cpus();
	__u64 values[nr_cpus];
	__u32 key;

	memset(values, 0, sizeof(values));
	for (key = 0; key < SLOTS; key++)
		bpf_map_update_elem(fd, &key, values, BPF_ANY);
}