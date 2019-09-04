#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  syntax; } ;
typedef  TYPE_1__ tms320_dasm_t ;

/* Variables and functions */
 int /*<<< orphan*/  D16 ; 
 int /*<<< orphan*/  K16 ; 
 int /*<<< orphan*/  K8 ; 
 int /*<<< orphan*/  SHFT ; 
 int /*<<< orphan*/  SHIFTW ; 
 int be16 (int) ; 
 scalar_t__ field_valid (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int field_value (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  k12 ; 
 int /*<<< orphan*/  k16 ; 
 int /*<<< orphan*/  k3 ; 
 int /*<<< orphan*/  k4 ; 
 int /*<<< orphan*/  k5 ; 
 int /*<<< orphan*/  k8 ; 
 int /*<<< orphan*/  substitute (int /*<<< orphan*/ ,char*,char*,int) ; 

void decode_constants(tms320_dasm_t * dasm)
{
	// signed constant

	if (field_valid (dasm, K8)) {
		substitute (dasm->syntax, "K8", "0x%02X", field_value (dasm, K8));
	}
	if (field_valid (dasm, K16)) {
		substitute (dasm->syntax, "K16", "0x%04X", be16 (field_value (dasm, K16)));
	}

	// unsigned constant

	if (field_valid (dasm, k4)) {
		substitute (dasm->syntax, "K4", "0x%01X", field_value (dasm, k4));
	}
	if (field_valid (dasm, k5)) {
		substitute (dasm->syntax, "k5", "0x%02X", field_value (dasm, k5));
	}
	if (field_valid (dasm, k8)) {
		substitute (dasm->syntax, "k8", "0x%02X", field_value (dasm, k8));
	}

	if (field_valid (dasm, k12)) {
		substitute (dasm->syntax, "k12", "0x%03X", be16 (field_value (dasm, k12)));
	}
	if (field_valid (dasm, k16)) {
		substitute (dasm->syntax, "k16", "0x%04X", be16 (field_value (dasm, k16)));
	}

	if (field_valid (dasm, k4) && field_valid (dasm, k3)) {
		substitute (dasm->syntax, "k7", "0x%02X", (field_value (dasm, k3) << 4) | field_value (dasm, k4));
	}
	if (field_valid (dasm, k4) && field_valid (dasm, k5)) {
		substitute (dasm->syntax, "k9", "0x%03X", (field_value (dasm, k5) << 4) | field_value (dasm, k4));
	}
	if (field_valid (dasm, k4) && field_valid (dasm, k8)) {
		substitute (dasm->syntax, "k12", "0x%03X", (field_value (dasm, k8) << 4) | field_value (dasm, k4));
	}

	// dasm address label

	if (field_valid (dasm, D16)) {
		substitute (dasm->syntax, "D16", "0x%04X", be16 (field_value (dasm, D16)));
	}

	// immediate shift value

	if (field_valid (dasm, SHFT)) {
		substitute (dasm->syntax, "#SHFT", "0x%01X", field_value (dasm, SHFT));
	}
	if (field_valid (dasm, SHIFTW)) {
		substitute (dasm->syntax, "#SHIFTW", "0x%02X", field_value (dasm, SHIFTW));
	}
}