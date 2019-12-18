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
struct btf_type {int /*<<< orphan*/  type; int /*<<< orphan*/  size; } ;
struct btf_member {int /*<<< orphan*/  type; } ;
struct btf {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int __u16 ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  BTF_KIND_ARRAY 137 
#define  BTF_KIND_CONST 136 
#define  BTF_KIND_ENUM 135 
#define  BTF_KIND_INT 134 
#define  BTF_KIND_PTR 133 
#define  BTF_KIND_RESTRICT 132 
#define  BTF_KIND_STRUCT 131 
#define  BTF_KIND_TYPEDEF 130 
#define  BTF_KIND_UNION 129 
#define  BTF_KIND_VOLATILE 128 
 struct btf_type* btf__type_by_id (struct btf const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* btf_array (struct btf_type const*) ; 
 int btf_kind (struct btf_type const*) ; 
 struct btf_member* btf_members (struct btf_type const*) ; 
 int btf_vlen (struct btf_type const*) ; 
 int max (int,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,int) ; 

__attribute__((used)) static int btf_align_of(const struct btf *btf, __u32 id)
{
	const struct btf_type *t = btf__type_by_id(btf, id);
	__u16 kind = btf_kind(t);

	switch (kind) {
	case BTF_KIND_INT:
	case BTF_KIND_ENUM:
		return min(sizeof(void *), t->size);
	case BTF_KIND_PTR:
		return sizeof(void *);
	case BTF_KIND_TYPEDEF:
	case BTF_KIND_VOLATILE:
	case BTF_KIND_CONST:
	case BTF_KIND_RESTRICT:
		return btf_align_of(btf, t->type);
	case BTF_KIND_ARRAY:
		return btf_align_of(btf, btf_array(t)->type);
	case BTF_KIND_STRUCT:
	case BTF_KIND_UNION: {
		const struct btf_member *m = btf_members(t);
		__u16 vlen = btf_vlen(t);
		int i, align = 1;

		for (i = 0; i < vlen; i++, m++)
			align = max(align, btf_align_of(btf, m->type));

		return align;
	}
	default:
		pr_warning("unsupported BTF_KIND:%u\n", btf_kind(t));
		return 1;
	}
}