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
struct btf_var_secinfo {int type; int offset; int size; } ;
struct btf_var {int /*<<< orphan*/  linkage; } ;
struct btf_type {int size; int type; int /*<<< orphan*/  info; int /*<<< orphan*/  name_off; } ;
struct btf_param {int type; int /*<<< orphan*/  name_off; } ;
struct btf_member {int offset; int type; int /*<<< orphan*/  name_off; } ;
struct btf_enum {int val; int /*<<< orphan*/  name_off; } ;
struct btf_array {int type; int index_type; int nelems; } ;
struct btf {int dummy; } ;
typedef  int /*<<< orphan*/  json_writer_t ;
typedef  int __u32 ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BTF_INFO_KFLAG (int /*<<< orphan*/ ) ; 
 int BTF_INFO_KIND (int /*<<< orphan*/ ) ; 
 int BTF_INFO_VLEN (int /*<<< orphan*/ ) ; 
 int BTF_INT_BITS (int) ; 
 int /*<<< orphan*/  BTF_INT_ENCODING (int) ; 
 int BTF_INT_OFFSET (int) ; 
#define  BTF_KIND_ARRAY 142 
#define  BTF_KIND_CONST 141 
#define  BTF_KIND_DATASEC 140 
#define  BTF_KIND_ENUM 139 
#define  BTF_KIND_FUNC 138 
#define  BTF_KIND_FUNC_PROTO 137 
#define  BTF_KIND_FWD 136 
#define  BTF_KIND_INT 135 
 int BTF_KIND_MAX ; 
#define  BTF_KIND_PTR 134 
#define  BTF_KIND_RESTRICT 133 
#define  BTF_KIND_STRUCT 132 
#define  BTF_KIND_TYPEDEF 131 
#define  BTF_KIND_UNION 130 
 int BTF_KIND_UNKN ; 
#define  BTF_KIND_VAR 129 
#define  BTF_KIND_VOLATILE 128 
 int BTF_MEMBER_BITFIELD_SIZE (int) ; 
 int BTF_MEMBER_BIT_OFFSET (int) ; 
 char* btf_int_enc_str (int /*<<< orphan*/ ) ; 
 char** btf_kind_str ; 
 char* btf_str (struct btf const*,int /*<<< orphan*/ ) ; 
 char* btf_var_linkage_str (int /*<<< orphan*/ ) ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/ * json_wtr ; 
 int /*<<< orphan*/  jsonw_end_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonw_end_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonw_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  jsonw_start_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonw_start_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonw_string_field (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  jsonw_uint_field (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int dump_btf_type(const struct btf *btf, __u32 id,
			 const struct btf_type *t)
{
	json_writer_t *w = json_wtr;
	int kind, safe_kind;

	kind = BTF_INFO_KIND(t->info);
	safe_kind = kind <= BTF_KIND_MAX ? kind : BTF_KIND_UNKN;

	if (json_output) {
		jsonw_start_object(w);
		jsonw_uint_field(w, "id", id);
		jsonw_string_field(w, "kind", btf_kind_str[safe_kind]);
		jsonw_string_field(w, "name", btf_str(btf, t->name_off));
	} else {
		printf("[%u] %s '%s'", id, btf_kind_str[safe_kind],
		       btf_str(btf, t->name_off));
	}

	switch (BTF_INFO_KIND(t->info)) {
	case BTF_KIND_INT: {
		__u32 v = *(__u32 *)(t + 1);
		const char *enc;

		enc = btf_int_enc_str(BTF_INT_ENCODING(v));

		if (json_output) {
			jsonw_uint_field(w, "size", t->size);
			jsonw_uint_field(w, "bits_offset", BTF_INT_OFFSET(v));
			jsonw_uint_field(w, "nr_bits", BTF_INT_BITS(v));
			jsonw_string_field(w, "encoding", enc);
		} else {
			printf(" size=%u bits_offset=%u nr_bits=%u encoding=%s",
			       t->size, BTF_INT_OFFSET(v), BTF_INT_BITS(v),
			       enc);
		}
		break;
	}
	case BTF_KIND_PTR:
	case BTF_KIND_CONST:
	case BTF_KIND_VOLATILE:
	case BTF_KIND_RESTRICT:
	case BTF_KIND_TYPEDEF:
		if (json_output)
			jsonw_uint_field(w, "type_id", t->type);
		else
			printf(" type_id=%u", t->type);
		break;
	case BTF_KIND_ARRAY: {
		const struct btf_array *arr = (const void *)(t + 1);

		if (json_output) {
			jsonw_uint_field(w, "type_id", arr->type);
			jsonw_uint_field(w, "index_type_id", arr->index_type);
			jsonw_uint_field(w, "nr_elems", arr->nelems);
		} else {
			printf(" type_id=%u index_type_id=%u nr_elems=%u",
			       arr->type, arr->index_type, arr->nelems);
		}
		break;
	}
	case BTF_KIND_STRUCT:
	case BTF_KIND_UNION: {
		const struct btf_member *m = (const void *)(t + 1);
		__u16 vlen = BTF_INFO_VLEN(t->info);
		int i;

		if (json_output) {
			jsonw_uint_field(w, "size", t->size);
			jsonw_uint_field(w, "vlen", vlen);
			jsonw_name(w, "members");
			jsonw_start_array(w);
		} else {
			printf(" size=%u vlen=%u", t->size, vlen);
		}
		for (i = 0; i < vlen; i++, m++) {
			const char *name = btf_str(btf, m->name_off);
			__u32 bit_off, bit_sz;

			if (BTF_INFO_KFLAG(t->info)) {
				bit_off = BTF_MEMBER_BIT_OFFSET(m->offset);
				bit_sz = BTF_MEMBER_BITFIELD_SIZE(m->offset);
			} else {
				bit_off = m->offset;
				bit_sz = 0;
			}

			if (json_output) {
				jsonw_start_object(w);
				jsonw_string_field(w, "name", name);
				jsonw_uint_field(w, "type_id", m->type);
				jsonw_uint_field(w, "bits_offset", bit_off);
				if (bit_sz) {
					jsonw_uint_field(w, "bitfield_size",
							 bit_sz);
				}
				jsonw_end_object(w);
			} else {
				printf("\n\t'%s' type_id=%u bits_offset=%u",
				       name, m->type, bit_off);
				if (bit_sz)
					printf(" bitfield_size=%u", bit_sz);
			}
		}
		if (json_output)
			jsonw_end_array(w);
		break;
	}
	case BTF_KIND_ENUM: {
		const struct btf_enum *v = (const void *)(t + 1);
		__u16 vlen = BTF_INFO_VLEN(t->info);
		int i;

		if (json_output) {
			jsonw_uint_field(w, "size", t->size);
			jsonw_uint_field(w, "vlen", vlen);
			jsonw_name(w, "values");
			jsonw_start_array(w);
		} else {
			printf(" size=%u vlen=%u", t->size, vlen);
		}
		for (i = 0; i < vlen; i++, v++) {
			const char *name = btf_str(btf, v->name_off);

			if (json_output) {
				jsonw_start_object(w);
				jsonw_string_field(w, "name", name);
				jsonw_uint_field(w, "val", v->val);
				jsonw_end_object(w);
			} else {
				printf("\n\t'%s' val=%u", name, v->val);
			}
		}
		if (json_output)
			jsonw_end_array(w);
		break;
	}
	case BTF_KIND_FWD: {
		const char *fwd_kind = BTF_INFO_KFLAG(t->info) ? "union"
							       : "struct";

		if (json_output)
			jsonw_string_field(w, "fwd_kind", fwd_kind);
		else
			printf(" fwd_kind=%s", fwd_kind);
		break;
	}
	case BTF_KIND_FUNC:
		if (json_output)
			jsonw_uint_field(w, "type_id", t->type);
		else
			printf(" type_id=%u", t->type);
		break;
	case BTF_KIND_FUNC_PROTO: {
		const struct btf_param *p = (const void *)(t + 1);
		__u16 vlen = BTF_INFO_VLEN(t->info);
		int i;

		if (json_output) {
			jsonw_uint_field(w, "ret_type_id", t->type);
			jsonw_uint_field(w, "vlen", vlen);
			jsonw_name(w, "params");
			jsonw_start_array(w);
		} else {
			printf(" ret_type_id=%u vlen=%u", t->type, vlen);
		}
		for (i = 0; i < vlen; i++, p++) {
			const char *name = btf_str(btf, p->name_off);

			if (json_output) {
				jsonw_start_object(w);
				jsonw_string_field(w, "name", name);
				jsonw_uint_field(w, "type_id", p->type);
				jsonw_end_object(w);
			} else {
				printf("\n\t'%s' type_id=%u", name, p->type);
			}
		}
		if (json_output)
			jsonw_end_array(w);
		break;
	}
	case BTF_KIND_VAR: {
		const struct btf_var *v = (const void *)(t + 1);
		const char *linkage;

		linkage = btf_var_linkage_str(v->linkage);

		if (json_output) {
			jsonw_uint_field(w, "type_id", t->type);
			jsonw_string_field(w, "linkage", linkage);
		} else {
			printf(" type_id=%u, linkage=%s", t->type, linkage);
		}
		break;
	}
	case BTF_KIND_DATASEC: {
		const struct btf_var_secinfo *v = (const void *)(t+1);
		__u16 vlen = BTF_INFO_VLEN(t->info);
		int i;

		if (json_output) {
			jsonw_uint_field(w, "size", t->size);
			jsonw_uint_field(w, "vlen", vlen);
			jsonw_name(w, "vars");
			jsonw_start_array(w);
		} else {
			printf(" size=%u vlen=%u", t->size, vlen);
		}
		for (i = 0; i < vlen; i++, v++) {
			if (json_output) {
				jsonw_start_object(w);
				jsonw_uint_field(w, "type_id", v->type);
				jsonw_uint_field(w, "offset", v->offset);
				jsonw_uint_field(w, "size", v->size);
				jsonw_end_object(w);
			} else {
				printf("\n\ttype_id=%u offset=%u size=%u",
				       v->type, v->offset, v->size);
			}
		}
		if (json_output)
			jsonw_end_array(w);
		break;
	}
	default:
		break;
	}

	if (json_output)
		jsonw_end_object(json_wtr);
	else
		printf("\n");

	return 0;
}