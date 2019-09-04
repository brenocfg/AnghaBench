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
struct btf_type {int type; int /*<<< orphan*/  info; } ;
struct btf_array {int nelems; int type; } ;
struct btf {int dummy; } ;
typedef  int __u32 ;
typedef  int __s64 ;

/* Variables and functions */
 int BTF_INFO_KIND (int /*<<< orphan*/ ) ; 
#define  BTF_KIND_ARRAY 132 
#define  BTF_KIND_CONST 131 
#define  BTF_KIND_RESTRICT 130 
#define  BTF_KIND_TYPEDEF 129 
#define  BTF_KIND_VOLATILE 128 
 int E2BIG ; 
 int EINVAL ; 
 int MAX_RESOLVE_DEPTH ; 
 int UINT32_MAX ; 
 struct btf_type* btf__type_by_id (struct btf const*,int) ; 
 int /*<<< orphan*/  btf_type_is_void_or_null (struct btf_type const*) ; 
 int btf_type_size (struct btf_type const*) ; 

__s64 btf__resolve_size(const struct btf *btf, __u32 type_id)
{
	const struct btf_array *array;
	const struct btf_type *t;
	__u32 nelems = 1;
	__s64 size = -1;
	int i;

	t = btf__type_by_id(btf, type_id);
	for (i = 0; i < MAX_RESOLVE_DEPTH && !btf_type_is_void_or_null(t);
	     i++) {
		size = btf_type_size(t);
		if (size >= 0)
			break;

		switch (BTF_INFO_KIND(t->info)) {
		case BTF_KIND_TYPEDEF:
		case BTF_KIND_VOLATILE:
		case BTF_KIND_CONST:
		case BTF_KIND_RESTRICT:
			type_id = t->type;
			break;
		case BTF_KIND_ARRAY:
			array = (const struct btf_array *)(t + 1);
			if (nelems && array->nelems > UINT32_MAX / nelems)
				return -E2BIG;
			nelems *= array->nelems;
			type_id = array->type;
			break;
		default:
			return -EINVAL;
		}

		t = btf__type_by_id(btf, type_id);
	}

	if (size < 0)
		return -EINVAL;

	if (nelems && size > UINT32_MAX / nelems)
		return -E2BIG;

	return nelems * size;
}