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
struct TYPE_2__ {scalar_t__ name; } ;
struct bpf_object {unsigned int nr_maps; struct bpf_map* maps; scalar_t__ btf; TYPE_1__ caps; } ;
struct bpf_map_def {scalar_t__ type; int max_entries; int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; int /*<<< orphan*/  map_flags; } ;
struct bpf_map {int fd; scalar_t__ inner_map_fd; int /*<<< orphan*/  name; scalar_t__ btf_value_type_id; scalar_t__ btf_key_type_id; int /*<<< orphan*/  map_ifindex; struct bpf_map_def def; } ;
struct bpf_create_map_attr {scalar_t__ map_type; int max_entries; scalar_t__ inner_map_fd; scalar_t__ btf_value_type_id; scalar_t__ btf_key_type_id; scalar_t__ btf_fd; int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; int /*<<< orphan*/  map_flags; int /*<<< orphan*/  map_ifindex; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  errmsg ;

/* Variables and functions */
 scalar_t__ BPF_MAP_TYPE_PERF_EVENT_ARRAY ; 
 int STRERR_BUFSIZE ; 
 int bpf_create_map_xattr (struct bpf_create_map_attr*) ; 
 scalar_t__ bpf_map__is_internal (struct bpf_map*) ; 
 int /*<<< orphan*/  bpf_map_find_btf_info (struct bpf_object*,struct bpf_map*) ; 
 scalar_t__ bpf_map_type__is_map_in_map (scalar_t__) ; 
 int bpf_object__populate_internal_map (struct bpf_object*,struct bpf_map*) ; 
 scalar_t__ btf__fd (scalar_t__) ; 
 int errno ; 
 int libbpf_num_possible_cpus () ; 
 char* libbpf_strerror_r (int,char*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warning (char*,int,...) ; 
 int /*<<< orphan*/  zclose (int) ; 

__attribute__((used)) static int
bpf_object__create_maps(struct bpf_object *obj)
{
	struct bpf_create_map_attr create_attr = {};
	int nr_cpus = 0;
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

		if (obj->caps.name)
			create_attr.name = map->name;
		create_attr.map_ifindex = map->map_ifindex;
		create_attr.map_type = def->type;
		create_attr.map_flags = def->map_flags;
		create_attr.key_size = def->key_size;
		create_attr.value_size = def->value_size;
		if (def->type == BPF_MAP_TYPE_PERF_EVENT_ARRAY &&
		    !def->max_entries) {
			if (!nr_cpus)
				nr_cpus = libbpf_num_possible_cpus();
			if (nr_cpus < 0) {
				pr_warning("failed to determine number of system CPUs: %d\n",
					   nr_cpus);
				err = nr_cpus;
				goto err_out;
			}
			pr_debug("map '%s': setting size to %d\n",
				 map->name, nr_cpus);
			create_attr.max_entries = nr_cpus;
		} else {
			create_attr.max_entries = def->max_entries;
		}
		create_attr.btf_fd = 0;
		create_attr.btf_key_type_id = 0;
		create_attr.btf_value_type_id = 0;
		if (bpf_map_type__is_map_in_map(def->type) &&
		    map->inner_map_fd >= 0)
			create_attr.inner_map_fd = map->inner_map_fd;

		if (obj->btf && !bpf_map_find_btf_info(obj, map)) {
			create_attr.btf_fd = btf__fd(obj->btf);
			create_attr.btf_key_type_id = map->btf_key_type_id;
			create_attr.btf_value_type_id = map->btf_value_type_id;
		}

		*pfd = bpf_create_map_xattr(&create_attr);
		if (*pfd < 0 && (create_attr.btf_key_type_id ||
				 create_attr.btf_value_type_id)) {
			err = -errno;
			cp = libbpf_strerror_r(err, errmsg, sizeof(errmsg));
			pr_warning("Error in bpf_create_map_xattr(%s):%s(%d). Retrying without BTF.\n",
				   map->name, cp, err);
			create_attr.btf_fd = 0;
			create_attr.btf_key_type_id = 0;
			create_attr.btf_value_type_id = 0;
			map->btf_key_type_id = 0;
			map->btf_value_type_id = 0;
			*pfd = bpf_create_map_xattr(&create_attr);
		}

		if (*pfd < 0) {
			size_t j;

			err = -errno;
err_out:
			cp = libbpf_strerror_r(err, errmsg, sizeof(errmsg));
			pr_warning("failed to create map (name: '%s'): %s(%d)\n",
				   map->name, cp, err);
			for (j = 0; j < i; j++)
				zclose(obj->maps[j].fd);
			return err;
		}

		if (bpf_map__is_internal(map)) {
			err = bpf_object__populate_internal_map(obj, map);
			if (err < 0) {
				zclose(*pfd);
				goto err_out;
			}
		}

		pr_debug("created map %s: fd=%d\n", map->name, *pfd);
	}

	return 0;
}