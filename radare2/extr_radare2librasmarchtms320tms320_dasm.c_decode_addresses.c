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
 int /*<<< orphan*/  L16 ; 
 int /*<<< orphan*/  L7 ; 
 int /*<<< orphan*/  L8 ; 
 int /*<<< orphan*/  P24 ; 
 int /*<<< orphan*/  P8 ; 
 int be16 (int) ; 
 int be24 (int) ; 
 scalar_t__ field_valid (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int field_value (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l1 ; 
 int /*<<< orphan*/  l16 ; 
 int /*<<< orphan*/  l3 ; 
 int /*<<< orphan*/  l7 ; 
 int /*<<< orphan*/  substitute (int /*<<< orphan*/ ,char*,char*,int) ; 

void decode_addresses(tms320_dasm_t * dasm)
{
	// program address label

	if (field_valid (dasm, L7)) {
		substitute (dasm->syntax, "L7", "0x%02X", field_value (dasm, L7));
	}
	if (field_valid (dasm, L8)) {
		substitute (dasm->syntax, "L8", "0x%02X", field_value (dasm, L8));
	}
	if (field_valid (dasm, L16)) {
		substitute (dasm->syntax, "L16", "0x%04X", be16 (field_value (dasm, L16)));
	}

	// program address label

	if (field_valid (dasm, l1) && field_valid (dasm, l3)) {
		substitute (dasm->syntax, "l4", "0x%01X", (field_value (dasm, l3) << 1) | field_value (dasm, l1));
	}

	// program memory address

	if (field_valid (dasm, l7)) {
		substitute (dasm->syntax, "pmad", "0x%02X", field_value (dasm, l7));
	}
	if (field_valid (dasm, l16)) {
		substitute (dasm->syntax, "pmad", "0x%04X", be16 (field_value (dasm, l16)));
	}

	// program or dasm address label

	if (field_valid (dasm, P8)) {
		substitute (dasm->syntax, "P8", "0x%02X", field_value (dasm, P8));
	}
	if (field_valid (dasm, P24)) {
		substitute (dasm->syntax, "P24", "0x%06X", be24 (field_value (dasm, P24)));
	}
}