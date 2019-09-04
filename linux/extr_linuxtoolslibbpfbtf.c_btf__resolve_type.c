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
struct btf {int dummy; } ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BTF_INFO_KIND (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ IS_MODIFIER (int /*<<< orphan*/ ) ; 
 int MAX_RESOLVE_DEPTH ; 
 struct btf_type* btf__type_by_id (struct btf const*,int) ; 
 scalar_t__ btf_type_is_void_or_null (struct btf_type const*) ; 

int btf__resolve_type(const struct btf *btf, __u32 type_id)
{
	const struct btf_type *t;
	int depth = 0;

	t = btf__type_by_id(btf, type_id);
	while (depth < MAX_RESOLVE_DEPTH &&
	       !btf_type_is_void_or_null(t) &&
	       IS_MODIFIER(BTF_INFO_KIND(t->info))) {
		type_id = t->type;
		t = btf__type_by_id(btf, type_id);
		depth++;
	}

	if (depth == MAX_RESOLVE_DEPTH || btf_type_is_void_or_null(t))
		return -EINVAL;

	return type_id;
}