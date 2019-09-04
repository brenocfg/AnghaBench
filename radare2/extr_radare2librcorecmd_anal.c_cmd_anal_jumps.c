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
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  r_core_cmdf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void cmd_anal_jumps(RCore *core, const char *input) {
	r_core_cmdf (core, "af @@= `ax~ref.code.jmp[1]`");
}