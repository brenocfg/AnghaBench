#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bpf_map_info {int /*<<< orphan*/  btf_value_type_id; int /*<<< orphan*/  btf_key_type_id; int /*<<< orphan*/  map_flags; int /*<<< orphan*/  max_entries; int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  map_flags; int /*<<< orphan*/  max_entries; int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; int /*<<< orphan*/  type; } ;
struct bpf_map {int fd; char* name; int /*<<< orphan*/  btf_value_type_id; int /*<<< orphan*/  btf_key_type_id; TYPE_1__ def; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int __u32 ;

/* Variables and functions */
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int bpf_obj_get_info_by_fd (int,struct bpf_map_info*,int*) ; 
 int /*<<< orphan*/  close (int) ; 
 int dup3 (int,int,int) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int open (char*,int) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int zclose (int) ; 

int bpf_map__reuse_fd(struct bpf_map *map, int fd)
{
	struct bpf_map_info info = {};
	__u32 len = sizeof(info);
	int new_fd, err;
	char *new_name;

	err = bpf_obj_get_info_by_fd(fd, &info, &len);
	if (err)
		return err;

	new_name = strdup(info.name);
	if (!new_name)
		return -errno;

	new_fd = open("/", O_RDONLY | O_CLOEXEC);
	if (new_fd < 0)
		goto err_free_new_name;

	new_fd = dup3(fd, new_fd, O_CLOEXEC);
	if (new_fd < 0)
		goto err_close_new_fd;

	err = zclose(map->fd);
	if (err)
		goto err_close_new_fd;
	free(map->name);

	map->fd = new_fd;
	map->name = new_name;
	map->def.type = info.type;
	map->def.key_size = info.key_size;
	map->def.value_size = info.value_size;
	map->def.max_entries = info.max_entries;
	map->def.map_flags = info.map_flags;
	map->btf_key_type_id = info.btf_key_type_id;
	map->btf_value_type_id = info.btf_value_type_id;

	return 0;

err_close_new_fd:
	close(new_fd);
err_free_new_name:
	free(new_name);
	return -errno;
}