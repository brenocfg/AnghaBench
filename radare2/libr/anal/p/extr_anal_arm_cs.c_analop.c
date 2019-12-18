#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  scalar_t__ csh ;
struct TYPE_26__ {int size; int /*<<< orphan*/  id; scalar_t__* op_str; int /*<<< orphan*/  mnemonic; } ;
typedef  TYPE_1__ cs_insn ;
struct TYPE_28__ {int bits; scalar_t__ cpu; scalar_t__ big_endian; } ;
struct TYPE_27__ {int size; int jump; int fail; int ptr; int val; int /*<<< orphan*/  opex; int /*<<< orphan*/  id; int /*<<< orphan*/  mnemonic; int /*<<< orphan*/  type; int /*<<< orphan*/  esil; scalar_t__ refptr; int /*<<< orphan*/  addr; scalar_t__ delay; int /*<<< orphan*/  stackop; } ;
typedef  int RAnalOpMask ;
typedef  TYPE_2__ RAnalOp ;
typedef  TYPE_3__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ARCH_ARM ; 
 int /*<<< orphan*/  CS_ARCH_ARM64 ; 
 int CS_ERR_OK ; 
 int CS_MODE_ARM ; 
 int CS_MODE_BIG_ENDIAN ; 
 int CS_MODE_LITTLE_ENDIAN ; 
 int CS_MODE_MCLASS ; 
 int CS_MODE_THUMB ; 
 int /*<<< orphan*/  CS_OPT_DETAIL ; 
 int /*<<< orphan*/  CS_OPT_ON ; 
 int R_ANAL_OP_MASK_DISASM ; 
 int R_ANAL_OP_MASK_ESIL ; 
 int R_ANAL_OP_MASK_OPEX ; 
 int R_ANAL_OP_MASK_VAL ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_ILL ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_NULL ; 
 int /*<<< orphan*/  R_ANAL_STACK_NULL ; 
 int /*<<< orphan*/  analop64_esil (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,scalar_t__*,TYPE_1__*) ; 
 int /*<<< orphan*/  analop_esil (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,scalar_t__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  anop32 (TYPE_3__*,scalar_t__,TYPE_2__*,TYPE_1__*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  anop64 (scalar_t__,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  cs_close (scalar_t__*) ; 
 int cs_disasm (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,TYPE_1__**) ; 
 int /*<<< orphan*/  cs_free (TYPE_1__*,int) ; 
 int cs_open (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  cs_option (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hackyArmAnal (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  op_fillval (TYPE_2__*,scalar_t__,TYPE_1__*,int) ; 
 int /*<<< orphan*/  opex (int /*<<< orphan*/ *,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  opex64 (int /*<<< orphan*/ *,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  r_str_newf (char*,int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  r_strbuf_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_opdir (TYPE_2__*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 scalar_t__ strstr (scalar_t__,char*) ; 

__attribute__((used)) static int analop(RAnal *a, RAnalOp *op, ut64 addr, const ut8 *buf, int len, RAnalOpMask mask) {
	static csh handle = 0;
	static int omode = -1;
	static int obits = 32;
	cs_insn *insn = NULL;
	int mode = (a->bits==16)? CS_MODE_THUMB: CS_MODE_ARM;
	int n, ret;
	mode |= (a->big_endian)? CS_MODE_BIG_ENDIAN: CS_MODE_LITTLE_ENDIAN;
	if (a->cpu && strstr (a->cpu, "cortex")) {
		mode |= CS_MODE_MCLASS;
	}

	if (mode != omode || a->bits != obits) {
		cs_close (&handle);
		handle = 0; // unnecessary
		omode = mode;
		obits = a->bits;
	}
	op->type = R_ANAL_OP_TYPE_NULL; // SHOULD BE ILL but this makes some stuff to fail
	op->size = (a->bits==16)? 2: 4;
	op->stackop = R_ANAL_STACK_NULL;
	op->delay = 0;
	op->jump = op->fail = -1;
	op->addr = addr;
	op->ptr = op->val = -1;
	op->refptr = 0;
	r_strbuf_init (&op->esil);
	if (handle == 0) {
		ret = (a->bits == 64)?
			cs_open (CS_ARCH_ARM64, mode, &handle):
			cs_open (CS_ARCH_ARM, mode, &handle);
		cs_option (handle, CS_OPT_DETAIL, CS_OPT_ON);
		if (ret != CS_ERR_OK) {
			handle = 0;
			return -1;
		}
	}
	int haa = hackyArmAnal (a, op, buf, len);
	if (haa > 0) {
		return haa;
	}

	n = cs_disasm (handle, (ut8*)buf, len, addr, 1, &insn);
	if (n < 1) {
		op->type = R_ANAL_OP_TYPE_ILL;
		if (mask & R_ANAL_OP_MASK_DISASM) {
			op->mnemonic = strdup ("invalid");
		}
	} else {
		if (mask & R_ANAL_OP_MASK_DISASM) {
			op->mnemonic = r_str_newf ("%s%s%s",
				insn->mnemonic,
				insn->op_str[0]?" ":"",
				insn->op_str);
		}
		//bool thumb = cs_insn_group (handle, insn, ARM_GRP_THUMB);
		bool thumb = a->bits == 16;
		op->size = insn->size;
		op->id = insn->id;
		if (a->bits == 64) {
			anop64 (handle, op, insn);
			if (mask & R_ANAL_OP_MASK_OPEX) {
				opex64 (&op->opex, handle, insn);
			}
			if (mask & R_ANAL_OP_MASK_ESIL) {
				analop64_esil (a, op, addr, buf, len, &handle, insn);
			}
		} else {
			anop32 (a, handle, op, insn, thumb, (ut8*)buf, len);
			if (mask & R_ANAL_OP_MASK_OPEX) {
				opex (&op->opex, handle, insn);
			}
			if (mask & R_ANAL_OP_MASK_ESIL) {
				analop_esil (a, op, addr, buf, len, &handle, insn, thumb);
			}
		}
		set_opdir (op);
		if (mask & R_ANAL_OP_MASK_VAL) {
			op_fillval (op, handle, insn, a->bits);
		}
		cs_free (insn, n);
	}
//		cs_close (&handle);
	return op->size;
}