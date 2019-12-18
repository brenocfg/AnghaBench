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
typedef  int /*<<< orphan*/  EStates ;

/* Variables and functions */
 int /*<<< orphan*/  eArrayState ; 
 int /*<<< orphan*/  eBitfieldState ; 
 int /*<<< orphan*/  eCharState ; 
 int /*<<< orphan*/  eDoubleState ; 
 int /*<<< orphan*/  eEnumState ; 
 int /*<<< orphan*/  eLongState ; 
 int /*<<< orphan*/  eMemberState ; 
 int /*<<< orphan*/  eModifierState ; 
 int /*<<< orphan*/  eOneMethodState ; 
 int /*<<< orphan*/  ePointerState ; 
 int /*<<< orphan*/  eShortState ; 
 int /*<<< orphan*/  eStateMax ; 
 int /*<<< orphan*/  eStructState ; 
 int /*<<< orphan*/  eUnionState ; 
 int /*<<< orphan*/  eUnsignedState ; 
 int /*<<< orphan*/  eVoidState ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static EStates convert_to_state(char *cstate) {
	EStates state = eStateMax;

	if (strstr (cstate, "member")) {
		state = eMemberState;
	} else if (strstr (cstate, "pointer")) {
		state = ePointerState;
	} else if (strstr (cstate, "union")) {
		state = eUnionState;
	} else if (strstr (cstate, "struct")) {
		state = eStructState;
	} else if (strstr (cstate, "unsigned")) {
		state = eUnsignedState;
	} else if (strstr (cstate, "short")) {
		state = eShortState;
	} else if (strstr (cstate, "long")) {
		state = eLongState;
	} else if (strstr (cstate, "char")) {
		state = eCharState;
	} else if (strstr (cstate, "modifier")) {
		state = eModifierState;
	} else if (strstr (cstate, "enum")) {
		state = eEnumState;
	} else if (strstr (cstate, "array")) {
		state = eArrayState;
	} else if (strstr (cstate, "onemethod")) {
		state = eOneMethodState;
	} else if (strstr (cstate, "void")) {
		state = eVoidState;
	} else if (strstr (cstate, "double")) {
		state = eDoubleState;
	} else if (strstr (cstate, "bitfield")) {
		state = eBitfieldState;
	}

	return state;
}