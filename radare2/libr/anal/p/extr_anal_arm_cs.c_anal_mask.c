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
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
typedef  int ut32 ;
struct TYPE_12__ {int bits; int /*<<< orphan*/  big_endian; } ;
struct TYPE_11__ {scalar_t__ bits; scalar_t__ ptr; scalar_t__ jump; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  TYPE_1__ RAnalHint ;
typedef  TYPE_3__ RAnal ;

/* Variables and functions */
#define  ARM64_INS_ADR 174 
#define  ARM64_INS_ADRP 173 
#define  ARM64_INS_B 172 
#define  ARM64_INS_BL 171 
#define  ARM64_INS_CBNZ 170 
#define  ARM64_INS_CBZ 169 
#define  ARM64_INS_LDNP 168 
#define  ARM64_INS_LDP 167 
#define  ARM64_INS_LDPSW 166 
#define  ARM64_INS_LDR 165 
#define  ARM64_INS_LDRB 164 
#define  ARM64_INS_LDRH 163 
#define  ARM64_INS_LDRSB 162 
#define  ARM64_INS_LDRSH 161 
#define  ARM64_INS_LDRSW 160 
#define  ARM64_INS_LDTR 159 
#define  ARM64_INS_LDTRB 158 
#define  ARM64_INS_LDTRH 157 
#define  ARM64_INS_LDTRSB 156 
#define  ARM64_INS_LDTRSH 155 
#define  ARM64_INS_LDTRSW 154 
#define  ARM64_INS_LDUR 153 
#define  ARM64_INS_LDURB 152 
#define  ARM64_INS_LDURH 151 
#define  ARM64_INS_LDURSB 150 
#define  ARM64_INS_LDURSH 149 
#define  ARM64_INS_LDURSW 148 
#define  ARM64_INS_LDXP 147 
#define  ARM64_INS_LDXR 146 
#define  ARM64_INS_LDXRB 145 
#define  ARM64_INS_LDXRH 144 
#define  ARM64_INS_STNP 143 
#define  ARM64_INS_STP 142 
#define  ARM64_INS_STR 141 
#define  ARM64_INS_STRB 140 
#define  ARM64_INS_STRH 139 
#define  ARM64_INS_STTR 138 
#define  ARM64_INS_STTRB 137 
#define  ARM64_INS_STTRH 136 
#define  ARM64_INS_STUR 135 
#define  ARM64_INS_STURB 134 
#define  ARM64_INS_STURH 133 
#define  ARM64_INS_STXR 132 
#define  ARM64_INS_STXRB 131 
#define  ARM64_INS_STXRH 130 
#define  ARM64_INS_TBNZ 129 
#define  ARM64_INS_TBZ 128 
 int /*<<< orphan*/  R_ANAL_OP_MASK_BASIC ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_CJMP ; 
 scalar_t__ UT64_MAX ; 
 int analop (TYPE_3__*,TYPE_1__*,scalar_t__,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__* r_anal_hint_get (TYPE_3__*,scalar_t__) ; 
 TYPE_1__* r_anal_op_new () ; 
 int r_read_ble (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_write_ble (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ut8 *anal_mask(RAnal *anal, int size, const ut8 *data, ut64 at) {
	RAnalOp *op = NULL;
	ut8 *ret = NULL;
	int oplen, idx = 0, obits = anal->bits;
	RAnalHint *hint = NULL;

	if (!data) {
		return NULL;
	}

	op = r_anal_op_new ();
	ret = malloc (size);
	memset (ret, 0xff, size);

	while (idx < size) {
		hint = r_anal_hint_get (anal, at + idx);
		if (hint) {
			if (hint->bits != 0) {
				anal->bits = hint->bits;
			}
			free (hint);
		}

		if ((oplen = analop (anal, op, at + idx, data + idx, size - idx, R_ANAL_OP_MASK_BASIC)) < 1) {
			break;
		}
		if (op->ptr != UT64_MAX || op->jump != UT64_MAX) {
			ut32 opcode = r_read_ble (data + idx, anal->big_endian, oplen * 8);
			switch (oplen) {
			case 2:
				memcpy (ret + idx, "\xf0\x00", 2);
				break;
			case 4:
				if (anal->bits == 64) {
					switch (op->id) {
					case ARM64_INS_LDP:
					case ARM64_INS_LDXP:
					case ARM64_INS_LDXR:
					case ARM64_INS_LDXRB:
					case ARM64_INS_LDXRH:
					case ARM64_INS_LDPSW:
					case ARM64_INS_LDNP:
					case ARM64_INS_LDTR:
					case ARM64_INS_LDTRB:
					case ARM64_INS_LDTRH:
					case ARM64_INS_LDTRSB:
					case ARM64_INS_LDTRSH:
					case ARM64_INS_LDTRSW:
					case ARM64_INS_LDUR:
					case ARM64_INS_LDURB:
					case ARM64_INS_LDURH:
					case ARM64_INS_LDURSB:
					case ARM64_INS_LDURSH:
					case ARM64_INS_LDURSW:
					case ARM64_INS_STP:
					case ARM64_INS_STNP:
					case ARM64_INS_STXR:
					case ARM64_INS_STXRB:
					case ARM64_INS_STXRH:
						r_write_ble (ret + idx, 0xffffffff, anal->big_endian, 32);
						break;
					case ARM64_INS_STRB:
					case ARM64_INS_STURB:
					case ARM64_INS_STURH:
					case ARM64_INS_STUR:
					case ARM64_INS_STR:
					case ARM64_INS_STTR:
					case ARM64_INS_STTRB:
					case ARM64_INS_STRH:
					case ARM64_INS_STTRH:
					case ARM64_INS_LDR:
					case ARM64_INS_LDRB:
					case ARM64_INS_LDRH:
					case ARM64_INS_LDRSB:
					case ARM64_INS_LDRSW:
					case ARM64_INS_LDRSH: {
						bool is_literal = (opcode & 0x38000000) == 0x18000000;
						if (is_literal) {
							r_write_ble (ret + idx, 0xff000000, anal->big_endian, 32);
						} else {
							r_write_ble (ret + idx, 0xffffffff, anal->big_endian, 32);
						}
						break;
					}
					case ARM64_INS_B:
					case ARM64_INS_BL:
					case ARM64_INS_CBZ:
					case ARM64_INS_CBNZ:
						if (op->type == R_ANAL_OP_TYPE_CJMP) {
							r_write_ble (ret + idx, 0xff00001f, anal->big_endian, 32);
						} else {
							r_write_ble (ret + idx, 0xfc000000, anal->big_endian, 32);
						}
						break;
					case ARM64_INS_TBZ:
					case ARM64_INS_TBNZ:
						r_write_ble (ret + idx, 0xfff8001f, anal->big_endian, 32);
						break;
					case ARM64_INS_ADR:
					case ARM64_INS_ADRP:
						r_write_ble (ret + idx, 0xff00001f, anal->big_endian, 32);
						break;
					default:
						r_write_ble (ret + idx, 0xfff00000, anal->big_endian, 32);
					}
				} else {
					r_write_ble (ret + idx, 0xfff00000, anal->big_endian, 32);
				}
				break;
			}
		}
		idx += oplen;
	}

	anal->bits = obits;
	free (op);

	return ret;
}