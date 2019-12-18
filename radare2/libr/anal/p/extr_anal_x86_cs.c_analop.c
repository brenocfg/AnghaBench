#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_28__ {int size; TYPE_2__* detail; int /*<<< orphan*/  id; scalar_t__* op_str; int /*<<< orphan*/  mnemonic; } ;
typedef  TYPE_3__ cs_insn ;
struct TYPE_30__ {int bits; } ;
struct TYPE_29__ {int cycles; int size; int /*<<< orphan*/  family; int /*<<< orphan*/  opex; scalar_t__ prefix; int /*<<< orphan*/  cond; int /*<<< orphan*/  id; scalar_t__ nopcode; int /*<<< orphan*/  mnemonic; int /*<<< orphan*/  type; int /*<<< orphan*/  esil; scalar_t__ delay; int /*<<< orphan*/ * dst; int /*<<< orphan*/ ** src; void* val; void* ptr; void* fail; void* jump; } ;
struct TYPE_26__ {int* prefix; int* opcode; } ;
struct TYPE_27__ {TYPE_1__ x86; } ;
typedef  int RAnalOpMask ;
typedef  TYPE_4__ RAnalOp ;
typedef  TYPE_5__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ARCH_X86 ; 
 int CS_ERR_OK ; 
 int CS_MODE_16 ; 
 int CS_MODE_32 ; 
 int CS_MODE_64 ; 
 int /*<<< orphan*/  CS_OPT_DETAIL ; 
 int /*<<< orphan*/  CS_OPT_ON ; 
 int /*<<< orphan*/  R_ANAL_OP_FAMILY_CPU ; 
 int /*<<< orphan*/  R_ANAL_OP_FAMILY_PRIV ; 
 int /*<<< orphan*/  R_ANAL_OP_FAMILY_THREAD ; 
 int R_ANAL_OP_MASK_DISASM ; 
 int R_ANAL_OP_MASK_ESIL ; 
 int R_ANAL_OP_MASK_OPEX ; 
 int R_ANAL_OP_MASK_VAL ; 
 scalar_t__ R_ANAL_OP_PREFIX_LOCK ; 
 scalar_t__ R_ANAL_OP_PREFIX_REP ; 
 scalar_t__ R_ANAL_OP_PREFIX_REPNE ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_ILL ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_NULL ; 
 void* UT64_MAX ; 
 int /*<<< orphan*/  X86_GRP_PRIVILEGE ; 
#define  X86_PREFIX_LOCK 130 
#define  X86_PREFIX_REP 129 
#define  X86_PREFIX_REPNE 128 
 int /*<<< orphan*/  anop (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,scalar_t__*,TYPE_3__*) ; 
 int /*<<< orphan*/  anop_esil (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,scalar_t__*,TYPE_3__*) ; 
 int /*<<< orphan*/  cond_x862r2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_close (scalar_t__*) ; 
 int cs_disasm (scalar_t__,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int,TYPE_3__**) ; 
 int cs_disasm_iter (scalar_t__,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  cs_free (TYPE_3__*,int) ; 
 scalar_t__ cs_insn_group (scalar_t__,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ cs_len_prefix_opcode (int*) ; 
 TYPE_3__* cs_malloc (scalar_t__) ; 
 int cs_open (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  cs_option (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ handle ; 
 int /*<<< orphan*/  memset (TYPE_4__*,char,int) ; 
 int /*<<< orphan*/  op_fillval (TYPE_5__*,TYPE_4__*,scalar_t__*,TYPE_3__*) ; 
 int /*<<< orphan*/  opex (int /*<<< orphan*/ *,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  r_str_newf (char*,int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  r_strbuf_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_opdir (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static int analop(RAnal *a, RAnalOp *op, ut64 addr, const ut8 *buf, int len, RAnalOpMask mask) {
	static int omode = 0;
#if USE_ITER_API
	static
#endif
	cs_insn *insn = NULL;
	int mode = (a->bits==64)? CS_MODE_64:
		(a->bits==32)? CS_MODE_32:
		(a->bits==16)? CS_MODE_16: 0;
	int n, ret;

	if (handle && mode != omode) {
		if (handle != 0) {
			cs_close (&handle);
			handle = 0;
		}
	}
	omode = mode;
	if (handle == 0) {
		ret = cs_open (CS_ARCH_X86, mode, &handle);
		if (ret != CS_ERR_OK) {
			handle = 0;
			return 0;
		}
	}
	memset (op, '\0', sizeof (RAnalOp));
	op->cycles = 1; // aprox
	op->type = R_ANAL_OP_TYPE_NULL;
	op->jump = UT64_MAX;
	op->fail = UT64_MAX;
	op->ptr = op->val = UT64_MAX;
	op->src[0] = NULL;
	op->src[1] = NULL;
	op->dst = NULL;
	op->size = 0;
	op->delay = 0;
	r_strbuf_init (&op->esil);
	cs_option (handle, CS_OPT_DETAIL, CS_OPT_ON);
	// capstone-next
#if USE_ITER_API
	{
		ut64 naddr = addr;
		size_t size = len;
		if (!insn) {
			insn = cs_malloc (handle);
		}
		n = cs_disasm_iter (handle, (const uint8_t**)&buf,
			&size, (uint64_t*)&naddr, insn);
	}
#else
	n = cs_disasm (handle, (const ut8*)buf, len, addr, 1, &insn);
#endif
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
		// int rs = a->bits / 8;
		//const char *pc = (a->bits==16)?"ip": (a->bits==32)?"eip":"rip";
		//const char *sp = (a->bits==16)?"sp": (a->bits==32)?"esp":"rsp";
		//const char *bp = (a->bits==16)?"bp": (a->bits==32)?"ebp":"rbp";
		op->nopcode = cs_len_prefix_opcode (insn->detail->x86.prefix)
			+ cs_len_prefix_opcode (insn->detail->x86.opcode);
		op->size = insn->size;
		op->id = insn->id;
		op->family = R_ANAL_OP_FAMILY_CPU; // almost everything is CPU
		op->prefix = 0;
		op->cond = cond_x862r2 (insn->id);
		switch (insn->detail->x86.prefix[0]) {
		case X86_PREFIX_REPNE:
			op->prefix |= R_ANAL_OP_PREFIX_REPNE;
			break;
		case X86_PREFIX_REP:
			op->prefix |= R_ANAL_OP_PREFIX_REP;
			break;
		case X86_PREFIX_LOCK:
			op->prefix |= R_ANAL_OP_PREFIX_LOCK;
			op->family = R_ANAL_OP_FAMILY_THREAD; // XXX ?
			break;
		}
		anop (a, op, addr, buf, len, &handle, insn);
		set_opdir (op, insn);
		if (mask & R_ANAL_OP_MASK_ESIL) {
			anop_esil (a, op, addr, buf, len, &handle, insn);
		}
		if (mask & R_ANAL_OP_MASK_OPEX) {
			opex (&op->opex, handle, insn);
		}
		if (mask & R_ANAL_OP_MASK_VAL) {
			op_fillval (a, op, &handle, insn);
		}
	}
//#if X86_GRP_PRIVILEGE>0
	if (insn) {
#if HAVE_CSGRP_PRIVILEGE
		if (cs_insn_group (handle, insn, X86_GRP_PRIVILEGE)) {
			op->family = R_ANAL_OP_FAMILY_PRIV;
		}
#endif
#if !USE_ITER_API
		cs_free (insn, n);
#endif
	}
	//cs_close (&handle);
	return op->size;
}