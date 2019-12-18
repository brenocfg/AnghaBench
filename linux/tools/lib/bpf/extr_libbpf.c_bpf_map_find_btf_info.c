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
struct TYPE_2__ {scalar_t__ btf_maps_shndx; } ;
struct bpf_object {int /*<<< orphan*/  btf; TYPE_1__ efile; } ;
struct bpf_map_def {int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; } ;
struct bpf_map {scalar_t__ sec_idx; size_t libbpf_type; int btf_key_type_id; int btf_value_type_id; int /*<<< orphan*/  name; struct bpf_map_def def; } ;
typedef  int __u32 ;

/* Variables and functions */
 scalar_t__ bpf_map__is_internal (struct bpf_map*) ; 
 int btf__find_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btf__get_map_kv_tids (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/ * libbpf_type_to_btf_name ; 

__attribute__((used)) static int bpf_map_find_btf_info(struct bpf_object *obj, struct bpf_map *map)
{
	struct bpf_map_def *def = &map->def;
	__u32 key_type_id = 0, value_type_id = 0;
	int ret;

	/* if it's BTF-defined map, we don't need to search for type IDs */
	if (map->sec_idx == obj->efile.btf_maps_shndx)
		return 0;

	if (!bpf_map__is_internal(map)) {
		ret = btf__get_map_kv_tids(obj->btf, map->name, def->key_size,
					   def->value_size, &key_type_id,
					   &value_type_id);
	} else {
		/*
		 * LLVM annotates global data differently in BTF, that is,
		 * only as '.data', '.bss' or '.rodata'.
		 */
		ret = btf__find_by_name(obj->btf,
				libbpf_type_to_btf_name[map->libbpf_type]);
	}
	if (ret < 0)
		return ret;

	map->btf_key_type_id = key_type_id;
	map->btf_value_type_id = bpf_map__is_internal(map) ?
				 ret : value_type_id;
	return 0;
}