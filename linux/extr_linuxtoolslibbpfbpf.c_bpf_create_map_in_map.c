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
typedef  enum bpf_map_type { ____Placeholder_bpf_map_type } bpf_map_type ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int bpf_create_map_in_map_node (int,char const*,int,int,int,int /*<<< orphan*/ ,int) ; 

int bpf_create_map_in_map(enum bpf_map_type map_type, const char *name,
			  int key_size, int inner_map_fd, int max_entries,
			  __u32 map_flags)
{
	return bpf_create_map_in_map_node(map_type, name, key_size,
					  inner_map_fd, max_entries, map_flags,
					  -1);
}