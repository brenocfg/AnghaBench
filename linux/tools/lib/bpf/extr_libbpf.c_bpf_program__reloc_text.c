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
struct reloc_desc {scalar_t__ type; size_t insn_idx; int /*<<< orphan*/  text_off; } ;
struct bpf_program {scalar_t__ idx; int main_prog_cnt; size_t insns_cnt; struct bpf_insn* insns; int /*<<< orphan*/  section_name; } ;
struct TYPE_2__ {scalar_t__ text_shndx; } ;
struct bpf_object {scalar_t__ btf_ext; TYPE_1__ efile; } ;
struct bpf_insn {int /*<<< orphan*/  imm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int LIBBPF_ERRNO__RELOC ; 
 scalar_t__ RELO_CALL ; 
 struct bpf_program* bpf_object__find_prog_by_idx (struct bpf_object*,scalar_t__) ; 
 int bpf_program_reloc_btf_ext (struct bpf_program*,struct bpf_object*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memcpy (struct bpf_insn*,struct bpf_insn*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 
 struct bpf_insn* reallocarray (struct bpf_insn*,size_t,int) ; 

__attribute__((used)) static int
bpf_program__reloc_text(struct bpf_program *prog, struct bpf_object *obj,
			struct reloc_desc *relo)
{
	struct bpf_insn *insn, *new_insn;
	struct bpf_program *text;
	size_t new_cnt;
	int err;

	if (relo->type != RELO_CALL)
		return -LIBBPF_ERRNO__RELOC;

	if (prog->idx == obj->efile.text_shndx) {
		pr_warning("relo in .text insn %d into off %d\n",
			   relo->insn_idx, relo->text_off);
		return -LIBBPF_ERRNO__RELOC;
	}

	if (prog->main_prog_cnt == 0) {
		text = bpf_object__find_prog_by_idx(obj, obj->efile.text_shndx);
		if (!text) {
			pr_warning("no .text section found yet relo into text exist\n");
			return -LIBBPF_ERRNO__RELOC;
		}
		new_cnt = prog->insns_cnt + text->insns_cnt;
		new_insn = reallocarray(prog->insns, new_cnt, sizeof(*insn));
		if (!new_insn) {
			pr_warning("oom in prog realloc\n");
			return -ENOMEM;
		}

		if (obj->btf_ext) {
			err = bpf_program_reloc_btf_ext(prog, obj,
							text->section_name,
							prog->insns_cnt);
			if (err)
				return err;
		}

		memcpy(new_insn + prog->insns_cnt, text->insns,
		       text->insns_cnt * sizeof(*insn));
		prog->insns = new_insn;
		prog->main_prog_cnt = prog->insns_cnt;
		prog->insns_cnt = new_cnt;
		pr_debug("added %zd insn from %s to prog %s\n",
			 text->insns_cnt, text->section_name,
			 prog->section_name);
	}
	insn = &prog->insns[relo->insn_idx];
	insn->imm += prog->main_prog_cnt - relo->insn_idx;
	return 0;
}