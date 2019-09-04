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
struct btf_type {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int BTF_INFO_KIND (int /*<<< orphan*/ ) ; 
#define  BTF_KIND_CONST 131 
#define  BTF_KIND_RESTRICT 130 
#define  BTF_KIND_TYPEDEF 129 
#define  BTF_KIND_VOLATILE 128 

__attribute__((used)) static bool btf_type_is_modifier(const struct btf_type *t)
{
	/* Some of them is not strictly a C modifier
	 * but they are grouped into the same bucket
	 * for BTF concern:
	 *   A type (t) that refers to another
	 *   type through t->type AND its size cannot
	 *   be determined without following the t->type.
	 *
	 * ptr does not fall into this bucket
	 * because its size is always sizeof(void *).
	 */
	switch (BTF_INFO_KIND(t->info)) {
	case BTF_KIND_TYPEDEF:
	case BTF_KIND_VOLATILE:
	case BTF_KIND_CONST:
	case BTF_KIND_RESTRICT:
		return true;
	}

	return false;
}