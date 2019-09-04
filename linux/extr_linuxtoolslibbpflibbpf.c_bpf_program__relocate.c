#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bpf_program {int nr_reloc; TYPE_2__* reloc_desc; int /*<<< orphan*/  section_name; scalar_t__ insns_cnt; struct bpf_insn* insns; } ;
struct bpf_object {TYPE_1__* maps; } ;
struct bpf_insn {int /*<<< orphan*/  imm; int /*<<< orphan*/  src_reg; } ;
struct TYPE_5__ {scalar_t__ type; int insn_idx; int map_idx; } ;
struct TYPE_4__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PSEUDO_MAP_FD ; 
 int LIBBPF_ERRNO__RELOC ; 
 scalar_t__ RELO_LD64 ; 
 int bpf_program__reloc_text (struct bpf_program*,struct bpf_object*,TYPE_2__*) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_2__**) ; 

__attribute__((used)) static int
bpf_program__relocate(struct bpf_program *prog, struct bpf_object *obj)
{
	int i, err;

	if (!prog || !prog->reloc_desc)
		return 0;

	for (i = 0; i < prog->nr_reloc; i++) {
		if (prog->reloc_desc[i].type == RELO_LD64) {
			struct bpf_insn *insns = prog->insns;
			int insn_idx, map_idx;

			insn_idx = prog->reloc_desc[i].insn_idx;
			map_idx = prog->reloc_desc[i].map_idx;

			if (insn_idx >= (int)prog->insns_cnt) {
				pr_warning("relocation out of range: '%s'\n",
					   prog->section_name);
				return -LIBBPF_ERRNO__RELOC;
			}
			insns[insn_idx].src_reg = BPF_PSEUDO_MAP_FD;
			insns[insn_idx].imm = obj->maps[map_idx].fd;
		} else {
			err = bpf_program__reloc_text(prog, obj,
						      &prog->reloc_desc[i]);
			if (err)
				return err;
		}
	}

	zfree(&prog->reloc_desc);
	prog->nr_reloc = 0;
	return 0;
}