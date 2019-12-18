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
struct btf_type {scalar_t__ name_off; int info; scalar_t__ size; } ;

/* Variables and functions */
 int btf_equal_enum (struct btf_type*,struct btf_type*) ; 
 int /*<<< orphan*/  btf_is_enum_fwd (struct btf_type*) ; 

__attribute__((used)) static bool btf_compat_enum(struct btf_type *t1, struct btf_type *t2)
{
	if (!btf_is_enum_fwd(t1) && !btf_is_enum_fwd(t2))
		return btf_equal_enum(t1, t2);
	/* ignore vlen when comparing */
	return t1->name_off == t2->name_off &&
	       (t1->info & ~0xffff) == (t2->info & ~0xffff) &&
	       t1->size == t2->size;
}