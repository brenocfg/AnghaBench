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
struct bpf_insn {int code; } ;

/* Variables and functions */
 int BPF_DW ; 
 int BPF_IMM ; 
 int BPF_LD ; 
 int /*<<< orphan*/  fprint_hex (int /*<<< orphan*/ ,struct bpf_insn*,int,char*) ; 
 int /*<<< orphan*/  print_bpf_insn (struct bpf_insn_cbs const*,struct bpf_insn*,int) ; 
 int /*<<< orphan*/  print_call ; 
 int /*<<< orphan*/  print_imm ; 
 int /*<<< orphan*/  print_insn ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

void dump_xlated_plain(struct dump_data *dd, void *buf, unsigned int len,
		       bool opcodes)
{
	const struct bpf_insn_cbs cbs = {
		.cb_print	= print_insn,
		.cb_call	= print_call,
		.cb_imm		= print_imm,
		.private_data	= dd,
	};
	struct bpf_insn *insn = buf;
	bool double_insn = false;
	unsigned int i;

	for (i = 0; i < len / sizeof(*insn); i++) {
		if (double_insn) {
			double_insn = false;
			continue;
		}

		double_insn = insn[i].code == (BPF_LD | BPF_IMM | BPF_DW);

		printf("% 4d: ", i);
		print_bpf_insn(&cbs, insn + i, true);

		if (opcodes) {
			printf("       ");
			fprint_hex(stdout, insn + i, 8, " ");
			if (double_insn && i < len - 1) {
				printf(" ");
				fprint_hex(stdout, insn + i + 1, 8, " ");
			}
			printf("\n");
		}
	}
}