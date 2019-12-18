#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut64 ;
typedef  int /*<<< orphan*/  csh ;
struct TYPE_8__ {int size; int id; } ;
typedef  TYPE_1__ cs_insn ;
struct TYPE_10__ {int /*<<< orphan*/  imm; } ;
struct TYPE_9__ {int size; int fail; int /*<<< orphan*/  jump; void* type; int /*<<< orphan*/  opex; int /*<<< orphan*/  esil; scalar_t__ delay; } ;
typedef  int RAnalOpMask ;
typedef  TYPE_2__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ARCH_SYSZ ; 
 int CS_ERR_OK ; 
 int CS_MODE_BIG_ENDIAN ; 
 int /*<<< orphan*/  CS_OPT_DETAIL ; 
 int /*<<< orphan*/  CS_OPT_ON ; 
 TYPE_7__ INSOP (int /*<<< orphan*/ ) ; 
 int R_ANAL_OP_MASK_OPEX ; 
 void* R_ANAL_OP_TYPE_CALL ; 
 void* R_ANAL_OP_TYPE_CJMP ; 
 void* R_ANAL_OP_TYPE_ILL ; 
 void* R_ANAL_OP_TYPE_JMP ; 
 void* R_ANAL_OP_TYPE_NULL ; 
#define  SYSZ_INS_BASR 179 
#define  SYSZ_INS_BER 178 
#define  SYSZ_INS_BHER 177 
#define  SYSZ_INS_BHR 176 
#define  SYSZ_INS_BLER 175 
#define  SYSZ_INS_BLHR 174 
#define  SYSZ_INS_BLR 173 
#define  SYSZ_INS_BNER 172 
#define  SYSZ_INS_BNHER 171 
#define  SYSZ_INS_BNHR 170 
#define  SYSZ_INS_BNLER 169 
#define  SYSZ_INS_BNLHR 168 
#define  SYSZ_INS_BNLR 167 
#define  SYSZ_INS_BNOR 166 
#define  SYSZ_INS_BOR 165 
#define  SYSZ_INS_BR 164 
#define  SYSZ_INS_BRAS 163 
#define  SYSZ_INS_BRASL 162 
#define  SYSZ_INS_BRC 161 
#define  SYSZ_INS_BRCL 160 
#define  SYSZ_INS_BRCT 159 
#define  SYSZ_INS_BRCTG 158 
#define  SYSZ_INS_J 157 
#define  SYSZ_INS_JE 156 
#define  SYSZ_INS_JG 155 
#define  SYSZ_INS_JGE 154 
#define  SYSZ_INS_JGH 153 
#define  SYSZ_INS_JGHE 152 
#define  SYSZ_INS_JGL 151 
#define  SYSZ_INS_JGLE 150 
#define  SYSZ_INS_JGLH 149 
#define  SYSZ_INS_JGNE 148 
#define  SYSZ_INS_JGNH 147 
#define  SYSZ_INS_JGNHE 146 
#define  SYSZ_INS_JGNL 145 
#define  SYSZ_INS_JGNLE 144 
#define  SYSZ_INS_JGNLH 143 
#define  SYSZ_INS_JGNO 142 
#define  SYSZ_INS_JGO 141 
#define  SYSZ_INS_JH 140 
#define  SYSZ_INS_JHE 139 
#define  SYSZ_INS_JL 138 
#define  SYSZ_INS_JLE 137 
#define  SYSZ_INS_JLH 136 
#define  SYSZ_INS_JNE 135 
#define  SYSZ_INS_JNH 134 
#define  SYSZ_INS_JNHE 133 
#define  SYSZ_INS_JNL 132 
#define  SYSZ_INS_JNLE 131 
#define  SYSZ_INS_JNLH 130 
#define  SYSZ_INS_JNO 129 
#define  SYSZ_INS_JO 128 
 int UT64_MAX ; 
 int /*<<< orphan*/  cs_close (int /*<<< orphan*/ *) ; 
 int cs_disasm (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int,int,TYPE_1__**) ; 
 int /*<<< orphan*/  cs_free (TYPE_1__*,int) ; 
 int cs_open (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cs_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  r_strbuf_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int analop(RAnal *a, RAnalOp *op, ut64 addr, const ut8 *buf, int len, RAnalOpMask mask) {
	csh handle;
	cs_insn *insn;
	int mode = CS_MODE_BIG_ENDIAN;
	int ret = cs_open (CS_ARCH_SYSZ, mode, &handle);
	op->type = R_ANAL_OP_TYPE_NULL;
	op->size = 0;
	op->delay = 0;
	r_strbuf_init (&op->esil);
	if (ret == CS_ERR_OK) {
		cs_option (handle, CS_OPT_DETAIL, CS_OPT_ON);
		// capstone-next
		int n = cs_disasm (handle, (const ut8*)buf, len, addr, 1, &insn);
		if (n < 1) {
			op->type = R_ANAL_OP_TYPE_ILL;
		} else {
			if (mask & R_ANAL_OP_MASK_OPEX) {
				opex (&op->opex, handle, insn);
			}
			op->size = insn->size;
			switch (insn->id) {
			case SYSZ_INS_BRCL:
			case SYSZ_INS_BRASL:
				op->type = R_ANAL_OP_TYPE_CALL;
				break;
			case SYSZ_INS_BR:
				op->type = R_ANAL_OP_TYPE_JMP;
				break;
			case SYSZ_INS_BRC:
			case SYSZ_INS_BER:
			case SYSZ_INS_BHR:
			case SYSZ_INS_BHER:
			case SYSZ_INS_BLR:
			case SYSZ_INS_BLER:
			case SYSZ_INS_BLHR:
			case SYSZ_INS_BNER:
			case SYSZ_INS_BNHR:
			case SYSZ_INS_BNHER:
			case SYSZ_INS_BNLR:
			case SYSZ_INS_BNLER:
			case SYSZ_INS_BNLHR:
			case SYSZ_INS_BNOR:
			case SYSZ_INS_BOR:
			case SYSZ_INS_BASR:
			case SYSZ_INS_BRAS:
			case SYSZ_INS_BRCT:
			case SYSZ_INS_BRCTG:
				op->type = R_ANAL_OP_TYPE_CJMP;
				break;
			case SYSZ_INS_JE:
			case SYSZ_INS_JGE:
			case SYSZ_INS_JHE:
			case SYSZ_INS_JGHE:
			case SYSZ_INS_JH:
			case SYSZ_INS_JGH:
			case SYSZ_INS_JLE:
			case SYSZ_INS_JGLE:
			case SYSZ_INS_JLH:
			case SYSZ_INS_JGLH:
			case SYSZ_INS_JL:
			case SYSZ_INS_JGL:
			case SYSZ_INS_JNE:
			case SYSZ_INS_JGNE:
			case SYSZ_INS_JNHE:
			case SYSZ_INS_JGNHE:
			case SYSZ_INS_JNH:
			case SYSZ_INS_JGNH:
			case SYSZ_INS_JNLE:
			case SYSZ_INS_JGNLE:
			case SYSZ_INS_JNLH:
			case SYSZ_INS_JGNLH:
			case SYSZ_INS_JNL:
			case SYSZ_INS_JGNL:
			case SYSZ_INS_JNO:
			case SYSZ_INS_JGNO:
			case SYSZ_INS_JO:
			case SYSZ_INS_JGO:
			case SYSZ_INS_JG:
				op->type = R_ANAL_OP_TYPE_CJMP;
				op->jump = INSOP(0).imm;
				op->fail = addr+op->size;
				break;
			case SYSZ_INS_J:
				op->type = R_ANAL_OP_TYPE_JMP;
				op->jump = INSOP(0).imm;
				op->fail = UT64_MAX;
				break;
			}
		}
		cs_free (insn, n);
		cs_close (&handle);
	}
	return op->size;
}