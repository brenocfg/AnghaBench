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
struct btf_type {int dummy; } ;
struct btf_dumper {int /*<<< orphan*/  jw; int /*<<< orphan*/  btf; } ;
struct btf_array {long long nelems; int /*<<< orphan*/  type; } ;
typedef  long long __u32 ;

/* Variables and functions */
 long long btf__resolve_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btf_type* btf__type_by_id (int /*<<< orphan*/ ,long long) ; 
 int btf_dumper_do_type (struct btf_dumper const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  jsonw_end_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_start_array (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btf_dumper_array(const struct btf_dumper *d, __u32 type_id,
			    const void *data)
{
	const struct btf_type *t = btf__type_by_id(d->btf, type_id);
	struct btf_array *arr = (struct btf_array *)(t + 1);
	long long elem_size;
	int ret = 0;
	__u32 i;

	elem_size = btf__resolve_size(d->btf, arr->type);
	if (elem_size < 0)
		return elem_size;

	jsonw_start_array(d->jw);
	for (i = 0; i < arr->nelems; i++) {
		ret = btf_dumper_do_type(d, arr->type, 0,
					 data + i * elem_size);
		if (ret)
			break;
	}

	jsonw_end_array(d->jw);
	return ret;
}