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
struct TYPE_3__ {int /*<<< orphan*/  anal; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_1__ RCore ;
typedef  int /*<<< orphan*/  RAnalFunction ;

/* Variables and functions */
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 
 int r_sign_add_refs (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_sign_fcn_refs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool addFcnRefs(RCore *core, RAnalFunction *fcn, const char *name) {
	RList *refs = r_sign_fcn_refs (core->anal, fcn);
	if (!refs) {
		return false;
	}
	bool retval = r_sign_add_refs (core->anal, name, refs);
	r_list_free (refs);
	return retval;
}