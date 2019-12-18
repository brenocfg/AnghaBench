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
struct TYPE_3__ {int break_loop; int /*<<< orphan*/  dbg; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  r_cons_break_pop () ; 
 int /*<<< orphan*/  r_cons_break_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ r_cons_is_breaked () ; 
 scalar_t__ r_debug_is_dead (int /*<<< orphan*/ ) ; 
 scalar_t__ r_debug_reg_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_debug_step (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int step_until(RCore *core, ut64 addr) {
	ut64 off = r_debug_reg_get (core->dbg, "PC");
	if (!off) {
		eprintf ("Cannot 'drn PC'\n");
		return false;
	}
	if (!addr) {
		eprintf ("Cannot continue until address 0\n");
		return false;
	}
	r_cons_break_push (NULL, NULL);
	do {
		if (r_cons_is_breaked ()) {
			core->break_loop = true;
			break;
		}
		if (r_debug_is_dead (core->dbg)) {
			core->break_loop = true;
			break;
		}
		r_debug_step (core->dbg, 1);
		off = r_debug_reg_get (core->dbg, "PC");
		// check breakpoint here
	} while (off != addr);
	r_cons_break_pop ();
	return true;
}