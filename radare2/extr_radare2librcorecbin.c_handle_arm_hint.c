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
typedef  int ut64 ;
struct TYPE_6__ {int bits; } ;
struct TYPE_5__ {int /*<<< orphan*/  anal; int /*<<< orphan*/  bin; } ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RBinInfo ;

/* Variables and functions */
 int compute_addr (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  r_anal_hint_set_bits (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void handle_arm_hint(RCore *core, RBinInfo *info, ut64 paddr, ut64 vaddr, int bits, int va) {
	if (info->bits > 32) { // we look at 16 or 32 bit only
		return;
	}

	int force_bits = 0;
	ut64 addr = compute_addr (core->bin, paddr, vaddr, va);
	if (paddr & 1 || bits == 16) {
		force_bits = 16;
	} else if (info->bits == 16 && bits == 32) {
		force_bits = 32;
	} else if (!(paddr & 1) && bits == 32) {
		force_bits = 32;
	}
	if (force_bits) {
		r_anal_hint_set_bits (core->anal, addr, force_bits);
	}
}