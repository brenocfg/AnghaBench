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
typedef  int /*<<< orphan*/  RListFree ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 scalar_t__ free ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_newf (int /*<<< orphan*/ ) ; 
 int r_sign_add_refs (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_str_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_str_word_get0 (char const*,int) ; 

__attribute__((used)) static bool addRefsZign(RCore *core, const char *name, const char *args0, int nargs) {
	int i = 0;
	if (nargs < 1) {
		eprintf ("error: invalid syntax\n");
		return false;
	}

	RList *refs = r_list_newf ((RListFree) free);
	for (i = 0; i < nargs; i++) {
		r_list_append (refs, r_str_new (r_str_word_get0 (args0, i)));
	}

	bool retval = r_sign_add_refs (core->anal, name, refs);
	r_list_free (refs);
	return retval;
}