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
struct winedbg_arm_insn {int thumb; int /*<<< orphan*/ * str_asm; int /*<<< orphan*/ * str_hex; scalar_t__ pc; } ;

/* Variables and functions */
 struct winedbg_arm_insn* malloc (int) ; 

struct winedbg_arm_insn* arm_new() {
	struct winedbg_arm_insn *ret;
	ret = malloc(sizeof(struct winedbg_arm_insn));
	ret->pc = 0;
	ret->thumb = false;
	ret->str_hex = NULL;
	ret->str_asm = NULL;
	return ret;
}