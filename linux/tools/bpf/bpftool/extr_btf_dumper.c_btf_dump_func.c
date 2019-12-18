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
struct btf_type {int /*<<< orphan*/  info; int /*<<< orphan*/  name_off; scalar_t__ type; } ;
struct btf_param {int /*<<< orphan*/  name_off; scalar_t__ type; } ;
struct btf {int dummy; } ;

/* Variables and functions */
 int BTF_INFO_VLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTF_PRINT_ARG (char*,...) ; 
 int /*<<< orphan*/  BTF_PRINT_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  btf__name_by_offset (struct btf const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btf_dump_func(const struct btf *btf, char *func_sig,
			 const struct btf_type *func_proto,
			 const struct btf_type *func, int pos, int size)
{
	int i, vlen;

	BTF_PRINT_TYPE(func_proto->type);
	if (func)
		BTF_PRINT_ARG("%s(", btf__name_by_offset(btf, func->name_off));
	else
		BTF_PRINT_ARG("(");
	vlen = BTF_INFO_VLEN(func_proto->info);
	for (i = 0; i < vlen; i++) {
		struct btf_param *arg = &((struct btf_param *)(func_proto + 1))[i];

		if (i)
			BTF_PRINT_ARG(", ");
		if (arg->type) {
			BTF_PRINT_TYPE(arg->type);
			BTF_PRINT_ARG("%s",
				      btf__name_by_offset(btf, arg->name_off));
		} else {
			BTF_PRINT_ARG("...");
		}
	}
	BTF_PRINT_ARG(")");

	return pos;
}