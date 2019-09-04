#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_13__ {scalar_t__ size; scalar_t__* op_str; int /*<<< orphan*/  mnemonic; } ;
typedef  TYPE_1__ cs_insn ;
struct TYPE_15__ {int bits; scalar_t__ big_endian; scalar_t__ cpu; int /*<<< orphan*/  pc; } ;
struct TYPE_14__ {int size; } ;
typedef  TYPE_2__ RAsmOp ;
typedef  TYPE_3__ RAsm ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ARCH_PPC ; 
 int CS_ERR_OK ; 
 int CS_MODE_32 ; 
 int CS_MODE_64 ; 
 int CS_MODE_BIG_ENDIAN ; 
 int CS_MODE_LITTLE_ENDIAN ; 
 int /*<<< orphan*/  CS_OPT_DETAIL ; 
 int /*<<< orphan*/  CS_OPT_OFF ; 
 int /*<<< orphan*/  cs_close (scalar_t__*) ; 
 int cs_disasm (scalar_t__,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int,TYPE_1__**) ; 
 int /*<<< orphan*/  cs_free (TYPE_1__*,int) ; 
 int cs_open (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  cs_option (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int decompile_ps (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/  const*,int) ; 
 int decompile_vle (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ handle ; 
 int /*<<< orphan*/  r_asm_op_set_asm (TYPE_2__*,char const*) ; 
 char* sdb_fmt (char*,int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 scalar_t__ strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static int disassemble(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	static int omode = -1, obits = -1;
	int n, ret;
	ut64 off = a->pc;
	cs_insn* insn;
	int mode = (a->bits == 64) ? CS_MODE_64 : (a->bits == 32) ? CS_MODE_32 : 0;
	mode |= a->big_endian ? CS_MODE_BIG_ENDIAN : CS_MODE_LITTLE_ENDIAN;

	if (a->cpu && strncmp (a->cpu, "vle", 3) == 0) {
		// vle is big-endian only
		if (!a->big_endian) {
			return -1;
		}
		ret = decompile_vle (a, op, buf, len);
		if (ret >= 0) {
			return op->size;
		}
	} else if (a->cpu && strncmp (a->cpu, "ps", 2) == 0) {
		// libps is big-endian only
		if (!a->big_endian) {
			return -1;
		}
		ret = decompile_ps (a, op, buf, len);
		if (ret >= 0) {
			return op->size;
		}
	}
	if (mode != omode || a->bits != obits) {
		cs_close (&handle);
		handle = 0;
		omode = mode;
		obits = a->bits;
	}
	if (handle == 0) {
		ret = cs_open (CS_ARCH_PPC, mode, &handle);
		if (ret != CS_ERR_OK) {
			return -1;
		}
	}
	op->size = 4;
	cs_option (handle, CS_OPT_DETAIL, CS_OPT_OFF);
	n = cs_disasm (handle, (const ut8*) buf, len, off, 1, &insn);
	op->size = 4;
	if (n > 0 && insn->size > 0) {
		const char *opstr = sdb_fmt ("%s%s%s", insn->mnemonic,
			insn->op_str[0] ? " " : "", insn->op_str);
		r_asm_op_set_asm (op, opstr);
		cs_free (insn, n);
		return op->size;
	}
	r_asm_op_set_asm (op, "invalid");
	op->size = 4;
	cs_free (insn, n);
	return op->size;
}