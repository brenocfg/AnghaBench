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
struct btf_dumper {int is_plain_text; int /*<<< orphan*/ * jw; struct btf* btf; } ;
struct btf {int dummy; } ;
struct bpf_map_info {int /*<<< orphan*/  btf_id; } ;
typedef  int /*<<< orphan*/  json_writer_t ;

/* Variables and functions */
 int /*<<< orphan*/  btf__free (struct btf*) ; 
 int btf__get_from_id (int /*<<< orphan*/ ,struct btf**) ; 
 int /*<<< orphan*/  do_dump_btf (struct btf_dumper*,struct bpf_map_info*,void*,void*) ; 
 int /*<<< orphan*/ * get_btf_writer () ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  jsonw_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  p_err (char*) ; 
 int /*<<< orphan*/  p_info (char*) ; 
 int /*<<< orphan*/  print_entry_json (struct bpf_map_info*,void*,void*,struct btf*) ; 
 int /*<<< orphan*/  print_entry_plain (struct bpf_map_info*,void*,void*) ; 

__attribute__((used)) static void print_key_value(struct bpf_map_info *info, void *key,
			    void *value)
{
	json_writer_t *btf_wtr;
	struct btf *btf = NULL;
	int err;

	err = btf__get_from_id(info->btf_id, &btf);
	if (err) {
		p_err("failed to get btf");
		return;
	}

	if (json_output) {
		print_entry_json(info, key, value, btf);
	} else if (btf) {
		/* if here json_wtr wouldn't have been initialised,
		 * so let's create separate writer for btf
		 */
		btf_wtr = get_btf_writer();
		if (!btf_wtr) {
			p_info("failed to create json writer for btf. falling back to plain output");
			btf__free(btf);
			btf = NULL;
			print_entry_plain(info, key, value);
		} else {
			struct btf_dumper d = {
				.btf = btf,
				.jw = btf_wtr,
				.is_plain_text = true,
			};

			do_dump_btf(&d, info, key, value);
			jsonw_destroy(&btf_wtr);
		}
	} else {
		print_entry_plain(info, key, value);
	}
	btf__free(btf);
}