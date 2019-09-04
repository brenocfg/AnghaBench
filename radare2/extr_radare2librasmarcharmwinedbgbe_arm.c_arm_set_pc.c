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
typedef  int /*<<< orphan*/  ut64 ;
struct winedbg_arm_insn {int /*<<< orphan*/  pc; } ;

/* Variables and functions */

void arm_set_pc(struct winedbg_arm_insn *arminsn, ut64 pc) {
	arminsn->pc = pc;
}