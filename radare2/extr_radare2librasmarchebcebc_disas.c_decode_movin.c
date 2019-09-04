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
struct TYPE_7__ {char sign; int n; int /*<<< orphan*/  c; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ebc_index_t ;
struct TYPE_8__ {char* instr; int /*<<< orphan*/  operands; } ;
typedef  TYPE_2__ ebc_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHK_SNPRINTF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int EBC_INSTR_MAXLEN ; 
 int const EBC_OPCODE_MASK ; 
 int /*<<< orphan*/  EBC_OPERANDS_MAXLEN ; 
 scalar_t__ TEST_BIT (int const,int) ; 
 int /*<<< orphan*/  decode_index16 (int const*,TYPE_1__*) ; 
 int /*<<< orphan*/  decode_index32 (int const*,TYPE_1__*) ; 
 int /*<<< orphan*/  decode_index64 (int const*,TYPE_1__*) ; 
 char** instr_names ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int decode_movin(const ut8 *bytes, ebc_command_t *cmd) {
	int ret = 2;
	char p1 = 0;
	char indx1[32] = {0};
	char indx2[32] = {0};
	char op1[32];
	char sign;
	ebc_index_t idx = {0};

	switch (bytes[0] >> 6) {
	case 0: ret = -1; break;
	case 1: p1 = 'w'; break;
	case 2: p1 = 'd'; break;
	case 3: p1 = 'q'; break;
	}

	if (ret < 0) {
		return ret;
	}

	snprintf(cmd->instr, EBC_INSTR_MAXLEN, "%s%c",
			instr_names[bytes[0] & EBC_OPCODE_MASK], p1);

	if (TEST_BIT(bytes[1], 6)) {
		decode_index16(bytes + 2, &idx);

		sign = idx.sign ? '+' : '-';

		snprintf(indx1, 32, "(%c%u, %c%u)", sign,
				idx.n, sign, idx.c);

		ret += 2;
	}

	switch (p1) {
	case 'w':
		decode_index16(bytes + ret, &idx);
		ret += 2;
		break;
	case 'd':
		decode_index32(bytes + ret, &idx);
		ret += 4;
		break;
	case 'q':
		decode_index64(bytes + ret, &idx);
		ret += 8;
		break;
	}

	sign = idx.sign ? '+' : '-';

	snprintf (indx2, 32, "(%c%u, %c%u)", sign, idx.n, sign, idx.c);

	snprintf (op1, 32, "%sr%u", TEST_BIT (bytes[1], 3) ? "@" : "", bytes[1] & 0x7);
	CHK_SNPRINTF (cmd->operands, EBC_OPERANDS_MAXLEN, "%s%s, %s", op1, indx1, indx2);
	return ret;
}