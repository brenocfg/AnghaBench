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
struct dump_data {int dummy; } ;
struct bpf_insn_cbs {struct dump_data* private_data; int /*<<< orphan*/  cb_imm; int /*<<< orphan*/  cb_call; int /*<<< orphan*/  cb_print; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_bpf_insn (struct bpf_insn_cbs const*,struct bpf_insn*,int) ; 
 int /*<<< orphan*/  print_call ; 
 int /*<<< orphan*/  print_imm ; 
 int /*<<< orphan*/  print_insn_for_graph ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void dump_xlated_for_graph(struct dump_data *dd, void *buf_start, void *buf_end,
			   unsigned int start_idx)
{
	const struct bpf_insn_cbs cbs = {
		.cb_print	= print_insn_for_graph,
		.cb_call	= print_call,
		.cb_imm		= print_imm,
		.private_data	= dd,
	};
	struct bpf_insn *insn_start = buf_start;
	struct bpf_insn *insn_end = buf_end;
	struct bpf_insn *cur = insn_start;

	for (; cur <= insn_end; cur++) {
		printf("% 4d: ", (int)(cur - insn_start + start_idx));
		print_bpf_insn(&cbs, cur, true);
		if (cur != insn_end)
			printf(" | ");
	}
}