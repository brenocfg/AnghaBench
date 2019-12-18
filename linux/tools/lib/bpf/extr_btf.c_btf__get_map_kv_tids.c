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
struct btf_type {int dummy; } ;
struct btf_member {scalar_t__ type; } ;
struct btf {int dummy; } ;
typedef  scalar_t__ __u32 ;
typedef  scalar_t__ __s64 ;
typedef  int __s32 ;

/* Variables and functions */
 int EINVAL ; 
 int btf__find_by_name (struct btf const*,char*) ; 
 scalar_t__ btf__resolve_size (struct btf const*,scalar_t__) ; 
 struct btf_type* btf__type_by_id (struct btf const*,int) ; 
 int /*<<< orphan*/  btf_is_struct (struct btf_type const*) ; 
 struct btf_member* btf_members (struct btf_type const*) ; 
 int btf_vlen (struct btf_type const*) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*,char*) ; 
 int /*<<< orphan*/  pr_warning (char*,char const*,...) ; 
 size_t const snprintf (char*,size_t const,char*,char const*) ; 

int btf__get_map_kv_tids(const struct btf *btf, const char *map_name,
			 __u32 expected_key_size, __u32 expected_value_size,
			 __u32 *key_type_id, __u32 *value_type_id)
{
	const struct btf_type *container_type;
	const struct btf_member *key, *value;
	const size_t max_name = 256;
	char container_name[max_name];
	__s64 key_size, value_size;
	__s32 container_id;

	if (snprintf(container_name, max_name, "____btf_map_%s", map_name) ==
	    max_name) {
		pr_warning("map:%s length of '____btf_map_%s' is too long\n",
			   map_name, map_name);
		return -EINVAL;
	}

	container_id = btf__find_by_name(btf, container_name);
	if (container_id < 0) {
		pr_debug("map:%s container_name:%s cannot be found in BTF. Missing BPF_ANNOTATE_KV_PAIR?\n",
			 map_name, container_name);
		return container_id;
	}

	container_type = btf__type_by_id(btf, container_id);
	if (!container_type) {
		pr_warning("map:%s cannot find BTF type for container_id:%u\n",
			   map_name, container_id);
		return -EINVAL;
	}

	if (!btf_is_struct(container_type) || btf_vlen(container_type) < 2) {
		pr_warning("map:%s container_name:%s is an invalid container struct\n",
			   map_name, container_name);
		return -EINVAL;
	}

	key = btf_members(container_type);
	value = key + 1;

	key_size = btf__resolve_size(btf, key->type);
	if (key_size < 0) {
		pr_warning("map:%s invalid BTF key_type_size\n", map_name);
		return key_size;
	}

	if (expected_key_size != key_size) {
		pr_warning("map:%s btf_key_type_size:%u != map_def_key_size:%u\n",
			   map_name, (__u32)key_size, expected_key_size);
		return -EINVAL;
	}

	value_size = btf__resolve_size(btf, value->type);
	if (value_size < 0) {
		pr_warning("map:%s invalid BTF value_type_size\n", map_name);
		return value_size;
	}

	if (expected_value_size != value_size) {
		pr_warning("map:%s btf_value_type_size:%u != map_def_value_size:%u\n",
			   map_name, (__u32)value_size, expected_value_size);
		return -EINVAL;
	}

	*key_type_id = key->type;
	*value_type_id = value->type;

	return 0;
}