#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  void* ut64 ;
struct Getarg {scalar_t__ handle; int bits; TYPE_4__* insn; } ;
typedef  scalar_t__ csh ;
struct TYPE_20__ {int size; int id; TYPE_3__* detail; } ;
typedef  TYPE_4__ cs_insn ;
struct TYPE_22__ {int bits; scalar_t__ big_endian; scalar_t__ cpu; } ;
struct TYPE_21__ {void* type; int size; int id; int sign; int /*<<< orphan*/  esil; void* fail; void* jump; int /*<<< orphan*/  opex; void* val; void* ptr; scalar_t__ delay; } ;
struct TYPE_18__ {int /*<<< orphan*/  bc; TYPE_1__* operands; } ;
struct TYPE_19__ {TYPE_2__ ppc; } ;
struct TYPE_17__ {int /*<<< orphan*/  type; } ;
typedef  int RAnalOpMask ;
typedef  TYPE_5__ RAnalOp ;
typedef  TYPE_6__ RAnal ;

/* Variables and functions */
 char* ARG (int) ; 
 int /*<<< orphan*/  ARG2 (int,char*) ; 
 int /*<<< orphan*/  CS_ARCH_PPC ; 
 int CS_ERR_OK ; 
 int CS_MODE_32 ; 
 int CS_MODE_64 ; 
 int CS_MODE_BIG_ENDIAN ; 
 int CS_MODE_LITTLE_ENDIAN ; 
 int /*<<< orphan*/  CS_OPT_DETAIL ; 
 int /*<<< orphan*/  CS_OPT_ON ; 
 void* IMM (int) ; 
 int /*<<< orphan*/  PPCSPR (int) ; 
#define  PPC_BC_EQ 299 
#define  PPC_BC_GE 298 
#define  PPC_BC_GT 297 
#define  PPC_BC_INVALID 296 
#define  PPC_BC_LE 295 
#define  PPC_BC_LT 294 
#define  PPC_BC_NE 293 
#define  PPC_BC_NS 292 
#define  PPC_BC_NU 291 
#define  PPC_BC_SO 290 
#define  PPC_BC_UN 289 
#define  PPC_INS_ADD 288 
#define  PPC_INS_ADDC 287 
#define  PPC_INS_ADDE 286 
#define  PPC_INS_ADDI 285 
#define  PPC_INS_ADDIC 284 
#define  PPC_INS_ADDIS 283 
#define  PPC_INS_ADDME 282 
#define  PPC_INS_ADDZE 281 
#define  PPC_INS_AND 280 
#define  PPC_INS_ANDI 279 
#define  PPC_INS_ANDIS 278 
#define  PPC_INS_B 277 
#define  PPC_INS_BA 276 
#define  PPC_INS_BC 275 
#define  PPC_INS_BCLR 274 
#define  PPC_INS_BCLRL 273 
#define  PPC_INS_BCTR 272 
#define  PPC_INS_BCTRL 271 
#define  PPC_INS_BDNZ 270 
#define  PPC_INS_BDNZA 269 
#define  PPC_INS_BDNZL 268 
#define  PPC_INS_BDNZLA 267 
#define  PPC_INS_BDNZLR 266 
#define  PPC_INS_BDNZLRL 265 
#define  PPC_INS_BDZ 264 
#define  PPC_INS_BDZA 263 
#define  PPC_INS_BDZL 262 
#define  PPC_INS_BDZLA 261 
#define  PPC_INS_BDZLR 260 
#define  PPC_INS_BDZLRL 259 
#define  PPC_INS_BL 258 
#define  PPC_INS_BLA 257 
#define  PPC_INS_BLR 256 
#define  PPC_INS_BLRL 255 
#define  PPC_INS_CLRLDI 254 
#define  PPC_INS_CLRLWI 253 
#define  PPC_INS_CMPD 252 
#define  PPC_INS_CMPDI 251 
#define  PPC_INS_CMPLD 250 
#define  PPC_INS_CMPLDI 249 
#define  PPC_INS_CMPLW 248 
#define  PPC_INS_CMPLWI 247 
#define  PPC_INS_CMPW 246 
#define  PPC_INS_CMPWI 245 
#define  PPC_INS_DCBZ 244 
#define  PPC_INS_DIVD 243 
#define  PPC_INS_DIVDU 242 
#define  PPC_INS_DIVW 241 
#define  PPC_INS_DIVWU 240 
#define  PPC_INS_EIEIO 239 
#define  PPC_INS_EXTSB 238 
#define  PPC_INS_EXTSH 237 
#define  PPC_INS_EXTSW 236 
#define  PPC_INS_ISYNC 235 
#define  PPC_INS_LBZ 234 
#define  PPC_INS_LBZU 233 
#define  PPC_INS_LBZUX 232 
#define  PPC_INS_LBZX 231 
#define  PPC_INS_LD 230 
#define  PPC_INS_LDARX 229 
#define  PPC_INS_LDBRX 228 
#define  PPC_INS_LDU 227 
#define  PPC_INS_LDUX 226 
#define  PPC_INS_LDX 225 
#define  PPC_INS_LFD 224 
#define  PPC_INS_LFDU 223 
#define  PPC_INS_LFDUX 222 
#define  PPC_INS_LFDX 221 
#define  PPC_INS_LFIWAX 220 
#define  PPC_INS_LFIWZX 219 
#define  PPC_INS_LFS 218 
#define  PPC_INS_LFSU 217 
#define  PPC_INS_LFSUX 216 
#define  PPC_INS_LFSX 215 
#define  PPC_INS_LHA 214 
#define  PPC_INS_LHAU 213 
#define  PPC_INS_LHAUX 212 
#define  PPC_INS_LHAX 211 
#define  PPC_INS_LHBRX 210 
#define  PPC_INS_LHZ 209 
#define  PPC_INS_LHZU 208 
#define  PPC_INS_LI 207 
#define  PPC_INS_LIS 206 
#define  PPC_INS_LWA 205 
#define  PPC_INS_LWARX 204 
#define  PPC_INS_LWAUX 203 
#define  PPC_INS_LWAX 202 
#define  PPC_INS_LWBRX 201 
#define  PPC_INS_LWSYNC 200 
#define  PPC_INS_LWZ 199 
#define  PPC_INS_LWZU 198 
#define  PPC_INS_LWZUX 197 
#define  PPC_INS_LWZX 196 
#define  PPC_INS_MFCTR 195 
#define  PPC_INS_MFDCCR 194 
#define  PPC_INS_MFDEAR 193 
#define  PPC_INS_MFICCR 192 
#define  PPC_INS_MFLR 191 
#define  PPC_INS_MFMSR 190 
#define  PPC_INS_MFPVR 189 
#define  PPC_INS_MFSPR 188 
#define  PPC_INS_MR 187 
#define  PPC_INS_MSYNC 186 
#define  PPC_INS_MTCTR 185 
#define  PPC_INS_MTDCCR 184 
#define  PPC_INS_MTDEAR 183 
#define  PPC_INS_MTICCR 182 
#define  PPC_INS_MTLR 181 
#define  PPC_INS_MTMSR 180 
#define  PPC_INS_MTMSRD 179 
#define  PPC_INS_MTSPR 178 
#define  PPC_INS_MULLD 177 
#define  PPC_INS_MULLI 176 
#define  PPC_INS_MULLW 175 
#define  PPC_INS_NAND 174 
#define  PPC_INS_NOP 173 
#define  PPC_INS_NOR 172 
#define  PPC_INS_OR 171 
#define  PPC_INS_ORI 170 
#define  PPC_INS_ORIS 169 
#define  PPC_INS_PTESYNC 168 
#define  PPC_INS_RLDCL 167 
#define  PPC_INS_RLDCR 166 
#define  PPC_INS_RLDICL 165 
#define  PPC_INS_RLDICR 164 
#define  PPC_INS_RLWINM 163 
#define  PPC_INS_ROTLDI 162 
#define  PPC_INS_SC 161 
#define  PPC_INS_SLBIA 160 
#define  PPC_INS_SLBIE 159 
#define  PPC_INS_SLBMFEE 158 
#define  PPC_INS_SLBMTE 157 
#define  PPC_INS_SLW 156 
#define  PPC_INS_SLWI 155 
#define  PPC_INS_SRW 154 
#define  PPC_INS_SRWI 153 
#define  PPC_INS_STB 152 
#define  PPC_INS_STBU 151 
#define  PPC_INS_STD 150 
#define  PPC_INS_STDU 149 
#define  PPC_INS_STH 148 
#define  PPC_INS_STHU 147 
#define  PPC_INS_STW 146 
#define  PPC_INS_STWBRX 145 
#define  PPC_INS_STWCX 144 
#define  PPC_INS_STWU 143 
#define  PPC_INS_STWUX 142 
#define  PPC_INS_STWX 141 
#define  PPC_INS_SUB 140 
#define  PPC_INS_SUBC 139 
#define  PPC_INS_SUBF 138 
#define  PPC_INS_SUBFIC 137 
#define  PPC_INS_SUBFZE 136 
#define  PPC_INS_SYNC 135 
#define  PPC_INS_TLBSYNC 134 
#define  PPC_INS_TRAP 133 
#define  PPC_INS_XOR 132 
#define  PPC_INS_XORI 131 
#define  PPC_INS_XORIS 130 
#define  PPC_OP_CRX 129 
#define  PPC_OP_REG 128 
 int R_ANAL_OP_MASK_OPEX ; 
 int R_ANAL_OP_MASK_VAL ; 
 void* R_ANAL_OP_TYPE_ADD ; 
 void* R_ANAL_OP_TYPE_AND ; 
 void* R_ANAL_OP_TYPE_CALL ; 
 void* R_ANAL_OP_TYPE_CJMP ; 
 void* R_ANAL_OP_TYPE_CMP ; 
 void* R_ANAL_OP_TYPE_CRET ; 
 void* R_ANAL_OP_TYPE_DIV ; 
 void* R_ANAL_OP_TYPE_ILL ; 
 void* R_ANAL_OP_TYPE_JMP ; 
 void* R_ANAL_OP_TYPE_LOAD ; 
 void* R_ANAL_OP_TYPE_MOV ; 
 void* R_ANAL_OP_TYPE_MUL ; 
 void* R_ANAL_OP_TYPE_NOP ; 
 void* R_ANAL_OP_TYPE_NOR ; 
 void* R_ANAL_OP_TYPE_NULL ; 
 void* R_ANAL_OP_TYPE_OR ; 
 void* R_ANAL_OP_TYPE_RET ; 
 void* R_ANAL_OP_TYPE_ROL ; 
 void* R_ANAL_OP_TYPE_SHL ; 
 void* R_ANAL_OP_TYPE_SHR ; 
 void* R_ANAL_OP_TYPE_STORE ; 
 void* R_ANAL_OP_TYPE_SUB ; 
 void* R_ANAL_OP_TYPE_SWI ; 
 void* R_ANAL_OP_TYPE_TRAP ; 
 void* R_ANAL_OP_TYPE_UCJMP ; 
 void* R_ANAL_OP_TYPE_UJMP ; 
 void* R_ANAL_OP_TYPE_XOR ; 
 void* UT64_MAX ; 
 int analop_vle (TYPE_6__*,TYPE_5__*,void*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  cmask32 (char*,char*) ; 
 int /*<<< orphan*/  cmask64 (char*,char*) ; 
 int /*<<< orphan*/  cs_close (scalar_t__*) ; 
 int cs_disasm (scalar_t__,int /*<<< orphan*/  const*,int,void*,int,TYPE_4__**) ; 
 int /*<<< orphan*/  cs_free (TYPE_4__*,int) ; 
 int cs_open (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  cs_option (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esilprintf (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  op_fillval (TYPE_5__*,scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  opex (int /*<<< orphan*/ *,scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  r_strbuf_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_strbuf_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_strbuf_set (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static int analop(RAnal *a, RAnalOp *op, ut64 addr, const ut8 *buf, int len, RAnalOpMask mask) {
	static csh handle = 0;
	static int omode = -1, obits = -1;
	int n, ret;
	cs_insn *insn;
	int mode = (a->bits == 64) ? CS_MODE_64 : (a->bits == 32) ? CS_MODE_32 : 0;
	mode |= a->big_endian ? CS_MODE_BIG_ENDIAN : CS_MODE_LITTLE_ENDIAN;

	op->delay = 0;
	op->type = R_ANAL_OP_TYPE_NULL;
	op->jump = UT64_MAX;
	op->fail = UT64_MAX;
	op->ptr = op->val = UT64_MAX;
	if (a->cpu && strncmp (a->cpu, "vle", 3) == 0) {
		// vle is big-endian only
		if (!a->big_endian) {
			return -1;
		}
		ret = analop_vle (a, op, addr, buf, len);
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
		cs_option (handle, CS_OPT_DETAIL, CS_OPT_ON);
	}
	op->size = 4;

	r_strbuf_init (&op->esil);
	r_strbuf_set (&op->esil, "");

	// capstone-next
	n = cs_disasm (handle, (const ut8*)buf, len, addr, 1, &insn);
	if (n < 1) {
		op->type = R_ANAL_OP_TYPE_ILL;
	} else {
		if (mask & R_ANAL_OP_MASK_OPEX) {
			opex (&op->opex, handle, insn);
		}
		struct Getarg gop = {
			.handle = handle,
			.insn = insn,
			.bits = a->bits
		};
		op->size = insn->size;
		op->id = insn->id;
		switch (insn->id) {
#if CS_API_MAJOR >= 4
		case PPC_INS_CMPB:
#endif
		case PPC_INS_CMPD:
		case PPC_INS_CMPDI:
		case PPC_INS_CMPLD:
		case PPC_INS_CMPLDI:
		case PPC_INS_CMPLW:
		case PPC_INS_CMPLWI:
		case PPC_INS_CMPW:
		case PPC_INS_CMPWI:
			op->type = R_ANAL_OP_TYPE_CMP;
			op->sign = true;
			if (ARG (2)[0] == '\0') {
				esilprintf (op, "%s,%s,-,0xff,&,cr0,=", ARG (1), ARG (0));
			} else {
				esilprintf (op, "%s,%s,-,0xff,&,%s,=", ARG (2), ARG (1), ARG (0));
			}
			break;
		case PPC_INS_MFLR:
			op->type = R_ANAL_OP_TYPE_MOV;
			esilprintf (op, "lr,%s,=", ARG (0));
			break;
		case PPC_INS_MTLR:
			op->type = R_ANAL_OP_TYPE_MOV;
			esilprintf (op, "%s,lr,=", ARG (0));
			break;
		case PPC_INS_MR:
		case PPC_INS_LI:
			op->type = R_ANAL_OP_TYPE_MOV;
			esilprintf (op, "%s,%s,=", ARG (1), ARG (0));
			break;
		case PPC_INS_LIS:
			op->type = R_ANAL_OP_TYPE_MOV;
			esilprintf (op, "%s0000,%s,=", ARG (1), ARG (0));
			break;
		case PPC_INS_CLRLWI:
			op->type = R_ANAL_OP_TYPE_AND;
			esilprintf (op, "%s,%s,&,%s,=", ARG (1), cmask32 (ARG (2), "0x1F"), ARG (0));
			break;
		case PPC_INS_RLWINM:
			op->type = R_ANAL_OP_TYPE_ROL;
			esilprintf (op, "%s,%s,<<<,%s,&,%s,=", ARG (2), ARG (1), cmask32 (ARG (3), ARG (4)), ARG (0));
			break;
		case PPC_INS_SC:
			op->type = R_ANAL_OP_TYPE_SWI;
			esilprintf (op, "0,$");
			break;
		case PPC_INS_EXTSB:
			op->sign = true;
			op->type = R_ANAL_OP_TYPE_MOV;
			if (a->bits == 64) {
				esilprintf (op, "%s,0x80,&,?{,0xFFFFFFFFFFFFFF00,%s,|,%s,=,}", ARG (1), ARG (1), ARG (0));
			} else {
				esilprintf (op, "%s,0x80,&,?{,0xFFFFFF00,%s,|,%s,=,}", ARG (1), ARG (1), ARG (0));
			}
			break;
		case PPC_INS_EXTSH:
			op->sign = true;
			if (a->bits == 64) {
				esilprintf (op, "%s,0x8000,&,?{,0xFFFFFFFFFFFF0000,%s,|,%s,=,}", ARG (1), ARG (1), ARG (0));
			} else {
				esilprintf (op, "%s,0x8000,&,?{,0xFFFF0000,%s,|,%s,=,}", ARG (1), ARG (1), ARG (0));
			}
			break;
		case PPC_INS_EXTSW:
			op->sign = true;
			esilprintf (op, "%s,0x80000000,&,?{,0xFFFFFFFF00000000,%s,|,%s,=,}", ARG (1), ARG (1), ARG (0));
			break;
		case PPC_INS_SYNC:
		case PPC_INS_ISYNC:
		case PPC_INS_LWSYNC:
		case PPC_INS_MSYNC:
		case PPC_INS_PTESYNC:
		case PPC_INS_TLBSYNC:
		case PPC_INS_SLBIA:
		case PPC_INS_SLBIE:
		case PPC_INS_SLBMFEE:
		case PPC_INS_SLBMTE:
		case PPC_INS_EIEIO:
		case PPC_INS_NOP:
			op->type = R_ANAL_OP_TYPE_NOP;
			esilprintf (op, ",");
			break;
		case PPC_INS_STW:
		case PPC_INS_STWU:
		case PPC_INS_STWUX:
		case PPC_INS_STWX:
		case PPC_INS_STWCX:
			op->type = R_ANAL_OP_TYPE_STORE;
			esilprintf (op, "%s,%s", ARG (0), ARG2 (1, "=[4]"));
			break;
		case PPC_INS_STWBRX:
			op->type = R_ANAL_OP_TYPE_STORE;
			break;
		case PPC_INS_STB:
		case PPC_INS_STBU:
			op->type = R_ANAL_OP_TYPE_STORE;
			esilprintf (op, "%s,%s", ARG (0), ARG2 (1, "=[1]"));
			break;
		case PPC_INS_STH:
		case PPC_INS_STHU:
			op->type = R_ANAL_OP_TYPE_STORE;
			esilprintf (op, "%s,%s", ARG (0), ARG2 (1, "=[2]"));
			break;
		case PPC_INS_STD:
		case PPC_INS_STDU:
			op->type = R_ANAL_OP_TYPE_STORE;
			esilprintf (op, "%s,%s", ARG (0), ARG2 (1, "=[8]"));
			break;
		case PPC_INS_LBZ:
#if CS_API_MAJOR >= 4
		case PPC_INS_LBZCIX:
#endif
		case PPC_INS_LBZU:
		case PPC_INS_LBZUX:
		case PPC_INS_LBZX:
			op->type = R_ANAL_OP_TYPE_LOAD;
			esilprintf (op, "%s,%s,=", ARG2 (1, "[1]"), ARG (0));
			break;
		case PPC_INS_LD:
		case PPC_INS_LDARX:
#if CS_API_MAJOR >= 4
		case PPC_INS_LDCIX:
#endif
		case PPC_INS_LDU:
		case PPC_INS_LDUX:
		case PPC_INS_LDX:
			op->type = R_ANAL_OP_TYPE_LOAD;
			esilprintf (op, "%s,%s,=", ARG2 (1, "[8]"), ARG (0));
			break;
		case PPC_INS_LDBRX:
			op->type = R_ANAL_OP_TYPE_LOAD;
			break;
		case PPC_INS_LFD:
		case PPC_INS_LFDU:
		case PPC_INS_LFDUX:
		case PPC_INS_LFDX:
		case PPC_INS_LFIWAX:
		case PPC_INS_LFIWZX:
		case PPC_INS_LFS:
		case PPC_INS_LFSU:
		case PPC_INS_LFSUX:
		case PPC_INS_LFSX:
			op->type = R_ANAL_OP_TYPE_LOAD;
			esilprintf (op, "%s,%s,=", ARG2 (1, "[4]"), ARG (0));
			break;
		case PPC_INS_LHA:
		case PPC_INS_LHAU:
		case PPC_INS_LHAUX:
		case PPC_INS_LHAX:
		case PPC_INS_LHZ:
		case PPC_INS_LHZU:
			op->type = R_ANAL_OP_TYPE_LOAD;
			esilprintf (op, "%s,%s,=", ARG2 (1, "[2]"), ARG (0));
			break;
		case PPC_INS_LHBRX:
			op->type = R_ANAL_OP_TYPE_LOAD;
			break;
		case PPC_INS_LWA:
		case PPC_INS_LWARX:
		case PPC_INS_LWAUX:
		case PPC_INS_LWAX:
		case PPC_INS_LWZ:
#if CS_API_MAJOR >= 4
		case PPC_INS_LWZCIX:
#endif
		case PPC_INS_LWZU:
		case PPC_INS_LWZUX:
		case PPC_INS_LWZX:
			op->type = R_ANAL_OP_TYPE_LOAD;
			esilprintf (op, "%s,%s,=", ARG2 (1, "[4]"), ARG (0));
			break;
		case PPC_INS_LWBRX:
			op->type = R_ANAL_OP_TYPE_LOAD;
			break;
		case PPC_INS_SLW:
		case PPC_INS_SLWI:
			op->type = R_ANAL_OP_TYPE_SHL;
			esilprintf (op, "%s,%s,<<,%s,=", ARG (2), ARG (1), ARG (0));
			break;
		case PPC_INS_SRW:
		case PPC_INS_SRWI:
			op->type = R_ANAL_OP_TYPE_SHR;
			esilprintf (op, "%s,%s,>>,%s,=", ARG (2), ARG (1), ARG (0));
			break;
		case PPC_INS_MULLI:
			op->sign = true;
		case PPC_INS_MULLW:
		case PPC_INS_MULLD:
			op->type = R_ANAL_OP_TYPE_MUL;
			esilprintf (op, "%s,%s,*,%s,=", ARG (2), ARG (1), ARG (0));
			break;
		case PPC_INS_SUB:
		case PPC_INS_SUBC:
		case PPC_INS_SUBF:
		case PPC_INS_SUBFIC:
		case PPC_INS_SUBFZE:
			op->type = R_ANAL_OP_TYPE_SUB;
			esilprintf (op, "%s,%s,-,%s,=", ARG (1), ARG (2), ARG (0));
			break;
		case PPC_INS_ADD:
		case PPC_INS_ADDI:
			op->sign = true;
			op->type = R_ANAL_OP_TYPE_ADD;
			esilprintf (op, "%s,%s,+,%s,=", ARG (2), ARG (1), ARG (0));
			break;
		case PPC_INS_ADDC:
		case PPC_INS_ADDIC:
			op->type = R_ANAL_OP_TYPE_ADD;
			esilprintf (op, "%s,%s,+,%s,=", ARG (2), ARG (1), ARG (0));
			break;
		case PPC_INS_ADDE:
		case PPC_INS_ADDIS:
		case PPC_INS_ADDME:
		case PPC_INS_ADDZE:
			op->type = R_ANAL_OP_TYPE_ADD;
			esilprintf (op, "%s,%s,+,%s,=", ARG (2), ARG (1), ARG (0));
			break;
		case PPC_INS_MTSPR:
			op->type = R_ANAL_OP_TYPE_MOV;
			esilprintf (op, "%s,%s,=", ARG (1), PPCSPR (0));
			break;
		case PPC_INS_BCTR: // switch table here
			op->type = R_ANAL_OP_TYPE_UJMP;
			esilprintf (op, "ctr,pc,=");
			break;
		case PPC_INS_BCTRL: // switch table here
			op->type = R_ANAL_OP_TYPE_CALL;
			esilprintf (op, "pc,lr,=,ctr,pc,=");
			break;
		case PPC_INS_B:
		case PPC_INS_BC:
			op->jump = ARG (1)[0] == '\0' ? IMM (0) : IMM (1);
			op->type = R_ANAL_OP_TYPE_CJMP;
			op->fail = addr + op->size;
			switch (insn->detail->ppc.bc) {
			case PPC_BC_LT:
				if (ARG (1)[0] == '\0') {
					esilprintf (op, "0x80,cr0,&,!,!,?{,%s,pc,=,},", ARG (0));
				} else {
					esilprintf (op, "0x80,%s,&,!,!,?{,%s,pc,=,},", ARG (0), ARG (1));
				}
				break;
			case PPC_BC_LE:
				if (ARG (1)[0] == '\0') {
					esilprintf (op, "0x80,cr0,&,!,!,cr0,!,|,?{,%s,pc,=,},", ARG (0));
				} else {
					esilprintf (op, "0x80,%s,&,!,!,0,%s,!,|,?{,%s,pc,=,},", ARG (0), ARG (0), ARG (1));
				}
				break;
			case PPC_BC_EQ:
				if (ARG (1)[0] == '\0') {
					esilprintf (op, "cr0,!,?{,%s,pc,=,},", ARG (0));
				} else {
					esilprintf (op, "%s,!,?{,%s,pc,=,},", ARG (0), ARG (1));
				}
				break;
			case PPC_BC_GE:
				if (ARG (1)[0] == '\0') {
					esilprintf (op, "0x80,cr0,&,!,cr0,!,|,?{,%s,pc,=,},", ARG (0));
				} else {
					esilprintf (op, "0x80,%s,&,!,%s,!,|,?{,%s,pc,=,},", ARG (0), ARG (0), ARG (1));
				}
				break;
			case PPC_BC_GT:
				if (ARG (1)[0] == '\0') {
					esilprintf (op, "0x80,cr0,&,!,?{,%s,pc,=,},", ARG (0));
				} else {
					esilprintf (op, "0x80,%s,&,!,?{,%s,pc,=,},", ARG (0), ARG (1));
				}
				break;
			case PPC_BC_NE:
				if (ARG (1)[0] == '\0') {
					esilprintf (op, "cr0,!,!,?{,%s,pc,=,},", ARG (0));
				} else {
					esilprintf (op, "%s,!,!,?{,%s,pc,=,},", ARG (0), ARG (1));
				}
				break;
			case PPC_BC_INVALID:
				op->type = R_ANAL_OP_TYPE_JMP;
				esilprintf (op, "%s,pc,=", ARG (0));
			case PPC_BC_UN: // unordered
			case PPC_BC_NU: // not unordered
			case PPC_BC_SO: // summary overflow
			case PPC_BC_NS: // not summary overflow
			default:
				break;
			}
			break;
		case PPC_INS_BA:
			switch (insn->detail->ppc.operands[0].type) {
			case PPC_OP_CRX:
				op->type = R_ANAL_OP_TYPE_CJMP;
				op->fail = addr + op->size;
				break;
			case PPC_OP_REG:
				if (op->type == R_ANAL_OP_TYPE_CJMP) {
					op->type = R_ANAL_OP_TYPE_UCJMP;
				} else {
					op->type = R_ANAL_OP_TYPE_CJMP;
				}
				op->jump = IMM (1);
				op->fail = addr + op->size;
				//op->type = R_ANAL_OP_TYPE_UJMP;
			default:
				break;
			}
			break;
		case PPC_INS_BDNZ:
			op->type = R_ANAL_OP_TYPE_CJMP;
			op->jump = IMM (0);
			op->fail = addr + op->size;
			esilprintf (op, "1,ctr,-=,$z,!,?{,%s,pc,=,}", ARG (0));
			break;
		case PPC_INS_BDNZA:
			op->type = R_ANAL_OP_TYPE_CJMP;
			op->jump = IMM (0);
			op->fail = addr + op->size;
			break;
		case PPC_INS_BDNZL:
			op->type = R_ANAL_OP_TYPE_CJMP;
			op->jump = IMM (0);
			op->fail = addr + op->size;
			break;
		case PPC_INS_BDNZLA:
			op->type = R_ANAL_OP_TYPE_CJMP;
			op->jump = IMM (0);
			op->fail = addr + op->size;
			break;
		case PPC_INS_BDNZLR:
			op->type = R_ANAL_OP_TYPE_CJMP;
			op->fail = addr + op->size;
			esilprintf (op, "1,ctr,-=,$z,!,?{,lr,pc,=,},");
			break;
		case PPC_INS_BDNZLRL:
			op->fail = addr + op->size;
			op->type = R_ANAL_OP_TYPE_CJMP;
			break;
		case PPC_INS_BDZ:
			op->type = R_ANAL_OP_TYPE_CJMP;
			op->jump = IMM (0);
			op->fail = addr + op->size;
			esilprintf (op, "1,ctr,-=,$z,?{,%s,pc,=,}", ARG (0));
			break;
		case PPC_INS_BDZA:
			op->type = R_ANAL_OP_TYPE_CJMP;
			op->jump = IMM (0);
			op->fail = addr + op->size;
			break;
		case PPC_INS_BDZL:
			op->type = R_ANAL_OP_TYPE_CJMP;
			op->jump = IMM (0);
			op->fail = addr + op->size;
			break;
		case PPC_INS_BDZLA:
			op->type = R_ANAL_OP_TYPE_CJMP;
			op->jump = IMM (0);
			op->fail = addr + op->size;
			break;
		case PPC_INS_BDZLR:
			op->type = R_ANAL_OP_TYPE_CJMP;
			op->fail = addr + op->size;
			esilprintf (op, "1,ctr,-=,$z,?{,lr,pc,=,}");
			break;
		case PPC_INS_BDZLRL:
			op->type = R_ANAL_OP_TYPE_CJMP;
			op->fail = addr + op->size;
			break;
		case PPC_INS_BLR:
		case PPC_INS_BLRL:
		case PPC_INS_BCLR:
		case PPC_INS_BCLRL:
			op->type = R_ANAL_OP_TYPE_CRET;		//I'm a condret
			op->fail = addr + op->size;
			switch (insn->detail->ppc.bc) {
			case PPC_BC_INVALID:
				op->type = R_ANAL_OP_TYPE_RET;
				esilprintf (op, "lr,pc,=");
				break;
			case PPC_BC_LT:
				if (ARG (1)[0] == '\0') {
					esilprintf (op, "0x80,cr0,&,!,!,?{,lr,pc,=,},");
				} else {
					esilprintf (op, "0x80,%s,&,!,!,?{,lr,pc,=,},", ARG (0));
				}
				break;
			case PPC_BC_LE:
				if (ARG (1)[0] == '\0') {
					esilprintf (op, "0x80,cr0,&,!,!,cr0,!,|,?{,lr,pc,=,},");
				} else {
					esilprintf (op, "0x80,%s,&,!,!,0,%s,!,|,?{,lr,pc,=,},", ARG (0), ARG (0));
				}
				break;
			case PPC_BC_EQ:
				if (ARG (1)[0] == '\0') {
					esilprintf (op, "cr0,!,?{,lr,pc,=,},");
				} else {
					esilprintf (op, "%s,!,?{,lr,pc,=,},", ARG (0));
				}
				break;
			case PPC_BC_GE:
				if (ARG (1)[0] == '\0') {
					esilprintf (op, "0x80,cr0,&,!,cr0,!,|,?{,lr,pc,=,},");
				} else {
					esilprintf (op, "0x80,%s,&,!,%s,!,|,?{,lr,pc,=,},", ARG (0), ARG (0));
				}
				break;
			case PPC_BC_GT:
				if (ARG (1)[0] == '\0') {
					esilprintf (op, "0x80,cr0,&,!,?{,lr,pc,=,},");
				} else {
					esilprintf (op, "0x80,%s,&,!,?{,lr,pc,=,},", ARG (0));
				}
				break;
			case PPC_BC_NE:
				if (ARG (1)[0] == '\0') {
					esilprintf (op, "cr0,!,!,?{,lr,pc,=,},");
				} else {
					esilprintf (op, "%s,!,!,?{,lr,pc,=,},", ARG (0));
				}
				break;
			case PPC_BC_UN: // unordered
			case PPC_BC_NU: // not unordered
			case PPC_BC_SO: // summary overflow
			case PPC_BC_NS: // not summary overflow
			default:
				break;
			}
			break;
		case PPC_INS_NOR:
			op->type = R_ANAL_OP_TYPE_NOR;
			esilprintf (op, "%s,%s,|,!,%s,=", ARG (2), ARG (1), ARG (0));
			break;
		case PPC_INS_XOR:
		case PPC_INS_XORI:
			op->type = R_ANAL_OP_TYPE_XOR;
			esilprintf (op, "%s,%s,^,%s,=", ARG (2), ARG (1), ARG (0));
			break;
		case PPC_INS_XORIS:
			op->type = R_ANAL_OP_TYPE_XOR;
			esilprintf (op, "16,%s,<<,%s,^,%s,=", ARG (2), ARG (1), ARG (0));
			break;
		case PPC_INS_DIVD:
		case PPC_INS_DIVW:
			op->sign = true;
			op->type = R_ANAL_OP_TYPE_DIV;
			esilprintf (op, "%s,%s,/,%s,=", ARG (2), ARG (1), ARG (0));
			break;
		case PPC_INS_DIVDU:
		case PPC_INS_DIVWU:
			op->type = R_ANAL_OP_TYPE_DIV;
			esilprintf (op, "%s,%s,/,%s,=", ARG (2), ARG (1), ARG (0));
			break;
		case PPC_INS_BL:
		case PPC_INS_BLA:
			op->type = R_ANAL_OP_TYPE_CALL;
			op->jump = IMM (0);
			op->fail = addr + op->size;
			esilprintf (op, "pc,lr,=,%s,pc,=", ARG (0));
			break;
		case PPC_INS_TRAP:
			op->sign = true;
			op->type = R_ANAL_OP_TYPE_TRAP;
			break;
		case PPC_INS_AND:
		case PPC_INS_NAND:
		case PPC_INS_ANDI:
			op->type = R_ANAL_OP_TYPE_AND;
			esilprintf (op, "%s,%s,&,%s,=", ARG (2), ARG (1), ARG (0));
			break;
		case PPC_INS_ANDIS:
			op->type = R_ANAL_OP_TYPE_AND;
			esilprintf (op, "16,%s,<<,%s,&,%s,=", ARG (2), ARG (1), ARG (0));
			break;
		case PPC_INS_OR:
		case PPC_INS_ORI:
			op->type = R_ANAL_OP_TYPE_OR;
			esilprintf (op, "%s,%s,|,%s,=", ARG (2), ARG (1), ARG (0));
			break;
		case PPC_INS_ORIS:
			op->type = R_ANAL_OP_TYPE_OR;
			esilprintf (op, "16,%s,<<,%s,|,%s,=", ARG (2), ARG (1), ARG (0));
			break;
		case PPC_INS_MFPVR:
			op->type = R_ANAL_OP_TYPE_MOV;
			esilprintf (op, "pvr,%s,=", ARG (0));
			break;
		case PPC_INS_MFSPR:
			op->type = R_ANAL_OP_TYPE_MOV;
			esilprintf (op, "%s,%s,=", PPCSPR (1), ARG (0));
			break;
		case PPC_INS_MFCTR:
			op->type = R_ANAL_OP_TYPE_MOV;
			esilprintf (op, "ctr,%s,=", ARG (0));
			break;
		case PPC_INS_MFDCCR:
			op->type = R_ANAL_OP_TYPE_MOV;
			esilprintf (op, "dccr,%s,=", ARG (0));
			break;
		case PPC_INS_MFICCR:
			op->type = R_ANAL_OP_TYPE_MOV;
			esilprintf (op, "iccr,%s,=", ARG (0));
			break;
		case PPC_INS_MFDEAR:
			op->type = R_ANAL_OP_TYPE_MOV;
			esilprintf (op, "dear,%s,=", ARG (0));
			break;
		case PPC_INS_MFMSR:
			op->type = R_ANAL_OP_TYPE_MOV;
			esilprintf (op, "msr,%s,=", ARG (0));
			break;
		case PPC_INS_MTCTR:
			op->type = R_ANAL_OP_TYPE_MOV;
			esilprintf (op, "%s,ctr,=", ARG (0));
			break;
		case PPC_INS_MTDCCR:
			op->type = R_ANAL_OP_TYPE_MOV;
			esilprintf (op, "%s,dccr,=", ARG (0));
			break;
		case PPC_INS_MTICCR:
			op->type = R_ANAL_OP_TYPE_MOV;
			esilprintf (op, "%s,iccr,=", ARG (0));
			break;
		case PPC_INS_MTDEAR:
			op->type = R_ANAL_OP_TYPE_MOV;
			esilprintf (op, "%s,dear,=", ARG (0));
			break;
		case PPC_INS_MTMSR:
		case PPC_INS_MTMSRD:
			op->type = R_ANAL_OP_TYPE_MOV;
			esilprintf (op, "%s,msr,=", ARG (0));
			break;
			// Data Cache Block Zero
		case PPC_INS_DCBZ:
			op->type = R_ANAL_OP_TYPE_STORE;
			esilprintf (op, "%s,%s", ARG (0), ARG2 (1, ",=[128]"));
			break;
		case PPC_INS_CLRLDI:
			op->type = R_ANAL_OP_TYPE_AND;
			esilprintf (op, "%s,%s,&,%s,=", ARG (1), cmask64 (ARG (2), "0x3F"), ARG (0));
			break;
		case PPC_INS_ROTLDI:
			op->type = R_ANAL_OP_TYPE_ROL;
			esilprintf (op, "%s,%s,<<<,%s,=", ARG (2), ARG (1), ARG (0));
			break;
		case PPC_INS_RLDCL:
		case PPC_INS_RLDICL:
			op->type = R_ANAL_OP_TYPE_ROL;
			esilprintf (op, "%s,%s,<<<,%s,&,%s,=", ARG (2), ARG (1), cmask64 (ARG (3), "0x3F"), ARG (0));
			break;
		case PPC_INS_RLDCR:
		case PPC_INS_RLDICR:
			op->type = R_ANAL_OP_TYPE_ROL;
			esilprintf (op, "%s,%s,<<<,%s,&,%s,=", ARG (2), ARG (1), cmask64 (0, ARG (3)), ARG (0));
			break;
		}
		if (mask & R_ANAL_OP_MASK_VAL) {
			op_fillval (op, handle, insn);
		}
		r_strbuf_fini (&op->esil);
		cs_free (insn, n);
		//cs_close (&handle);
	}
	return op->size;
}