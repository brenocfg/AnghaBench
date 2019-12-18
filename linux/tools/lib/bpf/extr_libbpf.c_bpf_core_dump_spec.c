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
struct btf_type {int /*<<< orphan*/  name_off; } ;
struct bpf_core_spec {int raw_len; int len; TYPE_1__* spec; scalar_t__ offset; int /*<<< orphan*/ * raw_spec; int /*<<< orphan*/  btf; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {scalar_t__ idx; scalar_t__ name; int /*<<< orphan*/  type_id; } ;

/* Variables and functions */
 char* btf__name_by_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btf_type* btf__type_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libbpf_print (int,char*,scalar_t__,...) ; 

__attribute__((used)) static void bpf_core_dump_spec(int level, const struct bpf_core_spec *spec)
{
	const struct btf_type *t;
	const char *s;
	__u32 type_id;
	int i;

	type_id = spec->spec[0].type_id;
	t = btf__type_by_id(spec->btf, type_id);
	s = btf__name_by_offset(spec->btf, t->name_off);
	libbpf_print(level, "[%u] %s + ", type_id, s);

	for (i = 0; i < spec->raw_len; i++)
		libbpf_print(level, "%d%s", spec->raw_spec[i],
			     i == spec->raw_len - 1 ? " => " : ":");

	libbpf_print(level, "%u @ &x", spec->offset);

	for (i = 0; i < spec->len; i++) {
		if (spec->spec[i].name)
			libbpf_print(level, ".%s", spec->spec[i].name);
		else
			libbpf_print(level, "[%u]", spec->spec[i].idx);
	}

}