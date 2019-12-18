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
struct bpf_create_map_attr {char* name; int key_size; int value_size; int max_entries; int btf_key_type_id; int btf_value_type_id; int btf_fd; int /*<<< orphan*/  map_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MAP_TYPE_ARRAY ; 
 int bpf_create_map_xattr (struct bpf_create_map_attr*) ; 
 int load_btf () ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int create_map_spin_lock(void)
{
	struct bpf_create_map_attr attr = {
		.name = "test_map",
		.map_type = BPF_MAP_TYPE_ARRAY,
		.key_size = 4,
		.value_size = 8,
		.max_entries = 1,
		.btf_key_type_id = 1,
		.btf_value_type_id = 3,
	};
	int fd, btf_fd;

	btf_fd = load_btf();
	if (btf_fd < 0)
		return -1;
	attr.btf_fd = btf_fd;
	fd = bpf_create_map_xattr(&attr);
	if (fd < 0)
		printf("Failed to create map with spin_lock\n");
	return fd;
}