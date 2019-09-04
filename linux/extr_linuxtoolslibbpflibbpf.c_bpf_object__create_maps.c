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
struct bpf_object {unsigned int nr_maps; struct bpf_map* maps; int /*<<< orphan*/  btf; } ;
struct bpf_map_def {int /*<<< orphan*/  max_entries; int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; int /*<<< orphan*/  map_flags; int /*<<< orphan*/  type; } ;
struct bpf_map {int fd; int /*<<< orphan*/  name; scalar_t__ btf_value_type_id; scalar_t__ btf_key_type_id; int /*<<< orphan*/  map_ifindex; struct bpf_map_def def; } ;
struct bpf_create_map_attr {scalar_t__ btf_value_type_id; scalar_t__ btf_key_type_id; scalar_t__ btf_fd; int /*<<< orphan*/  max_entries; int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; int /*<<< orphan*/  map_flags; int /*<<< orphan*/  map_type; int /*<<< orphan*/  map_ifindex; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  errmsg ;

/* Variables and functions */
 int STRERR_BUFSIZE ; 
 int bpf_create_map_xattr (struct bpf_create_map_attr*) ; 
 int /*<<< orphan*/  bpf_map_find_btf_info (struct bpf_map*,int /*<<< orphan*/ ) ; 
 scalar_t__ btf__fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,char*,...) ; 
 char* str_error (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zclose (int) ; 

__attribute__((used)) static int
bpf_object__create_maps(struct bpf_object *obj)
{
	struct bpf_create_map_attr create_attr = {};
	unsigned int i;
	int err;

	for (i = 0; i < obj->nr_maps; i++) {
		struct bpf_map *map = &obj->maps[i];
		struct bpf_map_def *def = &map->def;
		char *cp, errmsg[STRERR_BUFSIZE];
		int *pfd = &map->fd;

		if (map->fd >= 0) {
			pr_debug("skip map create (preset) %s: fd=%d\n",
				 map->name, map->fd);
			continue;
		}

		create_attr.name = map->name;
		create_attr.map_ifindex = map->map_ifindex;
		create_attr.map_type = def->type;
		create_attr.map_flags = def->map_flags;
		create_attr.key_size = def->key_size;
		create_attr.value_size = def->value_size;
		create_attr.max_entries = def->max_entries;
		create_attr.btf_fd = 0;
		create_attr.btf_key_type_id = 0;
		create_attr.btf_value_type_id = 0;

		if (obj->btf && !bpf_map_find_btf_info(map, obj->btf)) {
			create_attr.btf_fd = btf__fd(obj->btf);
			create_attr.btf_key_type_id = map->btf_key_type_id;
			create_attr.btf_value_type_id = map->btf_value_type_id;
		}

		*pfd = bpf_create_map_xattr(&create_attr);
		if (*pfd < 0 && create_attr.btf_key_type_id) {
			cp = str_error(errno, errmsg, sizeof(errmsg));
			pr_warning("Error in bpf_create_map_xattr(%s):%s(%d). Retrying without BTF.\n",
				   map->name, cp, errno);
			create_attr.btf_fd = 0;
			create_attr.btf_key_type_id = 0;
			create_attr.btf_value_type_id = 0;
			map->btf_key_type_id = 0;
			map->btf_value_type_id = 0;
			*pfd = bpf_create_map_xattr(&create_attr);
		}

		if (*pfd < 0) {
			size_t j;

			err = *pfd;
			cp = str_error(errno, errmsg, sizeof(errmsg));
			pr_warning("failed to create map (name: '%s'): %s\n",
				   map->name, cp);
			for (j = 0; j < i; j++)
				zclose(obj->maps[j].fd);
			return err;
		}
		pr_debug("create map %s: fd=%d\n", map->name, *pfd);
	}

	return 0;
}