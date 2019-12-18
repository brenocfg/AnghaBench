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
struct btf_var {int /*<<< orphan*/  linkage; } ;
struct btf_type {int /*<<< orphan*/  name_off; int /*<<< orphan*/  type; int /*<<< orphan*/  info; } ;
struct btf_array {int /*<<< orphan*/  nelems; int /*<<< orphan*/  type; } ;
struct btf {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BTF_INFO_KFLAG (int /*<<< orphan*/ ) ; 
 int BTF_INFO_KIND (int /*<<< orphan*/ ) ; 
#define  BTF_KIND_ARRAY 143 
#define  BTF_KIND_CONST 142 
#define  BTF_KIND_DATASEC 141 
#define  BTF_KIND_ENUM 140 
#define  BTF_KIND_FUNC 139 
#define  BTF_KIND_FUNC_PROTO 138 
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
 int /*<<< orphan*/  BTF_PRINT_ARG (char*,...) ; 
 int /*<<< orphan*/  BTF_PRINT_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTF_VAR_STATIC ; 
 int /*<<< orphan*/  btf__name_by_offset (struct btf const*,int /*<<< orphan*/ ) ; 
 struct btf_type* btf__type_by_id (struct btf const*,int /*<<< orphan*/ ) ; 
 int btf_dump_func (struct btf const*,char*,struct btf_type const*,struct btf_type const*,int,int) ; 

__attribute__((used)) static int __btf_dumper_type_only(const struct btf *btf, __u32 type_id,
				  char *func_sig, int pos, int size)
{
	const struct btf_type *proto_type;
	const struct btf_array *array;
	const struct btf_var *var;
	const struct btf_type *t;

	if (!type_id) {
		BTF_PRINT_ARG("void ");
		return pos;
	}

	t = btf__type_by_id(btf, type_id);

	switch (BTF_INFO_KIND(t->info)) {
	case BTF_KIND_INT:
	case BTF_KIND_TYPEDEF:
		BTF_PRINT_ARG("%s ", btf__name_by_offset(btf, t->name_off));
		break;
	case BTF_KIND_STRUCT:
		BTF_PRINT_ARG("struct %s ",
			      btf__name_by_offset(btf, t->name_off));
		break;
	case BTF_KIND_UNION:
		BTF_PRINT_ARG("union %s ",
			      btf__name_by_offset(btf, t->name_off));
		break;
	case BTF_KIND_ENUM:
		BTF_PRINT_ARG("enum %s ",
			      btf__name_by_offset(btf, t->name_off));
		break;
	case BTF_KIND_ARRAY:
		array = (struct btf_array *)(t + 1);
		BTF_PRINT_TYPE(array->type);
		BTF_PRINT_ARG("[%d]", array->nelems);
		break;
	case BTF_KIND_PTR:
		BTF_PRINT_TYPE(t->type);
		BTF_PRINT_ARG("* ");
		break;
	case BTF_KIND_FWD:
		BTF_PRINT_ARG("%s %s ",
			      BTF_INFO_KFLAG(t->info) ? "union" : "struct",
			      btf__name_by_offset(btf, t->name_off));
		break;
	case BTF_KIND_VOLATILE:
		BTF_PRINT_ARG("volatile ");
		BTF_PRINT_TYPE(t->type);
		break;
	case BTF_KIND_CONST:
		BTF_PRINT_ARG("const ");
		BTF_PRINT_TYPE(t->type);
		break;
	case BTF_KIND_RESTRICT:
		BTF_PRINT_ARG("restrict ");
		BTF_PRINT_TYPE(t->type);
		break;
	case BTF_KIND_FUNC_PROTO:
		pos = btf_dump_func(btf, func_sig, t, NULL, pos, size);
		if (pos == -1)
			return -1;
		break;
	case BTF_KIND_FUNC:
		proto_type = btf__type_by_id(btf, t->type);
		pos = btf_dump_func(btf, func_sig, proto_type, t, pos, size);
		if (pos == -1)
			return -1;
		break;
	case BTF_KIND_VAR:
		var = (struct btf_var *)(t + 1);
		if (var->linkage == BTF_VAR_STATIC)
			BTF_PRINT_ARG("static ");
		BTF_PRINT_TYPE(t->type);
		BTF_PRINT_ARG(" %s",
			      btf__name_by_offset(btf, t->name_off));
		break;
	case BTF_KIND_DATASEC:
		BTF_PRINT_ARG("section (\"%s\") ",
			      btf__name_by_offset(btf, t->name_off));
		break;
	case BTF_KIND_UNKN:
	default:
		return -1;
	}

	return pos;
}