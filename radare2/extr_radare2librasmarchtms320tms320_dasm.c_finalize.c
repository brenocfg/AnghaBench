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
struct TYPE_4__ {int /*<<< orphan*/ * insn; int /*<<< orphan*/  syntax; } ;
typedef  TYPE_1__ tms320_dasm_t ;
typedef  int /*<<< orphan*/  insn_item_t ;

/* Variables and functions */
 scalar_t__ field_value (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q_cr ; 
 int /*<<< orphan*/  q_lr ; 
 int /*<<< orphan*/  replace (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  substitute (int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static insn_item_t * finalize(tms320_dasm_t * dasm)
{
	// remove odd spaces

	substitute(dasm->syntax, "  ", "%s", " ");

	// add some qualifiers

	if (field_value (dasm, q_lr)) {
		replace (dasm->syntax, " ", ".lr ");
	}
	if (field_value (dasm, q_cr)) {
		replace (dasm->syntax, " ", ".cr ");
	}

	return dasm->insn;
}