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
struct btf_type {int /*<<< orphan*/  type; int /*<<< orphan*/  name_off; } ;
struct btf_dumper {int /*<<< orphan*/  jw; int /*<<< orphan*/  btf; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  btf__name_by_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btf_type* btf__type_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btf_dumper_do_type (struct btf_dumper const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  jsonw_end_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_start_object (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btf_dumper_var(const struct btf_dumper *d, __u32 type_id,
			  __u8 bit_offset, const void *data)
{
	const struct btf_type *t = btf__type_by_id(d->btf, type_id);
	int ret;

	jsonw_start_object(d->jw);
	jsonw_name(d->jw, btf__name_by_offset(d->btf, t->name_off));
	ret = btf_dumper_do_type(d, t->type, bit_offset, data);
	jsonw_end_object(d->jw);

	return ret;
}