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
struct bpf_create_map_attr {int map_type; int key_size; int value_size; int max_entries; int /*<<< orphan*/  map_flags; } ;
typedef  enum bpf_map_type { ____Placeholder_bpf_map_type } bpf_map_type ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int bpf_create_map_xattr (struct bpf_create_map_attr*) ; 

int bpf_create_map(enum bpf_map_type map_type, int key_size,
		   int value_size, int max_entries, __u32 map_flags)
{
	struct bpf_create_map_attr map_attr = {};

	map_attr.map_type = map_type;
	map_attr.map_flags = map_flags;
	map_attr.key_size = key_size;
	map_attr.value_size = value_size;
	map_attr.max_entries = max_entries;

	return bpf_create_map_xattr(&map_attr);
}