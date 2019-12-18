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
struct btf_dumper {int /*<<< orphan*/  jw; int /*<<< orphan*/  is_plain_text; int /*<<< orphan*/  btf; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int BTF_INFO_KIND (int /*<<< orphan*/ ) ; 
#define  BTF_KIND_ARRAY 141 
#define  BTF_KIND_CONST 140 
#define  BTF_KIND_DATASEC 139 
#define  BTF_KIND_ENUM 138 
#define  BTF_KIND_FWD 137 
#define  BTF_KIND_INT 136 
#define  BTF_KIND_PTR 135 
#define  BTF_KIND_RESTRICT 134 
#define  BTF_KIND_STRUCT 133 
#define  BTF_KIND_TYPEDEF 132 
#define  BTF_KIND_UNION 131 
#define  BTF_KIND_UNKN 130 
#define  BTF_KIND_VAR 129 
#define  BTF_KIND_VOLATILE 128 
 int EINVAL ; 
 struct btf_type* btf__type_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btf_dumper_array (struct btf_dumper const*,int /*<<< orphan*/ ,void const*) ; 
 int btf_dumper_datasec (struct btf_dumper const*,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  btf_dumper_enum (void const*,int /*<<< orphan*/ ) ; 
 int btf_dumper_int (struct btf_type const*,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btf_dumper_modifier (struct btf_dumper const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  btf_dumper_ptr (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btf_dumper_struct (struct btf_dumper const*,int /*<<< orphan*/ ,void const*) ; 
 int btf_dumper_var (struct btf_dumper const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  jsonw_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int btf_dumper_do_type(const struct btf_dumper *d, __u32 type_id,
			      __u8 bit_offset, const void *data)
{
	const struct btf_type *t = btf__type_by_id(d->btf, type_id);

	switch (BTF_INFO_KIND(t->info)) {
	case BTF_KIND_INT:
		return btf_dumper_int(t, bit_offset, data, d->jw,
				     d->is_plain_text);
	case BTF_KIND_STRUCT:
	case BTF_KIND_UNION:
		return btf_dumper_struct(d, type_id, data);
	case BTF_KIND_ARRAY:
		return btf_dumper_array(d, type_id, data);
	case BTF_KIND_ENUM:
		btf_dumper_enum(data, d->jw);
		return 0;
	case BTF_KIND_PTR:
		btf_dumper_ptr(data, d->jw, d->is_plain_text);
		return 0;
	case BTF_KIND_UNKN:
		jsonw_printf(d->jw, "(unknown)");
		return 0;
	case BTF_KIND_FWD:
		/* map key or value can't be forward */
		jsonw_printf(d->jw, "(fwd-kind-invalid)");
		return -EINVAL;
	case BTF_KIND_TYPEDEF:
	case BTF_KIND_VOLATILE:
	case BTF_KIND_CONST:
	case BTF_KIND_RESTRICT:
		return btf_dumper_modifier(d, type_id, bit_offset, data);
	case BTF_KIND_VAR:
		return btf_dumper_var(d, type_id, bit_offset, data);
	case BTF_KIND_DATASEC:
		return btf_dumper_datasec(d, type_id, data);
	default:
		jsonw_printf(d->jw, "(unsupported-kind");
		return -EINVAL;
	}
}