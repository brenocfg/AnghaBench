#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  offset; TYPE_1__* anal; } ;
struct TYPE_8__ {int /*<<< orphan*/  esil; } ;

/* Variables and functions */
 TYPE_2__* core ; 
 TYPE_5__* fcn ; 
 int /*<<< orphan*/  help_msg_aft ; 
 int* input ; 
 int /*<<< orphan*/  r_anal_esil_set_pc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_anal_type_match (TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_seek (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seek ; 

int main (int argc, char **argv) {
	r_anal_esil_set_pc (core->anal->esil, fcn ? fcn->addr : core->offset);
	switch (*input) {
	case '\0': // "aft"
	{
		seek = core->offset;
		r_anal_esil_set_pc (core->anal->esil, fcn ? fcn->addr : core->offset);
		r_core_anal_type_match (core, fcn);
		r_core_seek (core, seek, true);
		break;
	}
	case '?':
	default:
		r_core_cmd_help (core, help_msg_aft);
		break;
	}
	return 0;
}