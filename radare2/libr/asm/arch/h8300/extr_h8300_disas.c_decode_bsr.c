#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ ut8 ;
struct h8300_cmd {int /*<<< orphan*/  operands; } ;
typedef  int st8 ;

/* Variables and functions */
 int /*<<< orphan*/  H8300_INSTR_MAXLEN ; 
 scalar_t__ decode_opcode (scalar_t__ const*,struct h8300_cmd*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int decode_bsr(const ut8 *bytes, struct h8300_cmd *cmd)
{
	int ret = 2;

	if (decode_opcode(bytes, cmd)) {
		return -1;
	}

	snprintf(cmd->operands, H8300_INSTR_MAXLEN, ".%d",
			(st8)bytes[1]);

	return ret;
}