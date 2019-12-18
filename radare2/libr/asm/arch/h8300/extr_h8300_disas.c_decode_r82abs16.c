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
typedef  int ut16 ;
struct h8300_cmd {int /*<<< orphan*/  operands; int /*<<< orphan*/  instr; } ;

/* Variables and functions */
 int /*<<< orphan*/  H8300_INSTR_MAXLEN ; 
 scalar_t__ decode_opcode (int const*,struct h8300_cmd*) ; 
 int r_read_at_be16 (int const*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int const,int const,char) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_r82abs16(const ut8 *bytes, struct h8300_cmd *cmd)
{
	int ret = 4;
	ut16 abs;

	if (bytes[0] == 0x6A && bytes[1] >> 4 == 4) {
		strncpy(cmd->instr, "movfpe", H8300_INSTR_MAXLEN);
	} else if (bytes[0] == 0x6A && bytes[1] >> 4 == 0xC) {
		strncpy(cmd->instr, "movtpe", H8300_INSTR_MAXLEN);
	} else if (decode_opcode(bytes, cmd)) {
		return -1;
	}

	abs = r_read_at_be16 (bytes, 2);

	if (bytes[1] & 0x80) {
		snprintf(cmd->operands, H8300_INSTR_MAXLEN, "r%u%c,@0x%x:16",
			bytes[1] & 0x7, bytes[1] & 0x8 ? 'l' : 'h', abs);
	} else {
		snprintf(cmd->operands, H8300_INSTR_MAXLEN, "@0x%x:16,r%u%c",
			abs, bytes[1] & 0x7,
			bytes[1] & 0x8 ? 'l' : 'h');
	}

	return ret;
}