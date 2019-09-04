#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {int /*<<< orphan*/  zign_spaces; } ;
struct TYPE_26__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  name; } ;
struct TYPE_25__ {TYPE_5__* anal; } ;
struct TYPE_24__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ RSpace ;
typedef  TYPE_2__ RCore ;
typedef  TYPE_3__ RAnalFunction ;

/* Variables and functions */
 int /*<<< orphan*/  addFcnBytes (TYPE_2__*,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  addFcnGraph (TYPE_2__*,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  addFcnHash (TYPE_2__*,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  addFcnRefs (TYPE_2__*,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  addFcnVars (TYPE_2__*,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  addFcnXRefs (TYPE_2__*,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getFcnComments (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  r_sign_add_addr (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_sign_add_comment (TYPE_5__*,char*,char*) ; 
 int /*<<< orphan*/  r_sign_add_name (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* r_spaces_current (int /*<<< orphan*/ *) ; 
 char* r_str_appendf (char*,char*,int /*<<< orphan*/ ) ; 
 char* r_str_new (char const*) ; 
 char* r_str_newf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void addFcnZign(RCore *core, RAnalFunction *fcn, const char *name) {
	char *zigname = NULL;
	const RSpace *curspace = r_spaces_current (&core->anal->zign_spaces);

	if (name) {
		zigname = r_str_new (name);
	} else {
		if (curspace) {
			zigname = r_str_newf ("%s:", curspace->name);
		}
		zigname = r_str_appendf (zigname, "%s", fcn->name);
	}

	addFcnGraph (core, fcn, zigname);
	addFcnBytes (core, fcn, zigname);
	addFcnXRefs (core, fcn, zigname);
	addFcnRefs (core, fcn, zigname);
	addFcnVars (core, fcn, zigname);
	addFcnHash (core, fcn, zigname);
	if (strcmp (zigname, fcn->name)) {
		r_sign_add_name (core->anal, zigname, fcn->name);
	}
	char *comments = getFcnComments (core, fcn);
	if (comments) {
		r_sign_add_comment (core->anal, zigname, comments);
	}
	r_sign_add_addr (core->anal, zigname, fcn->addr);

	free (zigname);
}