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
typedef  scalar_t__ u8 ;
struct func_node {int /*<<< orphan*/  bbs; struct bpf_insn* end; struct bpf_insn* start; } ;
struct bpf_insn {int off; int /*<<< orphan*/  code; } ;
struct bb_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ BPF_CALL ; 
 scalar_t__ BPF_EXIT ; 
 scalar_t__ BPF_JA ; 
 scalar_t__ BPF_OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct bb_node* func_append_bb (struct func_node*,struct bpf_insn*) ; 
 scalar_t__ is_jmp_insn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool func_partition_bb_head(struct func_node *func)
{
	struct bpf_insn *cur, *end;
	struct bb_node *bb;

	cur = func->start;
	end = func->end;
	INIT_LIST_HEAD(&func->bbs);
	bb = func_append_bb(func, cur);
	if (!bb)
		return true;

	for (; cur <= end; cur++) {
		if (is_jmp_insn(cur->code)) {
			u8 opcode = BPF_OP(cur->code);

			if (opcode == BPF_EXIT || opcode == BPF_CALL)
				continue;

			bb = func_append_bb(func, cur + cur->off + 1);
			if (!bb)
				return true;

			if (opcode != BPF_JA) {
				bb = func_append_bb(func, cur + 1);
				if (!bb)
					return true;
			}
		}
	}

	return false;
}