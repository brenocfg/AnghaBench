#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  trace_clone; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_value; } ;
struct TYPE_6__ {TYPE_4__* dbg; TYPE_1__* io; } ;
struct TYPE_5__ {scalar_t__ debug; } ;
typedef  TYPE_2__ RCore ;
typedef  TYPE_3__ RConfigNode ;

/* Variables and functions */
 int /*<<< orphan*/  r_debug_attach (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cb_dbg_clone(void *user, void *data) {
	RCore *core = (RCore*) user;
	RConfigNode *node = (RConfigNode*) data;
	core->dbg->trace_clone = node->i_value;
	if (core->io->debug) {
		r_debug_attach (core->dbg, core->dbg->pid);
	}
	return true;
}