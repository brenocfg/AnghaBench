#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* anal; } ;
struct TYPE_10__ {int break_loop; TYPE_2__* anal; TYPE_5__* dbg; } ;
struct TYPE_9__ {int /*<<< orphan*/  esil; } ;
struct TYPE_8__ {int /*<<< orphan*/  esil; } ;
typedef  TYPE_3__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  R_REG_TYPE_ALL ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 scalar_t__ r_anal_esil_condition (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  r_cons_break_pop () ; 
 int /*<<< orphan*/  r_cons_break_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ r_cons_is_breaked () ; 
 scalar_t__ r_debug_is_dead (TYPE_5__*) ; 
 int /*<<< orphan*/  r_debug_reg_sync (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_debug_step (TYPE_5__*,int) ; 

__attribute__((used)) static int step_until_esil(RCore *core, const char *esilstr) {
	if (!core || !esilstr || !core->dbg || !core->dbg->anal \
			|| !core->dbg->anal->esil) {
		eprintf ("Not initialized %p. Run 'aei' first.\n", core->anal->esil);
		return false;
	}
	r_cons_break_push (NULL, NULL);
	for (;;) {
		if (r_cons_is_breaked ()) {
			core->break_loop = true;
			break;
		}
		if (r_debug_is_dead (core->dbg)) {
			core->break_loop = true;
			break;
		}
		r_debug_step (core->dbg, 1);
		r_debug_reg_sync (core->dbg, R_REG_TYPE_ALL, false);
		if (r_anal_esil_condition (core->anal->esil, esilstr)) {
			eprintf ("ESIL BREAK!\n");
			break;
		}
	}
	r_cons_break_pop ();
	return true;
}