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
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  scalar_t__ csh ;
struct TYPE_13__ {int size; int id; } ;
typedef  TYPE_1__ cs_insn ;
struct TYPE_15__ {int /*<<< orphan*/  cpu; int /*<<< orphan*/  big_endian; } ;
struct TYPE_14__ {int size; int delay; int id; void* type; void* fail; void* jump; int /*<<< orphan*/  opex; int /*<<< orphan*/  esil; void* ptr; void* val; } ;
struct TYPE_12__ {void* imm; int /*<<< orphan*/  type; } ;
typedef  int RAnalOpMask ;
typedef  TYPE_2__ RAnalOp ;
typedef  TYPE_3__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ARCH_SPARC ; 
 int CS_ERR_OK ; 
 int CS_MODE_LITTLE_ENDIAN ; 
 int CS_MODE_V9 ; 
 int /*<<< orphan*/  CS_OPT_DETAIL ; 
 int /*<<< orphan*/  CS_OPT_ON ; 
 int /*<<< orphan*/  INSCC ; 
 TYPE_11__ INSOP (int) ; 
 int R_ANAL_OP_MASK_OPEX ; 
 int R_ANAL_OP_MASK_VAL ; 
 void* R_ANAL_OP_TYPE_ADD ; 
 void* R_ANAL_OP_TYPE_CALL ; 
 void* R_ANAL_OP_TYPE_CJMP ; 
 void* R_ANAL_OP_TYPE_CMP ; 
 void* R_ANAL_OP_TYPE_DIV ; 
 void* R_ANAL_OP_TYPE_ILL ; 
 void* R_ANAL_OP_TYPE_JMP ; 
 void* R_ANAL_OP_TYPE_LOAD ; 
 void* R_ANAL_OP_TYPE_MOV ; 
 void* R_ANAL_OP_TYPE_MUL ; 
 void* R_ANAL_OP_TYPE_NOP ; 
 void* R_ANAL_OP_TYPE_NULL ; 
 void* R_ANAL_OP_TYPE_OR ; 
 void* R_ANAL_OP_TYPE_RET ; 
 void* R_ANAL_OP_TYPE_STORE ; 
 void* R_ANAL_OP_TYPE_SUB ; 
 void* R_ANAL_OP_TYPE_UCALL ; 
 void* R_ANAL_OP_TYPE_UNK ; 
 int /*<<< orphan*/  SPARC_CC_ICC_A ; 
 int /*<<< orphan*/  SPARC_CC_ICC_N ; 
#define  SPARC_INS_ADD 236 
#define  SPARC_INS_ADDCC 235 
#define  SPARC_INS_ADDX 234 
#define  SPARC_INS_ADDXC 233 
#define  SPARC_INS_ADDXCC 232 
#define  SPARC_INS_ADDXCCC 231 
#define  SPARC_INS_B 230 
#define  SPARC_INS_BMASK 229 
#define  SPARC_INS_BRGEZ 228 
#define  SPARC_INS_BRGZ 227 
#define  SPARC_INS_BRLEZ 226 
#define  SPARC_INS_BRLZ 225 
#define  SPARC_INS_BRNZ 224 
#define  SPARC_INS_BRZ 223 
#define  SPARC_INS_CALL 222 
#define  SPARC_INS_CMP 221 
#define  SPARC_INS_FADDD 220 
#define  SPARC_INS_FADDQ 219 
#define  SPARC_INS_FADDS 218 
#define  SPARC_INS_FB 217 
#define  SPARC_INS_FDIVD 216 
#define  SPARC_INS_FDIVQ 215 
#define  SPARC_INS_FDIVS 214 
#define  SPARC_INS_FDMULQ 213 
#define  SPARC_INS_FHADDD 212 
#define  SPARC_INS_FHADDS 211 
#define  SPARC_INS_FHSUBD 210 
#define  SPARC_INS_FHSUBS 209 
#define  SPARC_INS_FMUL8SUX16 208 
#define  SPARC_INS_FMUL8ULX16 207 
#define  SPARC_INS_FMUL8X16 206 
#define  SPARC_INS_FMUL8X16AL 205 
#define  SPARC_INS_FMUL8X16AU 204 
#define  SPARC_INS_FMULD 203 
#define  SPARC_INS_FMULD8SUX16 202 
#define  SPARC_INS_FMULD8ULX16 201 
#define  SPARC_INS_FMULQ 200 
#define  SPARC_INS_FMULS 199 
#define  SPARC_INS_FNADDD 198 
#define  SPARC_INS_FNADDS 197 
#define  SPARC_INS_FNHADDD 196 
#define  SPARC_INS_FNHADDS 195 
#define  SPARC_INS_FPADD16 194 
#define  SPARC_INS_FPADD16S 193 
#define  SPARC_INS_FPADD32 192 
#define  SPARC_INS_FPADD32S 191 
#define  SPARC_INS_FPADD64 190 
#define  SPARC_INS_FPSUB16 189 
#define  SPARC_INS_FPSUB16S 188 
#define  SPARC_INS_FPSUB32 187 
#define  SPARC_INS_FPSUB32S 186 
#define  SPARC_INS_FSMULD 185 
#define  SPARC_INS_FSUBD 184 
#define  SPARC_INS_FSUBQ 183 
#define  SPARC_INS_FSUBS 182 
#define  SPARC_INS_INVALID 181 
#define  SPARC_INS_JMP 180 
#define  SPARC_INS_JMPL 179 
#define  SPARC_INS_LD 178 
#define  SPARC_INS_LDD 177 
#define  SPARC_INS_LDQ 176 
#define  SPARC_INS_LDSB 175 
#define  SPARC_INS_LDSH 174 
#define  SPARC_INS_LDSW 173 
#define  SPARC_INS_LDUB 172 
#define  SPARC_INS_LDUH 171 
#define  SPARC_INS_LDX 170 
#define  SPARC_INS_MOV 169 
#define  SPARC_INS_MULX 168 
#define  SPARC_INS_NOP 167 
#define  SPARC_INS_OR 166 
#define  SPARC_INS_ORCC 165 
#define  SPARC_INS_ORN 164 
#define  SPARC_INS_ORNCC 163 
#define  SPARC_INS_RET 162 
#define  SPARC_INS_RETL 161 
#define  SPARC_INS_RETT 160 
#define  SPARC_INS_SDIV 159 
#define  SPARC_INS_SDIVCC 158 
#define  SPARC_INS_SDIVX 157 
#define  SPARC_INS_SMUL 156 
#define  SPARC_INS_SMULCC 155 
#define  SPARC_INS_ST 154 
#define  SPARC_INS_STB 153 
#define  SPARC_INS_STBAR 152 
#define  SPARC_INS_STD 151 
#define  SPARC_INS_STH 150 
#define  SPARC_INS_STQ 149 
#define  SPARC_INS_STX 148 
#define  SPARC_INS_SUB 147 
#define  SPARC_INS_SUBCC 146 
#define  SPARC_INS_SUBX 145 
#define  SPARC_INS_SUBXCC 144 
#define  SPARC_INS_TADDCC 143 
#define  SPARC_INS_TADDCCTV 142 
#define  SPARC_INS_TSUBCC 141 
#define  SPARC_INS_TSUBCCTV 140 
#define  SPARC_INS_UDIV 139 
#define  SPARC_INS_UDIVCC 138 
#define  SPARC_INS_UDIVX 137 
#define  SPARC_INS_UMUL 136 
#define  SPARC_INS_UMULCC 135 
#define  SPARC_INS_UMULXHI 134 
#define  SPARC_INS_UNIMP 133 
#define  SPARC_INS_XMULX 132 
#define  SPARC_INS_XMULXHI 131 
#define  SPARC_OP_IMM 130 
#define  SPARC_OP_MEM 129 
#define  SPARC_OP_REG 128 
 void* UT64_MAX ; 
 int /*<<< orphan*/  cs_close (scalar_t__*) ; 
 int cs_disasm (scalar_t__,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int,TYPE_1__**) ; 
 int /*<<< orphan*/  cs_free (TYPE_1__*,int) ; 
 int cs_open (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  cs_option (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op_fillval (TYPE_2__*,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  opex (int /*<<< orphan*/ *,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  r_strbuf_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int analop(RAnal *a, RAnalOp *op, ut64 addr, const ut8 *buf, int len, RAnalOpMask mask) {
	static csh handle = 0;
	static int omode;
	cs_insn *insn;
	int mode, n, ret;

	if (!a->big_endian) {
		return -1;
	}

	mode = CS_MODE_LITTLE_ENDIAN;
	if (!strcmp (a->cpu, "v9")) {
		mode |= CS_MODE_V9;
	}
	if (mode != omode) {
		cs_close (&handle);
		handle = 0;
		omode = mode;
	}
	if (handle == 0) {
		ret = cs_open (CS_ARCH_SPARC, mode, &handle);
		if (ret != CS_ERR_OK) {
			return -1;
		}
		cs_option (handle, CS_OPT_DETAIL, CS_OPT_ON);
	}
	op->type = R_ANAL_OP_TYPE_NULL;
	op->size = 0;
	op->delay = 0;
	op->jump = UT64_MAX;
	op->fail = UT64_MAX;
	op->val = UT64_MAX;
	op->ptr = UT64_MAX;
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
		case SPARC_INS_INVALID:
			op->type = R_ANAL_OP_TYPE_ILL;
			break;
		case SPARC_INS_MOV:
			op->type = R_ANAL_OP_TYPE_MOV;
			break;
		case SPARC_INS_RETT:
		case SPARC_INS_RET:
		case SPARC_INS_RETL:
			op->type = R_ANAL_OP_TYPE_RET;
			op->delay = 1;
			break;
		case SPARC_INS_UNIMP:
			op->type = R_ANAL_OP_TYPE_UNK;
			break;
		case SPARC_INS_CALL:
			switch (INSOP(0).type) {
			case SPARC_OP_MEM:
				// TODO
				break;
			case SPARC_OP_REG:
				op->type = R_ANAL_OP_TYPE_UCALL;
				op->delay = 1;
				break;
			default:
				op->type = R_ANAL_OP_TYPE_CALL;
				op->delay = 1;
				op->jump = INSOP(0).imm;
				break;
			}
			break;
		case SPARC_INS_NOP:
			op->type = R_ANAL_OP_TYPE_NOP;
			break;
		case SPARC_INS_CMP:
			op->type = R_ANAL_OP_TYPE_CMP;
			break;
		case SPARC_INS_JMP:
		case SPARC_INS_JMPL:
			op->type = R_ANAL_OP_TYPE_JMP;
			op->delay = 1;
			op->jump = INSOP(0).imm;
			break;
		case SPARC_INS_LDD:
		case SPARC_INS_LD:
		case SPARC_INS_LDQ:
		case SPARC_INS_LDSB:
		case SPARC_INS_LDSH:
		case SPARC_INS_LDSW:
		case SPARC_INS_LDUB:
		case SPARC_INS_LDUH:
		case SPARC_INS_LDX:
			op->type = R_ANAL_OP_TYPE_LOAD;
			break;
		case SPARC_INS_STBAR:
		case SPARC_INS_STB:
		case SPARC_INS_STD:
		case SPARC_INS_ST:
		case SPARC_INS_STH:
		case SPARC_INS_STQ:
		case SPARC_INS_STX:
			op->type = R_ANAL_OP_TYPE_STORE;
			break;
		case SPARC_INS_ORCC:
		case SPARC_INS_ORNCC:
		case SPARC_INS_ORN:
		case SPARC_INS_OR:
			op->type = R_ANAL_OP_TYPE_OR;
			break;
		case SPARC_INS_B:
		case SPARC_INS_BMASK:
		case SPARC_INS_BRGEZ:
		case SPARC_INS_BRGZ:
		case SPARC_INS_BRLEZ:
		case SPARC_INS_BRLZ:
		case SPARC_INS_BRNZ:
		case SPARC_INS_BRZ:
		case SPARC_INS_FB:
			switch (INSOP(0).type) {
			case SPARC_OP_REG:
				op->type = R_ANAL_OP_TYPE_CJMP;
				op->delay = 1;
				if (INSCC != SPARC_CC_ICC_N) { // never
					op->jump = INSOP (1).imm;
				}
				if (INSCC != SPARC_CC_ICC_A) { // always
					op->fail = addr + 8;
				}
				break;
			case SPARC_OP_IMM:
				op->type = R_ANAL_OP_TYPE_CJMP;
				op->delay = 1;
				if (INSCC != SPARC_CC_ICC_N) { // never
					op->jump = INSOP (0).imm;
				}
				if (INSCC != SPARC_CC_ICC_A) { // always
					op->fail = addr + 8;
				}
				break;
			default:
				// MEM?
				break;
			}
			break;
		case SPARC_INS_FHSUBD:
		case SPARC_INS_FHSUBS:
		case SPARC_INS_FPSUB16:
		case SPARC_INS_FPSUB16S:
		case SPARC_INS_FPSUB32:
		case SPARC_INS_FPSUB32S:
		case SPARC_INS_FSUBD:
		case SPARC_INS_FSUBQ:
		case SPARC_INS_FSUBS:
		case SPARC_INS_SUBCC:
		case SPARC_INS_SUBX:
		case SPARC_INS_SUBXCC:
		case SPARC_INS_SUB:
		case SPARC_INS_TSUBCCTV:
		case SPARC_INS_TSUBCC:
			op->type = R_ANAL_OP_TYPE_SUB;
			break;
		case SPARC_INS_ADDCC:
		case SPARC_INS_ADDX:
		case SPARC_INS_ADDXCC:
		case SPARC_INS_ADDXC:
		case SPARC_INS_ADDXCCC:
		case SPARC_INS_ADD:
		case SPARC_INS_FADDD:
		case SPARC_INS_FADDQ:
		case SPARC_INS_FADDS:
		case SPARC_INS_FHADDD:
		case SPARC_INS_FHADDS:
		case SPARC_INS_FNADDD:
		case SPARC_INS_FNADDS:
		case SPARC_INS_FNHADDD:
		case SPARC_INS_FNHADDS:
		case SPARC_INS_FPADD16:
		case SPARC_INS_FPADD16S:
		case SPARC_INS_FPADD32:
		case SPARC_INS_FPADD32S:
		case SPARC_INS_FPADD64:
		case SPARC_INS_TADDCCTV:
		case SPARC_INS_TADDCC:
			op->type = R_ANAL_OP_TYPE_ADD;
			break;
		case SPARC_INS_FDMULQ:
		case SPARC_INS_FMUL8SUX16:
		case SPARC_INS_FMUL8ULX16:
		case SPARC_INS_FMUL8X16:
		case SPARC_INS_FMUL8X16AL:
		case SPARC_INS_FMUL8X16AU:
		case SPARC_INS_FMULD:
		case SPARC_INS_FMULD8SUX16:
		case SPARC_INS_FMULD8ULX16:
		case SPARC_INS_FMULQ:
		case SPARC_INS_FMULS:
		case SPARC_INS_FSMULD:
		case SPARC_INS_MULX:
		case SPARC_INS_SMULCC:
		case SPARC_INS_SMUL:
		case SPARC_INS_UMULCC:
		case SPARC_INS_UMULXHI:
		case SPARC_INS_UMUL:
		case SPARC_INS_XMULX:
		case SPARC_INS_XMULXHI:
			op->type = R_ANAL_OP_TYPE_MUL;
			break;
		case SPARC_INS_FDIVD:
		case SPARC_INS_FDIVQ:
		case SPARC_INS_FDIVS:
		case SPARC_INS_SDIVCC:
		case SPARC_INS_SDIVX:
		case SPARC_INS_SDIV:
		case SPARC_INS_UDIVCC:
		case SPARC_INS_UDIVX:
		case SPARC_INS_UDIV:
			op->type = R_ANAL_OP_TYPE_DIV;
			break;
		}
		if (mask & R_ANAL_OP_MASK_VAL) {
			op_fillval (op, handle, insn);
		}
		cs_free (insn, n);
	}
	return op->size;
}