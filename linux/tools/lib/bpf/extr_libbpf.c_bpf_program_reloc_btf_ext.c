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
struct bpf_program {int /*<<< orphan*/  line_info_rec_size; int /*<<< orphan*/  line_info; int /*<<< orphan*/  line_info_cnt; int /*<<< orphan*/  func_info_rec_size; int /*<<< orphan*/  func_info; int /*<<< orphan*/  func_info_cnt; } ;
struct bpf_object {int /*<<< orphan*/  btf_ext; int /*<<< orphan*/  btf; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  btf_ext__func_info_rec_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btf_ext__line_info_rec_size (int /*<<< orphan*/ ) ; 
 int btf_ext__reloc_func_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int btf_ext__reloc_line_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int check_btf_ext_reloc_err (struct bpf_program*,int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
bpf_program_reloc_btf_ext(struct bpf_program *prog, struct bpf_object *obj,
			  const char *section_name,  __u32 insn_offset)
{
	int err;

	if (!insn_offset || prog->func_info) {
		/*
		 * !insn_offset => main program
		 *
		 * For sub prog, the main program's func_info has to
		 * be loaded first (i.e. prog->func_info != NULL)
		 */
		err = btf_ext__reloc_func_info(obj->btf, obj->btf_ext,
					       section_name, insn_offset,
					       &prog->func_info,
					       &prog->func_info_cnt);
		if (err)
			return check_btf_ext_reloc_err(prog, err,
						       prog->func_info,
						       "bpf_func_info");

		prog->func_info_rec_size = btf_ext__func_info_rec_size(obj->btf_ext);
	}

	if (!insn_offset || prog->line_info) {
		err = btf_ext__reloc_line_info(obj->btf, obj->btf_ext,
					       section_name, insn_offset,
					       &prog->line_info,
					       &prog->line_info_cnt);
		if (err)
			return check_btf_ext_reloc_err(prog, err,
						       prog->line_info,
						       "bpf_line_info");

		prog->line_info_rec_size = btf_ext__line_info_rec_size(obj->btf_ext);
	}

	return 0;
}