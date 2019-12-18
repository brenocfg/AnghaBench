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
struct bpf_create_map_attr {char* name; int key_size; int value_size; int btf_key_type_id; int btf_value_type_id; int btf_fd; int /*<<< orphan*/  map_flags; int /*<<< orphan*/  max_entries; int /*<<< orphan*/  map_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_F_NO_PREALLOC ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_SK_STORAGE ; 
 int bpf_create_map_xattr (struct bpf_create_map_attr*) ; 
 int /*<<< orphan*/  close (int) ; 
 int load_btf () ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int create_sk_storage_map(void)
{
	struct bpf_create_map_attr attr = {
		.name = "test_map",
		.map_type = BPF_MAP_TYPE_SK_STORAGE,
		.key_size = 4,
		.value_size = 8,
		.max_entries = 0,
		.map_flags = BPF_F_NO_PREALLOC,
		.btf_key_type_id = 1,
		.btf_value_type_id = 3,
	};
	int fd, btf_fd;

	btf_fd = load_btf();
	if (btf_fd < 0)
		return -1;
	attr.btf_fd = btf_fd;
	fd = bpf_create_map_xattr(&attr);
	close(attr.btf_fd);
	if (fd < 0)
		printf("Failed to create sk_storage_map\n");
	return fd;
}