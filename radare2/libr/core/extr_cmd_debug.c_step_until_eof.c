#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_3__ {int /*<<< orphan*/  dbg; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  r_cons_break_pop () ; 
 int /*<<< orphan*/  r_cons_break_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ r_debug_reg_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_debug_step_over (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int step_until_eof(RCore *core) {
	int maxLoops = 200000;
	ut64 off, now = r_debug_reg_get (core->dbg, "SP");
	r_cons_break_push (NULL, NULL);
	do {
		// XXX (HACK!)
		r_debug_step_over (core->dbg, 1);
		off = r_debug_reg_get (core->dbg, "SP");
		// check breakpoint here
		if (--maxLoops < 0) {
			eprintf ("Step loop limit exceeded\n");
			break;
		}
	} while (off <= now);
	r_cons_break_pop ();
	return true;
}