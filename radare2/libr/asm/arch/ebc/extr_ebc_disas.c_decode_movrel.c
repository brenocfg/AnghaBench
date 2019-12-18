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
typedef  unsigned long ut32 ;
typedef  unsigned long ut16 ;
struct TYPE_5__ {char sign; int n; int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ ebc_index_t ;
struct TYPE_6__ {int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;
typedef  TYPE_2__ ebc_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHK_SNPRINTF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  EBC_INSTR_MAXLEN ; 
 int const EBC_OPCODE_MASK ; 
 int /*<<< orphan*/  EBC_OPERANDS_MAXLEN ; 
 scalar_t__ TEST_BIT (int const,int) ; 
 int /*<<< orphan*/  decode_index16 (int const*,TYPE_1__*) ; 
 char** instr_names ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int decode_movrel(const ut8 *bytes, ebc_command_t *cmd) {
	int ret = 2;
	char p1 = 0;
	char op1[32];
	char indx[32] = {0};
	unsigned long immed = 0;
	unsigned formathex = 0;

	switch (bytes[0] >> 6) {
	case 0:
		ret = -1;
		break;
	case 1:
		p1 = 'w';
		formathex = 4;
		break;
	case 2:
		p1 = 'd';
		formathex = 8;
		break;
	case 3:
		p1 = 'q';
		formathex = 16;
		break;
	}

	if (ret < 0) {
		return ret;
	}

	snprintf(cmd->instr, EBC_INSTR_MAXLEN, "%s%c",
			instr_names[bytes[0] & EBC_OPCODE_MASK], p1);
	snprintf(op1, 32, "%sr%u", TEST_BIT(bytes[1], 3) ? "@" : "", bytes[1] & 0x7);

	if (TEST_BIT(bytes[1], 6)) {
		ebc_index_t idx;
		char sign;

		decode_index16(bytes + 2, &idx);
		sign = idx.sign ? '+' : '-';

		snprintf(indx, 32, "(%c%u, %c%u)", sign, idx.n, sign, idx.c);

		ret += 2;
	}

	ut16 v16;
	ut32 v32;
	ut64 v64;
	switch (p1) {
	case 'w':
		v16 = *(ut16 *)(bytes + 2);
		immed = v16;
		ret += 2;
		break;
	case 'd':
		v32 = *(ut32 *)(bytes + 2);
		immed = v32;
		ret += 4;
		break;
	case 'q':
		v64 = *(ut64 *)(bytes + 2);
		immed = v64;
		ret += 8;
		break;
	}

	CHK_SNPRINTF (cmd->operands, EBC_OPERANDS_MAXLEN, "%s%s, 0x%0*lx",
		op1, indx, formathex, immed);
	return ret;
}