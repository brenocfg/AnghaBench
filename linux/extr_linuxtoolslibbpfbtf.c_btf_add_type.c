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
struct btf {int types_size; int nr_types; struct btf_type** types; } ;
typedef  int __u32 ;

/* Variables and functions */
 int BTF_MAX_NR_TYPES ; 
 int E2BIG ; 
 int ENOMEM ; 
 struct btf_type btf_void ; 
 int max (int,int) ; 
 int min (int,int) ; 
 struct btf_type** realloc (struct btf_type**,int) ; 

__attribute__((used)) static int btf_add_type(struct btf *btf, struct btf_type *t)
{
	if (btf->types_size - btf->nr_types < 2) {
		struct btf_type **new_types;
		__u32 expand_by, new_size;

		if (btf->types_size == BTF_MAX_NR_TYPES)
			return -E2BIG;

		expand_by = max(btf->types_size >> 2, 16);
		new_size = min(BTF_MAX_NR_TYPES, btf->types_size + expand_by);

		new_types = realloc(btf->types, sizeof(*new_types) * new_size);
		if (!new_types)
			return -ENOMEM;

		if (btf->nr_types == 0)
			new_types[0] = &btf_void;

		btf->types = new_types;
		btf->types_size = new_size;
	}

	btf->types[++(btf->nr_types)] = t;

	return 0;
}