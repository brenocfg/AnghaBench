#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct disassemble_info {char* disassembler_options; int endian; int /*<<< orphan*/  stream; int /*<<< orphan*/ * fprintf_func; int /*<<< orphan*/ * print_address_func; int /*<<< orphan*/ * memory_error_func; int /*<<< orphan*/ * symbol_at_address_func; int /*<<< orphan*/ * read_memory_func; int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
struct TYPE_6__ {int bits; scalar_t__ syntax; scalar_t__* cpu; int /*<<< orphan*/  big_endian; int /*<<< orphan*/  pc; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/  buf_asm; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  TYPE_2__ RAsm ;

/* Variables and functions */
 int /*<<< orphan*/  Offset ; 
 scalar_t__ R_ASM_SYNTAX_ATT ; 
 int /*<<< orphan*/  R_MIN (int,int) ; 
 int /*<<< orphan*/ * buf_global ; 
 int /*<<< orphan*/  bytes ; 
 int /*<<< orphan*/  cris_buffer_read_memory ; 
 int /*<<< orphan*/  cris_parse_disassembler_options (struct disassemble_info*,int) ; 
 int /*<<< orphan*/  generic_fprintf_func ; 
 int /*<<< orphan*/  generic_print_address_func ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_error_func ; 
 int /*<<< orphan*/  memset (struct disassemble_info*,char,int) ; 
 int print_insn_cris_with_register_prefix (int /*<<< orphan*/ ,struct disassemble_info*) ; 
 int print_insn_cris_without_register_prefix (int /*<<< orphan*/ ,struct disassemble_info*) ; 
 int print_insn_crisv10_v32_with_register_prefix (int /*<<< orphan*/ ,struct disassemble_info*) ; 
 int print_insn_crisv10_v32_without_register_prefix (int /*<<< orphan*/ ,struct disassemble_info*) ; 
 int print_insn_crisv32_with_register_prefix (int /*<<< orphan*/ ,struct disassemble_info*) ; 
 int print_insn_crisv32_without_register_prefix (int /*<<< orphan*/ ,struct disassemble_info*) ; 
 int /*<<< orphan*/  r_strbuf_set (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strstr (scalar_t__*,char*) ; 
 int /*<<< orphan*/  symbol_at_address ; 

__attribute__((used)) static int disassemble(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	struct disassemble_info disasm_obj;
	int mode = 2;
	if (len < 4) {
		return -1;
	}
	buf_global = &op->buf_asm;
	Offset = a->pc;
	memcpy (bytes, buf, R_MIN (len, 8)); // TODO handle thumb

	/* prepare disassembler */
	memset (&disasm_obj, '\0', sizeof (struct disassemble_info));
	disasm_obj.disassembler_options=(a->bits==64)?"64":"";
	disasm_obj.buffer = bytes;
	disasm_obj.read_memory_func = &cris_buffer_read_memory;
	disasm_obj.symbol_at_address_func = &symbol_at_address;
	disasm_obj.memory_error_func = &memory_error_func;
	disasm_obj.print_address_func = &generic_print_address_func;
	disasm_obj.endian = !a->big_endian;
	disasm_obj.fprintf_func = &generic_fprintf_func;
	disasm_obj.stream = stdout;

	if (a->cpu && *a->cpu) {
		// enum cris_disass_family { cris_dis_v0_v10, cris_dis_common_v10_v32, cris_dis_v32 };
		// 0: v0-v10
		// 1: v10-v32
		// 2: v32
		mode = 0;
		if (strstr (a->cpu,  "v10")) {
			mode = 1;
		}
		if (strstr (a->cpu,  "v32")) {
			mode = 2;
		}
	} else {
		mode = 2;
	}
	(void)cris_parse_disassembler_options (&disasm_obj, mode);
	if (a->syntax == R_ASM_SYNTAX_ATT) {
		switch (mode) {
		case 0:
			op->size = print_insn_cris_with_register_prefix ((bfd_vma)Offset, &disasm_obj);
			break;
		case 1:
			op->size = print_insn_crisv10_v32_with_register_prefix ((bfd_vma)Offset, &disasm_obj);
			break;
		default:
			op->size = print_insn_crisv32_with_register_prefix ((bfd_vma)Offset, &disasm_obj);
			break;
		}
	} else {
		switch (mode) {
		case 0:
			op->size = print_insn_cris_without_register_prefix ((bfd_vma)Offset, &disasm_obj);
			break;
		case 1:
			op->size = print_insn_crisv10_v32_without_register_prefix ((bfd_vma)Offset, &disasm_obj);
			break;
		default:
			op->size = print_insn_crisv32_without_register_prefix ((bfd_vma)Offset, &disasm_obj);
			break;
		}
	}
	if (op->size == -1) {
		r_strbuf_set (&op->buf_asm, "(data)");
	}
	return op->size;
}