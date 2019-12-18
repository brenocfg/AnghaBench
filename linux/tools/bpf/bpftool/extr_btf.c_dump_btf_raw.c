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
struct btf {int dummy; } ;
typedef  int __u32 ;

/* Variables and functions */
 int btf__get_nr_types (struct btf const*) ; 
 struct btf_type* btf__type_by_id (struct btf const*,int) ; 
 int /*<<< orphan*/  dump_btf_type (struct btf const*,int,struct btf_type const*) ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_end_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_end_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jsonw_start_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_start_object (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dump_btf_raw(const struct btf *btf,
			__u32 *root_type_ids, int root_type_cnt)
{
	const struct btf_type *t;
	int i;

	if (json_output) {
		jsonw_start_object(json_wtr);
		jsonw_name(json_wtr, "types");
		jsonw_start_array(json_wtr);
	}

	if (root_type_cnt) {
		for (i = 0; i < root_type_cnt; i++) {
			t = btf__type_by_id(btf, root_type_ids[i]);
			dump_btf_type(btf, root_type_ids[i], t);
		}
	} else {
		int cnt = btf__get_nr_types(btf);

		for (i = 1; i <= cnt; i++) {
			t = btf__type_by_id(btf, i);
			dump_btf_type(btf, i, t);
		}
	}

	if (json_output) {
		jsonw_end_array(json_wtr);
		jsonw_end_object(json_wtr);
	}
	return 0;
}