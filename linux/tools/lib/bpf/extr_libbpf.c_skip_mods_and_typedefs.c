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
struct btf_type {int /*<<< orphan*/  type; } ;
struct btf {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 struct btf_type* btf__type_by_id (struct btf const*,int /*<<< orphan*/ ) ; 
 scalar_t__ btf_is_mod (struct btf_type const*) ; 
 scalar_t__ btf_is_typedef (struct btf_type const*) ; 

__attribute__((used)) static const struct btf_type *
skip_mods_and_typedefs(const struct btf *btf, __u32 id, __u32 *res_id)
{
	const struct btf_type *t = btf__type_by_id(btf, id);

	if (res_id)
		*res_id = id;

	while (btf_is_mod(t) || btf_is_typedef(t)) {
		if (res_id)
			*res_id = t->type;
		t = btf__type_by_id(btf, t->type);
	}

	return t;
}