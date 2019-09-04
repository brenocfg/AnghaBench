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
struct btf_member {int dummy; } ;
struct btf_header {int type_off; int str_off; } ;
struct btf_enum {int dummy; } ;
struct btf_array {int dummy; } ;
struct btf {void* nohdr_data; struct btf_header* hdr; } ;
typedef  int /*<<< orphan*/  btf_print_fn_t ;
typedef  int __u16 ;

/* Variables and functions */
 int BTF_INFO_KIND (int /*<<< orphan*/ ) ; 
 int BTF_INFO_VLEN (int /*<<< orphan*/ ) ; 
#define  BTF_KIND_ARRAY 138 
#define  BTF_KIND_CONST 137 
#define  BTF_KIND_ENUM 136 
#define  BTF_KIND_FWD 135 
#define  BTF_KIND_INT 134 
#define  BTF_KIND_PTR 133 
#define  BTF_KIND_RESTRICT 132 
#define  BTF_KIND_STRUCT 131 
#define  BTF_KIND_TYPEDEF 130 
#define  BTF_KIND_UNION 129 
#define  BTF_KIND_VOLATILE 128 
 int EINVAL ; 
 int btf_add_type (struct btf*,struct btf_type*) ; 
 int /*<<< orphan*/  elog (char*,int) ; 

__attribute__((used)) static int btf_parse_type_sec(struct btf *btf, btf_print_fn_t err_log)
{
	struct btf_header *hdr = btf->hdr;
	void *nohdr_data = btf->nohdr_data;
	void *next_type = nohdr_data + hdr->type_off;
	void *end_type = nohdr_data + hdr->str_off;

	while (next_type < end_type) {
		struct btf_type *t = next_type;
		__u16 vlen = BTF_INFO_VLEN(t->info);
		int err;

		next_type += sizeof(*t);
		switch (BTF_INFO_KIND(t->info)) {
		case BTF_KIND_INT:
			next_type += sizeof(int);
			break;
		case BTF_KIND_ARRAY:
			next_type += sizeof(struct btf_array);
			break;
		case BTF_KIND_STRUCT:
		case BTF_KIND_UNION:
			next_type += vlen * sizeof(struct btf_member);
			break;
		case BTF_KIND_ENUM:
			next_type += vlen * sizeof(struct btf_enum);
			break;
		case BTF_KIND_TYPEDEF:
		case BTF_KIND_PTR:
		case BTF_KIND_FWD:
		case BTF_KIND_VOLATILE:
		case BTF_KIND_CONST:
		case BTF_KIND_RESTRICT:
			break;
		default:
			elog("Unsupported BTF_KIND:%u\n",
			     BTF_INFO_KIND(t->info));
			return -EINVAL;
		}

		err = btf_add_type(btf, t);
		if (err)
			return err;
	}

	return 0;
}