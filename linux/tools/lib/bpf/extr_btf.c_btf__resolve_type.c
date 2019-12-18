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
struct btf_type {int type; } ;
struct btf {int dummy; } ;
typedef  int __u32 ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_RESOLVE_DEPTH ; 
 struct btf_type* btf__type_by_id (struct btf const*,int) ; 
 scalar_t__ btf_is_mod (struct btf_type const*) ; 
 scalar_t__ btf_is_typedef (struct btf_type const*) ; 
 scalar_t__ btf_is_var (struct btf_type const*) ; 
 scalar_t__ btf_type_is_void_or_null (struct btf_type const*) ; 

int btf__resolve_type(const struct btf *btf, __u32 type_id)
{
	const struct btf_type *t;
	int depth = 0;

	t = btf__type_by_id(btf, type_id);
	while (depth < MAX_RESOLVE_DEPTH &&
	       !btf_type_is_void_or_null(t) &&
	       (btf_is_mod(t) || btf_is_typedef(t) || btf_is_var(t))) {
		type_id = t->type;
		t = btf__type_by_id(btf, type_id);
		depth++;
	}

	if (depth == MAX_RESOLVE_DEPTH || btf_type_is_void_or_null(t))
		return -EINVAL;

	return type_id;
}