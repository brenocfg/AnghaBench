#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {char const* name; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ RAnalVar ;
typedef  TYPE_2__ RAnalFunction ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  ARGPREFIX ; 
 int /*<<< orphan*/  VARPREFIX ; 
 TYPE_2__* r_anal_get_fcn_in (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_anal_var_rename (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char const*,char const*,int) ; 
 scalar_t__ r_str_startswith (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void var_rename(RAnal *anal, RAnalVar *v, const char *name, ut64 addr) {
	if (!name || !v) {
		return;
	}
	if (!*name || !strcmp (name , "...")) {
		return;
	}
	bool is_default = (r_str_startswith (v->name, VARPREFIX)
			|| r_str_startswith (v->name, ARGPREFIX))? true: false;
	if (*name == '*') {
		name++;
	}
	// longer name tends to be meaningful like "src" instead of "s1"
	if (!is_default && (strlen (v->name) > strlen (name))) {
		return;
	}
	RAnalFunction *fcn = r_anal_get_fcn_in (anal, addr, 0);
	if (!fcn) {
		return;
	}
	r_anal_var_rename (anal, fcn->addr, 1, v->kind, v->name, name, false);
}