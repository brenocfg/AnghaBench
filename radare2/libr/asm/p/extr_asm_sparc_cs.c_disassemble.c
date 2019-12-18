#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_10__ {int size; scalar_t__* op_str; int /*<<< orphan*/  mnemonic; } ;
typedef  TYPE_1__ cs_insn ;
struct TYPE_12__ {int /*<<< orphan*/  pc; scalar_t__ big_endian; scalar_t__* cpu; } ;
struct TYPE_11__ {int size; } ;
typedef  TYPE_2__ RAsmOp ;
typedef  TYPE_3__ RAsm ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ARCH_SPARC ; 
 int CS_MODE_BIG_ENDIAN ; 
 int CS_MODE_V9 ; 
 int /*<<< orphan*/  CS_OPT_DETAIL ; 
 int /*<<< orphan*/  CS_OPT_OFF ; 
 scalar_t__ cd ; 
 int /*<<< orphan*/  cs_close (scalar_t__*) ; 
 int cs_disasm (scalar_t__,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int,TYPE_1__**) ; 
 int /*<<< orphan*/  cs_free (TYPE_1__*,int) ; 
 int cs_open (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  cs_option (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_asm_op_set_asm (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  r_str_replace_char (char*,char,int /*<<< orphan*/ ) ; 
 char* sdb_fmt (char*,int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  strcmp (scalar_t__*,char*) ; 

__attribute__((used)) static int disassemble(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	cs_insn* insn;
	int n = -1, ret = -1;
	int mode = CS_MODE_BIG_ENDIAN;
	if (a->cpu && *a->cpu) {
		if (!strcmp (a->cpu, "v9")) {
			mode |= CS_MODE_V9;
		}
	}
	if (op) {
		memset (op, 0, sizeof (RAsmOp));
		op->size = 4;
	}
	if (cd != 0) {
		cs_close (&cd);
	}
	ret = cs_open (CS_ARCH_SPARC, mode, &cd);
	if (ret) {
		goto fin;
	}
	cs_option (cd, CS_OPT_DETAIL, CS_OPT_OFF);
	if (!op) {
		return 0;
	}
	if (a->big_endian) {
		n = cs_disasm (cd, buf, len, a->pc, 1, &insn);
	}
	if (n < 1) {
		r_asm_op_set_asm (op, "invalid");
		op->size = 4;
		ret = -1;
		goto beach;
	} else {
		ret = 4;
	}
	if (insn->size < 1) {
		goto beach;
	}
	op->size = insn->size;
	char *buf_asm = sdb_fmt ("%s%s%s",
		insn->mnemonic, insn->op_str[0]? " ": "",
		insn->op_str);
	r_str_replace_char (buf_asm, '%', 0);
	r_asm_op_set_asm (op, buf_asm);
	// TODO: remove the '$'<registername> in the string
	cs_free (insn, n);
	beach:
	// cs_close (&cd);
	fin:
	return ret;
}