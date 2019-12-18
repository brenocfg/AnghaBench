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
struct btf_var_secinfo {int offset; int /*<<< orphan*/  type; } ;
struct btf_type {int /*<<< orphan*/  name_off; int /*<<< orphan*/  info; } ;
struct btf_dumper {int /*<<< orphan*/  jw; int /*<<< orphan*/  btf; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int BTF_INFO_VLEN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  btf__name_by_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btf_type* btf__type_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btf_dumper_do_type (struct btf_dumper const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  jsonw_end_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_end_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_start_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_start_object (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btf_dumper_datasec(const struct btf_dumper *d, __u32 type_id,
			      const void *data)
{
	struct btf_var_secinfo *vsi;
	const struct btf_type *t;
	int ret = 0, i, vlen;

	t = btf__type_by_id(d->btf, type_id);
	if (!t)
		return -EINVAL;

	vlen = BTF_INFO_VLEN(t->info);
	vsi = (struct btf_var_secinfo *)(t + 1);

	jsonw_start_object(d->jw);
	jsonw_name(d->jw, btf__name_by_offset(d->btf, t->name_off));
	jsonw_start_array(d->jw);
	for (i = 0; i < vlen; i++) {
		ret = btf_dumper_do_type(d, vsi[i].type, 0, data + vsi[i].offset);
		if (ret)
			break;
	}
	jsonw_end_array(d->jw);
	jsonw_end_object(d->jw);

	return ret;
}