#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct bpf_map_data {scalar_t__ elf_offset; int /*<<< orphan*/  fd; } ;
struct bpf_insn {int code; int /*<<< orphan*/  imm; int /*<<< orphan*/  src_reg; } ;
struct TYPE_9__ {int r_offset; int /*<<< orphan*/  r_info; } ;
struct TYPE_8__ {int sh_size; int sh_entsize; } ;
struct TYPE_7__ {scalar_t__ st_value; } ;
typedef  TYPE_1__ GElf_Sym ;
typedef  TYPE_2__ GElf_Shdr ;
typedef  TYPE_3__ GElf_Rel ;
typedef  int /*<<< orphan*/  Elf_Data ;

/* Variables and functions */
 int BPF_DW ; 
 int BPF_IMM ; 
 int BPF_LD ; 
 int /*<<< orphan*/  BPF_PSEUDO_MAP_FD ; 
 int /*<<< orphan*/  GELF_R_SYM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gelf_getrel (int /*<<< orphan*/ *,int,TYPE_3__*) ; 
 int /*<<< orphan*/  gelf_getsym (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,unsigned int,...) ; 

__attribute__((used)) static int parse_relo_and_apply(Elf_Data *data, Elf_Data *symbols,
				GElf_Shdr *shdr, struct bpf_insn *insn,
				struct bpf_map_data *maps, int nr_maps)
{
	int i, nrels;

	nrels = shdr->sh_size / shdr->sh_entsize;

	for (i = 0; i < nrels; i++) {
		GElf_Sym sym;
		GElf_Rel rel;
		unsigned int insn_idx;
		bool match = false;
		int j, map_idx;

		gelf_getrel(data, i, &rel);

		insn_idx = rel.r_offset / sizeof(struct bpf_insn);

		gelf_getsym(symbols, GELF_R_SYM(rel.r_info), &sym);

		if (insn[insn_idx].code != (BPF_LD | BPF_IMM | BPF_DW)) {
			printf("invalid relo for insn[%d].code 0x%x\n",
			       insn_idx, insn[insn_idx].code);
			return 1;
		}
		insn[insn_idx].src_reg = BPF_PSEUDO_MAP_FD;

		/* Match FD relocation against recorded map_data[] offset */
		for (map_idx = 0; map_idx < nr_maps; map_idx++) {
			if (maps[map_idx].elf_offset == sym.st_value) {
				match = true;
				break;
			}
		}
		if (match) {
			insn[insn_idx].imm = maps[map_idx].fd;
		} else {
			printf("invalid relo for insn[%d] no map_data match\n",
			       insn_idx);
			return 1;
		}
	}

	return 0;
}