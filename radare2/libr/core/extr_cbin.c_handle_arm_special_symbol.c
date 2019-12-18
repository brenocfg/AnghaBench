#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  paddr; } ;
struct TYPE_5__ {int /*<<< orphan*/  anal; int /*<<< orphan*/  bin; } ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RBinSymbol ;

/* Variables and functions */
 int /*<<< orphan*/  R_LOG_WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_anal_hint_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void handle_arm_special_symbol(RCore *core, RBinSymbol *symbol, int va) {
	ut64 addr = compute_addr (core->bin, symbol->paddr, symbol->vaddr, va);
	if (!strcmp (symbol->name, "$a")) {
		r_anal_hint_set_bits (core->anal, addr, 32);
	} else if (!strcmp (symbol->name, "$x")) {
		r_anal_hint_set_bits (core->anal, addr, 64);
	} else if (!strcmp (symbol->name, "$t")) {
		r_anal_hint_set_bits (core->anal, addr, 16);
	} else if (!strcmp (symbol->name, "$d")) {
		// TODO: we could add data meta type at addr, but sometimes $d
		// is in the middle of the code and it would make the code less
		// readable.
	} else {
		R_LOG_WARN ("Special symbol %s not handled\n", symbol->name);
	}
}