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
typedef  int ut8 ;
struct h8300_cmd {int /*<<< orphan*/  operands; } ;

/* Variables and functions */
 int /*<<< orphan*/  H8300_INSTR_MAXLEN ; 
 scalar_t__ decode_opcode_4bit (int const*,struct h8300_cmd*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int const,int const,char) ; 

__attribute__((used)) static int decode_abs2r_short(const ut8 *bytes, struct h8300_cmd *cmd)
{
	int ret = 2;

	if (decode_opcode_4bit(bytes, cmd)) {
		return -1;
	}

	snprintf(cmd->operands, H8300_INSTR_MAXLEN,
			"@0x%x:8,r%u%c",
				bytes[1], bytes[0] & 0x7,
				bytes[0] & 0x8 ? 'l' : 'h');

	return ret;
}