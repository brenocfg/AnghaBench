#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_12__ {int /*<<< orphan*/  esil; } ;
struct TYPE_11__ {int /*<<< orphan*/  addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  offset; TYPE_9__* anal; } ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RAnalFunction ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  help_msg_aft ; 
 int /*<<< orphan*/  r_anal_esil_set_pc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* r_anal_get_fcn_in (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_cons_break_pop () ; 
 int /*<<< orphan*/  r_cons_break_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_core_anal_type_match (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_seek (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void type_cmd(RCore *core, const char *input) {
	RAnalFunction *fcn = r_anal_get_fcn_in (core->anal, core->offset, -1);
	if (!fcn && *input != '?') {
		eprintf ("cant find function here\n");
		return;
	}
	ut64 seek;
	r_cons_break_push (NULL, NULL);
	switch (*input) {
	case '\0': // "aft"
		seek = core->offset;
		r_anal_esil_set_pc (core->anal->esil, fcn? fcn->addr: core->offset);
		r_core_anal_type_match (core, fcn);
		r_core_seek (core, seek, true);
		break;
	case '?':
		r_core_cmd_help (core, help_msg_aft);
		break;
	}
	r_cons_break_pop ();
}