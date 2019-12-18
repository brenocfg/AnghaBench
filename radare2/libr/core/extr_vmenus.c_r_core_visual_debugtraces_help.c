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
 int /*<<< orphan*/  r_cons_any_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_clear00 () ; 
 int /*<<< orphan*/  r_cons_flush () ; 
 int /*<<< orphan*/  r_cons_printf (char*) ; 

__attribute__((used)) static void r_core_visual_debugtraces_help(RCore *core) {
	r_cons_clear00 ();
	r_cons_printf (
			"vbd: Visual Browse Debugtraces:\n\n"
			" q     - quit the bit editor\n"
			" Q     - Quit (jump into the disasm view)\n"
			" j/k   - Select next/previous trace\n"
			" :     - enter command\n");
	r_cons_flush ();
	r_cons_any_key (NULL);
}