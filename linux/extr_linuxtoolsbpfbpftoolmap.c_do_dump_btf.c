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
struct btf_dumper {int /*<<< orphan*/  jw; } ;
struct bpf_map_info {int /*<<< orphan*/  btf_value_type_id; int /*<<< orphan*/  btf_key_type_id; } ;

/* Variables and functions */
 int btf_dumper_type (struct btf_dumper const*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  jsonw_end_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jsonw_start_object (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_dump_btf(const struct btf_dumper *d,
		       struct bpf_map_info *map_info, void *key,
		       void *value)
{
	int ret;

	/* start of key-value pair */
	jsonw_start_object(d->jw);

	jsonw_name(d->jw, "key");

	ret = btf_dumper_type(d, map_info->btf_key_type_id, key);
	if (ret)
		goto err_end_obj;

	jsonw_name(d->jw, "value");

	ret = btf_dumper_type(d, map_info->btf_value_type_id, value);

err_end_obj:
	/* end of key-value pair */
	jsonw_end_object(d->jw);

	return ret;
}