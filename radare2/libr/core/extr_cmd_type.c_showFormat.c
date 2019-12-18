#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* anal; } ;
struct TYPE_4__ {int /*<<< orphan*/  sdb_types; } ;
typedef  TYPE_2__ RCore ;
typedef  int /*<<< orphan*/  PJ ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pj_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_ks (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * pj_new () ; 
 int /*<<< orphan*/  pj_o (int /*<<< orphan*/ *) ; 
 char* pj_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_printf (char*,char const*,...) ; 
 int /*<<< orphan*/  r_str_trim (char*) ; 
 char* r_type_format (int /*<<< orphan*/ ,char const*) ; 
 char* sdb_const_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void showFormat(RCore *core, const char *name, int mode) {
	const char *isenum = sdb_const_get (core->anal->sdb_types, name, 0);
	if (isenum && !strcmp (isenum, "enum")) {
		eprintf ("IS ENUM\n");
	} else {
		char *fmt = r_type_format (core->anal->sdb_types, name);
		if (fmt) {
			r_str_trim (fmt);
			if (mode == 'j') {
				PJ *pj = pj_new ();
				if (!pj) {
					return;
				}
				pj_o (pj);
				pj_ks (pj, "name", name);
				pj_ks (pj, "format", fmt);
				pj_end (pj);
				r_cons_printf ("%s", pj_string (pj));
				pj_free (pj);
			} else {
				if (mode) {
					r_cons_printf ("pf.%s %s\n", name, fmt);
				} else {
					r_cons_printf ("pf %s\n", fmt);
				}
			}
			free (fmt);
		} else {
			eprintf ("Cannot find '%s' type\n", name);
		}
	}
}