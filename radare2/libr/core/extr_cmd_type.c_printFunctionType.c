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
struct TYPE_4__ {int /*<<< orphan*/ * sdb_types; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  TYPE_2__ RCore ;
typedef  int /*<<< orphan*/  PJ ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pj_a (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_k (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pj_ks (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * pj_new () ; 
 int /*<<< orphan*/  pj_o (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_printf (char*,int /*<<< orphan*/ ) ; 
 char* r_str_trim_ro (char const*) ; 
 char* sdb_const_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_fmt (char*,char const*,...) ; 
 char* sdb_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sdb_num_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* sdb_querys (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void printFunctionType(RCore *core, const char *input) {
	Sdb *TDB = core->anal->sdb_types;
	PJ *pj = pj_new ();
	if (!pj) {
		return;
	}
	pj_o (pj);
	char *res = sdb_querys (TDB, NULL, -1, sdb_fmt ("func.%s.args", input));
	const char *name = r_str_trim_ro (input);
	int i, args = sdb_num_get (TDB, sdb_fmt ("func.%s.args", name), 0);
	pj_ks (pj, "name", name);
	pj_ks (pj, "ret", sdb_const_get (TDB, sdb_fmt ("func.%s.ret", name), 0));
	pj_k (pj, "args");
	pj_a (pj);
	for (i = 0; i < args; i++) {
		char *type = sdb_get (TDB, sdb_fmt ("func.%s.arg.%d", name, i), 0);
		if (!type) {
			continue;
		}
		char *name = strchr (type, ',');
		if (name) {
			*name++ = 0;
		}
		pj_o (pj);
		pj_ks (pj, "type", type);
		if (name) {
			pj_ks (pj, "name", name);
		} else {
			pj_ks (pj, "name", "(null)");
		}
		pj_end (pj);
	}
	pj_end (pj);
	pj_end (pj);
	r_cons_printf ("%s", pj_string (pj));
	pj_free (pj);
	free (res);
}