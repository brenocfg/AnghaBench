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
struct winedbg_arm_insn {struct winedbg_arm_insn* str_asm; struct winedbg_arm_insn* str_hex; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct winedbg_arm_insn*) ; 

void* arm_free(struct winedbg_arm_insn *arminsn) {
	free(arminsn->str_hex);
	free(arminsn->str_asm);
	free(arminsn);
	return NULL;
}