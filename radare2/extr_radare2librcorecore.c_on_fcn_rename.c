#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RAnalFunction ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 char* r_config_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_core_cmd0 (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  r_core_seek (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int on_fcn_rename(RAnal *_anal, void* _user, RAnalFunction *fcn, const char *oname) {
	RCore *core = (RCore*)_user;
	const char *cmd = r_config_get (core->config, "cmd.fcn.rename");
	if (cmd && *cmd) {
		// XXX: wat do with old name here?
		ut64 oaddr = core->offset;
		ut64 addr = fcn->addr;
		r_core_seek (core, addr, 1);
		r_core_cmd0 (core, cmd);
		r_core_seek (core, oaddr, 1);
	}
	return 0;
}