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
typedef  int /*<<< orphan*/  ut16 ;
struct TYPE_5__ {int /*<<< orphan*/  c; int /*<<< orphan*/  n; scalar_t__ sign; } ;
typedef  TYPE_1__ ebc_index_t ;
struct TYPE_6__ {int /*<<< orphan*/  operands; } ;
typedef  TYPE_2__ ebc_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHK_SNPRINTF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  EBC_OPERANDS_MAXLEN ; 
 scalar_t__ TEST_BIT (int const,int) ; 
 int /*<<< orphan*/  decode_index16 (int const*,TYPE_1__*) ; 

__attribute__((used)) static int decode_cmp(const ut8 *bytes, ebc_command_t *cmd) {
	int ret = 2;
	int op1, op2;
	char sign;
	ut16 immed;
	ebc_index_t idx;

	op1 = bytes[1] & 0x07;
	op2 = (bytes[1] >> 4) & 0x07;

	if (TEST_BIT (bytes[0], 7)) {
		ret += 2;
		if (TEST_BIT (bytes[1], 7)) {
			decode_index16 (bytes + 2, &idx);
			sign = idx.sign ? '+' : '-';
			CHK_SNPRINTF (cmd->operands, EBC_OPERANDS_MAXLEN,
				"r%d, @r%d (%c%d, %c%d)",
				op1, op2, sign, idx.n, sign, idx.c);
		} else {
			immed = *(ut16 *)&bytes[2];
			CHK_SNPRINTF (cmd->operands, EBC_OPERANDS_MAXLEN,
				"r%d, r%d %d", op1, op2, immed);
		}
	} else {
		CHK_SNPRINTF (cmd->operands, EBC_OPERANDS_MAXLEN,
			"r%d, r%d", op1, op2);
	}

	return ret;
}