#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_6__ {int n; int /*<<< orphan*/  c; scalar_t__ sign; } ;
typedef  TYPE_1__ ebc_index_t ;
struct TYPE_7__ {int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;
typedef  TYPE_2__ ebc_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHK_SNPRINTF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  EBC_INSTR_MAXLEN ; 
 int const EBC_MOVNW ; 
 int const EBC_OPCODE_MASK ; 
 int /*<<< orphan*/  EBC_OPERANDS_MAXLEN ; 
 scalar_t__ TEST_BIT (int const,int) ; 
 int /*<<< orphan*/  decode_index16 (int const*,TYPE_1__*) ; 
 int /*<<< orphan*/  decode_index32 (int const*,TYPE_1__*) ; 
 char** instr_names ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int decode_movn(const ut8 *bytes, ebc_command_t *cmd) {
	int ret = 2;
	unsigned op1 = bytes[1] & 0x07;
	unsigned op2 = (bytes[1] >> 4) & 0x07;
	char op1c[32], op2c[32];
	char indx1[32] = {0};
	char indx2[32] = {0};
	char sign;
	ebc_index_t idx;

	snprintf(cmd->instr, EBC_INSTR_MAXLEN, "%s",
			instr_names[bytes[0] & EBC_OPCODE_MASK]);

	snprintf(op1c, 32, "%sr%u", TEST_BIT(bytes[1], 3) ? "@" : "", op1);
	snprintf(op2c, 32, "%sr%u", TEST_BIT(bytes[1], 7) ? "@" : "", op2);

	if ((bytes[0] & EBC_OPCODE_MASK) == EBC_MOVNW) {
		if (TEST_BIT(bytes[0], 7)) {
			decode_index16(bytes + ret, &idx);
			sign = idx.sign ? '+' : '-';
			snprintf(indx1, 32, "(%c%u, %c%u)", sign, idx.n, sign, idx.c);
			ret += 2;
		}
		if (TEST_BIT(bytes[0], 6)) {
			decode_index16(bytes + ret, &idx);
			sign = idx.sign ? '+' : '-';
			snprintf(indx2, 32, "(%c%u, %c%u)", sign, idx.n, sign, idx.c);
			ret += 2;
		}
	} else {
		if (TEST_BIT(bytes[0], 7)) {
			decode_index32(bytes + ret, &idx);
			sign = idx.sign ? '+' : '-';
			snprintf(indx1, 32, "(%c%u, %c%u)", sign, idx.n, sign, idx.c);
			ret += 4;
		}
		if (TEST_BIT(bytes[0], 6)) {
			decode_index32(bytes + ret, &idx);
			sign = idx.sign ? '+' : '-';
			snprintf(indx2, 32, "(%c%u, %c%u)", sign, idx.n, sign, idx.c);
			ret += 4;
		}
	}

	CHK_SNPRINTF (cmd->operands, EBC_OPERANDS_MAXLEN, "%s%s, %s%s", op1c, indx1, op2c, indx2);
	return ret;
}