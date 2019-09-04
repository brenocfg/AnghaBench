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

/* Variables and functions */
 int TC_ACT_EXT_OPCODE (int) ; 
 int TC_ACT_EXT_OPCODE_MAX ; 
 int TC_ACT_UNSPEC ; 
 int TC_ACT_VALUE_MAX ; 

__attribute__((used)) static bool tcf_action_valid(int action)
{
	int opcode = TC_ACT_EXT_OPCODE(action);

	if (!opcode)
		return action <= TC_ACT_VALUE_MAX;
	return opcode <= TC_ACT_EXT_OPCODE_MAX || action == TC_ACT_UNSPEC;
}