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
typedef  int ut32 ;
typedef  int ut16 ;
typedef  int /*<<< orphan*/  op1c ;
typedef  int /*<<< orphan*/  indx ;
typedef  int /*<<< orphan*/  immed ;
struct TYPE_5__ {char sign; int n; int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ ebc_index_t ;
struct TYPE_6__ {int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;
typedef  TYPE_2__ ebc_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHK_SNPRINTF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int const EBC_CMPIEQ ; 
 int /*<<< orphan*/  EBC_INSTR_MAXLEN ; 
 int const EBC_OPCODE_MASK ; 
 int /*<<< orphan*/  EBC_OPERANDS_MAXLEN ; 
 scalar_t__ TEST_BIT (int const,int) ; 
 int /*<<< orphan*/  decode_index16 (int const*,TYPE_1__*) ; 
 char** instr_names ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int decode_cmpi(const ut8 *bytes, ebc_command_t *cmd) {
	int ret = 2;
	unsigned op1 = bytes[1] & 0x07;
	char op1c[32];
	char indx[32] = {0};
	char immed[32] = {0};
	char *suff[] = {"eq", "lte", "gte", "ulte", "ugte"};

	snprintf (op1c, sizeof (op1c)-1, "%sr%u",
		TEST_BIT(bytes[1], 3) ? "@" : "", op1);

	snprintf (cmd->instr, EBC_INSTR_MAXLEN, "%s%u%c%s",
			instr_names[bytes[0] & EBC_OPCODE_MASK],
			TEST_BIT(bytes[0], 6) ? 64 : 32,
			TEST_BIT(bytes[0], 7) ? 'd' : 'w',
			suff[(bytes[0] & EBC_OPCODE_MASK) - EBC_CMPIEQ]
			);

	if (TEST_BIT (bytes[1], 4)) {
		char sign;
		ebc_index_t idx;

		decode_index16(bytes + 2, &idx);

		sign = idx.sign ? '+' : '-';

		snprintf(indx, sizeof (indx), " (%c%u, %c%u)", sign, idx.n, sign, idx.c);

		ret += 2;
	}

	if (TEST_BIT(bytes[0], 7)) {
		ut32 im = *(ut32*)(bytes + ret);
		snprintf (immed, sizeof (immed), "%u", im);
		ret += 4;
	} else {
		ut16 im = *(ut16*)(bytes + ret);
		snprintf (immed, sizeof (immed), "%u", im);
		ret += 2;
	}

	CHK_SNPRINTF (cmd->operands, EBC_OPERANDS_MAXLEN, "%s%s, %s", op1c, indx, immed);
	return ret;
}