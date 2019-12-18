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
struct h8300_cmd {char* operands; } ;

/* Variables and functions */
#define  H8300_RTE 129 
#define  H8300_RTS 128 
 scalar_t__ decode_opcode (int const*,struct h8300_cmd*) ; 

__attribute__((used)) static int decode_eepmov(const ut8 *bytes, struct h8300_cmd *cmd)
{
	int ret = 4;

	if (decode_opcode(bytes, cmd)) {
		return -1;
	}
	cmd->operands[0] = '\0';

	switch (bytes[0]) {
	case H8300_RTS:
	case H8300_RTE:
		ret = 2;
		break;
	}

	return ret;
}