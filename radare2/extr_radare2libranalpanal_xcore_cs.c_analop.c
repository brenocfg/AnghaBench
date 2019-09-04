#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  scalar_t__ csh ;
struct TYPE_10__ {int size; int id; } ;
typedef  TYPE_1__ cs_insn ;
struct TYPE_13__ {int /*<<< orphan*/  imm; } ;
struct TYPE_12__ {int /*<<< orphan*/  cpu; } ;
struct TYPE_11__ {int size; int id; void* type; int /*<<< orphan*/  jump; int /*<<< orphan*/  opex; int /*<<< orphan*/  esil; scalar_t__ delay; } ;
typedef  int RAnalOpMask ;
typedef  TYPE_2__ RAnalOp ;
typedef  TYPE_3__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ARCH_XCORE ; 
 int CS_ERR_OK ; 
 int CS_MODE_BIG_ENDIAN ; 
 int CS_MODE_V9 ; 
 int /*<<< orphan*/  CS_OPT_DETAIL ; 
 int /*<<< orphan*/  CS_OPT_ON ; 
 TYPE_9__ INSOP (int /*<<< orphan*/ ) ; 
 int R_ANAL_OP_MASK_OPEX ; 
 void* R_ANAL_OP_TYPE_ADD ; 
 void* R_ANAL_OP_TYPE_CALL ; 
 void* R_ANAL_OP_TYPE_ILL ; 
 void* R_ANAL_OP_TYPE_NULL ; 
 void* R_ANAL_OP_TYPE_RET ; 
 void* R_ANAL_OP_TYPE_SUB ; 
#define  XCORE_INS_ADD 145 
#define  XCORE_INS_BF 144 
#define  XCORE_INS_BL 143 
#define  XCORE_INS_BLA 142 
#define  XCORE_INS_BLAT 141 
#define  XCORE_INS_BRU 140 
#define  XCORE_INS_BT 139 
#define  XCORE_INS_BU 138 
#define  XCORE_INS_DCALL 137 
#define  XCORE_INS_DRET 136 
#define  XCORE_INS_ECALLF 135 
#define  XCORE_INS_ECALLT 134 
#define  XCORE_INS_KCALL 133 
#define  XCORE_INS_KRET 132 
#define  XCORE_INS_LADD 131 
#define  XCORE_INS_LSUB 130 
#define  XCORE_INS_RETSP 129 
#define  XCORE_INS_SUB 128 
 int /*<<< orphan*/  cs_close (scalar_t__*) ; 
 int cs_disasm (scalar_t__,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int,TYPE_1__**) ; 
 int /*<<< orphan*/  cs_free (TYPE_1__*,int) ; 
 int cs_open (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  cs_option (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opex (int /*<<< orphan*/ *,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  r_strbuf_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int analop(RAnal *a, RAnalOp *op, ut64 addr, const ut8 *buf, int len, RAnalOpMask mask) {
	static csh handle = 0;
	static int omode = 0;
	cs_insn *insn;
	int mode, n, ret;
	mode = CS_MODE_BIG_ENDIAN;
	if (!strcmp (a->cpu, "v9")) {
		mode |= CS_MODE_V9;
	}
	if (mode != omode) {
		if (handle) {
			cs_close (&handle);
			handle = 0;
		}
		omode = mode;
	}
	if (handle == 0) {
		ret = cs_open (CS_ARCH_XCORE, mode, &handle);
		if (ret != CS_ERR_OK) {
			return -1;
		}
		cs_option (handle, CS_OPT_DETAIL, CS_OPT_ON);
	}
	op->type = R_ANAL_OP_TYPE_NULL;
	op->size = 0;
	op->delay = 0;
	r_strbuf_init (&op->esil);
	// capstone-next
	n = cs_disasm (handle, (const ut8*)buf, len, addr, 1, &insn);
	if (n < 1) {
		op->type = R_ANAL_OP_TYPE_ILL;
	} else {
		if (mask & R_ANAL_OP_MASK_OPEX) {
			opex (&op->opex, handle, insn);
		}
		op->size = insn->size;
		op->id = insn->id;
		switch (insn->id) {
		case XCORE_INS_DRET:
		case XCORE_INS_KRET:
		case XCORE_INS_RETSP:
			op->type = R_ANAL_OP_TYPE_RET;
			break;
		case XCORE_INS_DCALL:
		case XCORE_INS_KCALL:
		case XCORE_INS_ECALLF:
		case XCORE_INS_ECALLT:
			op->type = R_ANAL_OP_TYPE_CALL;
			op->jump = INSOP(0).imm;
			break;
		/* ??? */
		case XCORE_INS_BL:
		case XCORE_INS_BLA:
		case XCORE_INS_BLAT:
		case XCORE_INS_BT:
		case XCORE_INS_BF:
		case XCORE_INS_BU:
		case XCORE_INS_BRU:
			op->type = R_ANAL_OP_TYPE_CALL;
			op->jump = INSOP(0).imm;
			break;
		case XCORE_INS_SUB:
		case XCORE_INS_LSUB:
			op->type = R_ANAL_OP_TYPE_SUB;
			break;
		case XCORE_INS_ADD:
		case XCORE_INS_LADD:
			op->type = R_ANAL_OP_TYPE_ADD;
			break;
		}
		cs_free (insn, n);
	}
	//	cs_close (&handle);
	return op->size;
}