#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_9__ {scalar_t__ size; scalar_t__* op_str; int /*<<< orphan*/  mnemonic; } ;
typedef  TYPE_1__ cs_insn ;
struct TYPE_11__ {int /*<<< orphan*/  pc; } ;
struct TYPE_10__ {scalar_t__ size; } ;
typedef  TYPE_2__ RAsmOp ;
typedef  TYPE_3__ RAsm ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ARCH_SYSZ ; 
 int CS_MODE_BIG_ENDIAN ; 
 int /*<<< orphan*/  CS_OPT_DETAIL ; 
 int /*<<< orphan*/  CS_OPT_OFF ; 
 scalar_t__ cd ; 
 int /*<<< orphan*/  cs_close (scalar_t__*) ; 
 int cs_disasm (scalar_t__,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int,TYPE_1__**) ; 
 int /*<<< orphan*/  cs_free (TYPE_1__*,int) ; 
 int cs_open (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  cs_option (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  r_asm_op_set_asm (TYPE_2__*,char*) ; 
 char* sdb_fmt (char*,int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 scalar_t__ strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static int disassemble(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	static int omode = 0;
	int mode, n, ret;
	ut64 off = a->pc;
	cs_insn* insn = NULL;
	mode = CS_MODE_BIG_ENDIAN;
	if (cd && mode != omode) {
		cs_close (&cd);
		cd = 0;
	}
	op->size = 0;
	omode = mode;
	if (cd == 0) {
		ret = cs_open (CS_ARCH_SYSZ, mode, &cd);
		if (ret) {
			return 0;
		}
		cs_option (cd, CS_OPT_DETAIL, CS_OPT_OFF);
	}
	n = cs_disasm (cd, (const ut8*)buf, len, off, 1, &insn);
	if (n>0) {
		if (insn->size>0) {
			op->size = insn->size;
			char *buf_asm = sdb_fmt ("%s%s%s",
					insn->mnemonic, insn->op_str[0]?" ": "",
					insn->op_str);
			char *ptrstr = strstr (buf_asm, "ptr ");
			if (ptrstr) {
				memmove (ptrstr, ptrstr + 4, strlen (ptrstr + 4) + 1);
			}
			r_asm_op_set_asm (op, buf_asm);
		}
		cs_free (insn, n);
	}
	return op->size;
}