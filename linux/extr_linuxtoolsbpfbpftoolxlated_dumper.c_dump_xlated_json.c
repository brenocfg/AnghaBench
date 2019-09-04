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
typedef  int /*<<< orphan*/  uint8_t ;
struct dump_data {int dummy; } ;
struct bpf_insn_cbs {struct dump_data* private_data; int /*<<< orphan*/  cb_imm; int /*<<< orphan*/  cb_call; int /*<<< orphan*/  cb_print; } ;
struct bpf_insn {int code; int src_reg; int dst_reg; int /*<<< orphan*/  imm; int /*<<< orphan*/  off; } ;

/* Variables and functions */
 int BPF_DW ; 
 int BPF_IMM ; 
 int BPF_LD ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_end_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_end_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jsonw_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  jsonw_start_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_start_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_bpf_insn (struct bpf_insn_cbs const*,struct bpf_insn*,int) ; 
 int /*<<< orphan*/  print_call ; 
 int /*<<< orphan*/  print_hex_data_json (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_imm ; 
 int /*<<< orphan*/  print_insn_json ; 

void dump_xlated_json(struct dump_data *dd, void *buf, unsigned int len,
		      bool opcodes)
{
	const struct bpf_insn_cbs cbs = {
		.cb_print	= print_insn_json,
		.cb_call	= print_call,
		.cb_imm		= print_imm,
		.private_data	= dd,
	};
	struct bpf_insn *insn = buf;
	bool double_insn = false;
	unsigned int i;

	jsonw_start_array(json_wtr);
	for (i = 0; i < len / sizeof(*insn); i++) {
		if (double_insn) {
			double_insn = false;
			continue;
		}
		double_insn = insn[i].code == (BPF_LD | BPF_IMM | BPF_DW);

		jsonw_start_object(json_wtr);
		jsonw_name(json_wtr, "disasm");
		print_bpf_insn(&cbs, insn + i, true);

		if (opcodes) {
			jsonw_name(json_wtr, "opcodes");
			jsonw_start_object(json_wtr);

			jsonw_name(json_wtr, "code");
			jsonw_printf(json_wtr, "\"0x%02hhx\"", insn[i].code);

			jsonw_name(json_wtr, "src_reg");
			jsonw_printf(json_wtr, "\"0x%hhx\"", insn[i].src_reg);

			jsonw_name(json_wtr, "dst_reg");
			jsonw_printf(json_wtr, "\"0x%hhx\"", insn[i].dst_reg);

			jsonw_name(json_wtr, "off");
			print_hex_data_json((uint8_t *)(&insn[i].off), 2);

			jsonw_name(json_wtr, "imm");
			if (double_insn && i < len - 1)
				print_hex_data_json((uint8_t *)(&insn[i].imm),
						    12);
			else
				print_hex_data_json((uint8_t *)(&insn[i].imm),
						    4);
			jsonw_end_object(json_wtr);
		}
		jsonw_end_object(json_wtr);
	}
	jsonw_end_array(json_wtr);
}