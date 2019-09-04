#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct unwind_hint {scalar_t__ type; int sp_reg; int /*<<< orphan*/  end; int /*<<< orphan*/  sp_offset; } ;
struct section {int len; TYPE_1__* data; struct section* rela; } ;
struct rela {int /*<<< orphan*/  addend; TYPE_2__* sym; } ;
struct objtool_file {int hints; int /*<<< orphan*/  elf; } ;
struct cfi_reg {int /*<<< orphan*/  offset; int /*<<< orphan*/  base; } ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  end; struct cfi_reg cfa; } ;
struct instruction {int save; int restore; int hint; TYPE_3__ state; int /*<<< orphan*/  offset; int /*<<< orphan*/  sec; } ;
struct TYPE_5__ {int /*<<< orphan*/  sec; } ;
struct TYPE_4__ {scalar_t__ d_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFI_BP ; 
 int /*<<< orphan*/  CFI_DI ; 
 int /*<<< orphan*/  CFI_DX ; 
 int /*<<< orphan*/  CFI_R10 ; 
 int /*<<< orphan*/  CFI_R13 ; 
 int /*<<< orphan*/  CFI_SP ; 
 int /*<<< orphan*/  CFI_SP_INDIRECT ; 
 int /*<<< orphan*/  CFI_UNDEFINED ; 
#define  ORC_REG_BP 135 
#define  ORC_REG_DI 134 
#define  ORC_REG_DX 133 
#define  ORC_REG_R10 132 
#define  ORC_REG_R13 131 
#define  ORC_REG_SP 130 
#define  ORC_REG_SP_INDIRECT 129 
#define  ORC_REG_UNDEFINED 128 
 scalar_t__ UNWIND_HINT_TYPE_RESTORE ; 
 scalar_t__ UNWIND_HINT_TYPE_SAVE ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  WARN_FUNC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct instruction* find_insn (struct objtool_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rela* find_rela_by_dest (struct section*,int) ; 
 struct section* find_section_by_name (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int read_unwind_hints(struct objtool_file *file)
{
	struct section *sec, *relasec;
	struct rela *rela;
	struct unwind_hint *hint;
	struct instruction *insn;
	struct cfi_reg *cfa;
	int i;

	sec = find_section_by_name(file->elf, ".discard.unwind_hints");
	if (!sec)
		return 0;

	relasec = sec->rela;
	if (!relasec) {
		WARN("missing .rela.discard.unwind_hints section");
		return -1;
	}

	if (sec->len % sizeof(struct unwind_hint)) {
		WARN("struct unwind_hint size mismatch");
		return -1;
	}

	file->hints = true;

	for (i = 0; i < sec->len / sizeof(struct unwind_hint); i++) {
		hint = (struct unwind_hint *)sec->data->d_buf + i;

		rela = find_rela_by_dest(sec, i * sizeof(*hint));
		if (!rela) {
			WARN("can't find rela for unwind_hints[%d]", i);
			return -1;
		}

		insn = find_insn(file, rela->sym->sec, rela->addend);
		if (!insn) {
			WARN("can't find insn for unwind_hints[%d]", i);
			return -1;
		}

		cfa = &insn->state.cfa;

		if (hint->type == UNWIND_HINT_TYPE_SAVE) {
			insn->save = true;
			continue;

		} else if (hint->type == UNWIND_HINT_TYPE_RESTORE) {
			insn->restore = true;
			insn->hint = true;
			continue;
		}

		insn->hint = true;

		switch (hint->sp_reg) {
		case ORC_REG_UNDEFINED:
			cfa->base = CFI_UNDEFINED;
			break;
		case ORC_REG_SP:
			cfa->base = CFI_SP;
			break;
		case ORC_REG_BP:
			cfa->base = CFI_BP;
			break;
		case ORC_REG_SP_INDIRECT:
			cfa->base = CFI_SP_INDIRECT;
			break;
		case ORC_REG_R10:
			cfa->base = CFI_R10;
			break;
		case ORC_REG_R13:
			cfa->base = CFI_R13;
			break;
		case ORC_REG_DI:
			cfa->base = CFI_DI;
			break;
		case ORC_REG_DX:
			cfa->base = CFI_DX;
			break;
		default:
			WARN_FUNC("unsupported unwind_hint sp base reg %d",
				  insn->sec, insn->offset, hint->sp_reg);
			return -1;
		}

		cfa->offset = hint->sp_offset;
		insn->state.type = hint->type;
		insn->state.end = hint->end;
	}

	return 0;
}