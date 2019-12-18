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
 int /*<<< orphan*/  R ; 
 int /*<<< orphan*/  U ; 
 scalar_t__ field_valid (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ field_value (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g ; 
 int /*<<< orphan*/  substitute (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  u ; 

void decode_bits(tms320_dasm_t * dasm)
{
	// rounding
	if (field_valid (dasm, R)) {
		substitute (dasm->syntax, "[r]", "%s", field_value (dasm, R) ? "r" : "");
	}

	// unsigned
	if (field_valid (dasm, u)) {
		substitute (dasm->syntax, "[u]", "%s", field_value (dasm, u) ? "u" : "");
	}

	// 40 keyword
	if (field_valid (dasm, g)) {
		substitute (dasm->syntax, "[40]", "%s", field_value (dasm, g) ? "40" : "");
	}

	// T3 update
	if (field_valid (dasm, U)) {
		substitute (dasm->syntax, "[T3 = ]", "%s", field_value (dasm, U) ? "t3=" : "");
	}
}