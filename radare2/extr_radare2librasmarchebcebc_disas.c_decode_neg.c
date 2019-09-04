#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_4__ {char* instr; } ;
typedef  TYPE_1__ ebc_command_t ;

/* Variables and functions */
 int decode_not (int /*<<< orphan*/  const*,TYPE_1__*) ; 

__attribute__((used)) static int decode_neg(const ut8 *bytes, ebc_command_t *cmd) {
	int ret = decode_not(bytes, cmd);
	cmd->instr[1] = 'e';
	cmd->instr[2] = 'g';
	return ret;
}