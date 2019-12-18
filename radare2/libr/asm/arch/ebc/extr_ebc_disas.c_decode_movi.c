#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  unsigned long ut64 ;
typedef  scalar_t__ ut32 ;
typedef  scalar_t__ ut16 ;
struct TYPE_5__ {char sign; int n; int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ ebc_index_t ;
struct TYPE_6__ {int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;
typedef  TYPE_2__ ebc_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHK_SNPRINTF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,unsigned long) ; 
 int /*<<< orphan*/  EBC_INSTR_MAXLEN ; 
 int const EBC_OPCODE_MASK ; 
 int /*<<< orphan*/  EBC_OPERANDS_MAXLEN ; 
 scalar_t__ TEST_BIT (int const,int) ; 
 int /*<<< orphan*/  decode_index16 (int const*,TYPE_1__*) ; 
 char** instr_names ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int decode_movi(const ut8 *bytes, ebc_command_t *cmd) {
	int ret = 2;
	char p1 = 0, p2 = 0;
	char indx[32] = {0};
	char op1[32];
	unsigned long immed = 0;

	switch (bytes[0] >> 6) {
	case 0: ret = -1; break;
	case 1: p2 = 'w'; break;
	case 2: p2 = 'd'; break;
	case 3: p2 = 'q'; break;
	}

	if (ret < 0) {
		return ret;
	}

	switch ((bytes[1] >> 4) & 0x3) {
	case 0: p1 = 'b'; break;
	case 1: p1 = 'w'; break;
	case 2: p1 = 'd'; break;
	case 3: p1 = 'q'; break;
	}

	snprintf(cmd->instr, EBC_INSTR_MAXLEN, "%s%c%c",
			instr_names[bytes[0] & EBC_OPCODE_MASK], p1, p2);

	if (TEST_BIT(bytes[1], 6)) {
		char sign;
		ebc_index_t idx;

		decode_index16(bytes + 2, &idx);
		sign = idx.sign ? '+' : '-';

		snprintf(indx, 32, "(%c%u, %c%u)", sign, idx.n, sign, idx.c);

		ret += 2;
	}

	switch (p2) {
	ut16 i1;
	ut32 i2;
	ut64 i3;
	case 'w':
		i1 = *(ut16*)(bytes + ret);
		immed = (unsigned long)i1;
		ret += 2;
		break;
	case 'd':
		i2 = *(ut32*)(bytes + ret);
		immed = (unsigned long)i2;
		ret += 4;
		break;
	case 'q':
		i3 = *(ut64*)(bytes + ret);
		immed = i3;
		ret += 8;
		break;
	}

	snprintf (op1, 32, "%sr%u", TEST_BIT (bytes[1], 3) ? "@" : "", bytes[1] & 0x7);
	CHK_SNPRINTF (cmd->operands, EBC_OPERANDS_MAXLEN, "%s%s, %lu", op1, indx, immed);
	return ret;
}