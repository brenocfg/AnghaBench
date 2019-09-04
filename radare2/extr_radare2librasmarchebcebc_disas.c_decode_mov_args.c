#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_7__ {int n; int /*<<< orphan*/  c; int /*<<< orphan*/  sign; } ;
typedef  TYPE_1__ ebc_index_t ;
struct TYPE_8__ {int /*<<< orphan*/  operands; } ;
typedef  TYPE_2__ ebc_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHK_SNPRINTF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,char*,char*) ; 
#define  EBC_MOVBD 136 
#define  EBC_MOVBW 135 
#define  EBC_MOVDD 134 
#define  EBC_MOVDW 133 
#define  EBC_MOVQD 132 
#define  EBC_MOVQQ 131 
#define  EBC_MOVQW 130 
#define  EBC_MOVWD 129 
#define  EBC_MOVWW 128 
 int const EBC_OPCODE_MASK ; 
 int /*<<< orphan*/  EBC_OPERANDS_MAXLEN ; 
 scalar_t__ TEST_BIT (int const,int) ; 
 int /*<<< orphan*/  decode_index16 (int const*,TYPE_1__*) ; 
 int /*<<< orphan*/  decode_index32 (int const*,TYPE_1__*) ; 
 int /*<<< orphan*/  decode_index64 (int const*,TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int decode_mov_args(const ut8 *bytes, ebc_command_t *cmd) {
	int ret = 2;
	unsigned op1, op2;
	char op1c[32], op2c[32];
	char ind1[32] = {0}, ind2[32] = {0};
	ebc_index_t idx;
	char sign;

	op1 = bytes[1] & 0x07;
	op2 = (bytes[1] >> 4) & 0x07;

	snprintf(op1c, 32, "%sr%u", TEST_BIT(bytes[1], 3) ? "@" : "", op1);
	snprintf(op2c, 32, "%sr%u", TEST_BIT(bytes[1], 7) ? "@" : "", op2);

	switch (bytes[0] & EBC_OPCODE_MASK) {
	case EBC_MOVBW:
	case EBC_MOVWW:
	case EBC_MOVDW:
	case EBC_MOVQW:
		if (TEST_BIT(bytes[0], 7)) {
			decode_index16(bytes + ret, &idx);
			sign = idx.sign? '+': '-';
			snprintf(ind1, 32,"(%c%u, %c%u)", sign,
					idx.n, sign, idx.c);
			ret += 2;
		}
		if (TEST_BIT(bytes[0], 6)) {
			decode_index16(bytes + ret, &idx);
			sign = idx.sign? '+': '-';
			snprintf(ind2, 32, "(%c%u, %c%u)", sign,
					idx.n, sign, idx.c);
			ret += 2;
		}
		break;
	case EBC_MOVBD:
	case EBC_MOVWD:
	case EBC_MOVDD:
	case EBC_MOVQD:
		if (TEST_BIT(bytes[0], 7)) {
			decode_index32(bytes + ret, &idx);
			sign = idx.sign? '+': '-';
			snprintf(ind1, 32, "(%c%u, %c%u)", sign,
					idx.n, sign, idx.c);
			ret += 4;
		}
		if (TEST_BIT(bytes[0], 6)) {
			decode_index32(bytes + ret, &idx);
			sign = idx.sign? '+': '-';
			snprintf(ind2, 32, "(%c%u, %c%u)", sign,
					idx.n, sign, idx.c);
			ret += 4;
		}
		break;
	case EBC_MOVQQ:
		if (TEST_BIT(bytes[0], 7)) {
			decode_index64(bytes + ret, &idx);
			sign = idx.sign? '+': '-';
			snprintf(ind1, 32, "(%c%u, %c%u)", sign,
					idx.n, sign, idx.c);
			ret += 8;
		}
		if (TEST_BIT(bytes[0], 6)) {
			decode_index64(bytes + ret, &idx);
			sign = idx.sign? '+': '-';
			snprintf(ind1, 32, "(%c%u, %c%u)", sign,
					idx.n, sign, idx.c);
			ret += 8;
		}
		break;
	}

	CHK_SNPRINTF (cmd->operands, EBC_OPERANDS_MAXLEN, "%s%s, %s%s",
		op1c, ind1, op2c, ind2);

	return ret;
}