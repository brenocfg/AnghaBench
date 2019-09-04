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

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_printf (char*,...) ; 
 char* r_str_trim_ro (char const*) ; 
 char* sdb_const_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_fmt (char*,char const*,...) ; 
 char* sdb_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sdb_num_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* sdb_querys (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void printFunctionTypeC(RCore *core, const char *input) {
	Sdb *TDB = core->anal->sdb_types;
	char *res = sdb_querys (TDB, NULL, -1, sdb_fmt ("func.%s.args", input));
	const char *name = r_str_trim_ro (input);
	int i, args = sdb_num_get (TDB, sdb_fmt ("func.%s.args", name), 0);
	const char *ret = sdb_const_get (TDB, sdb_fmt ("func.%s.ret", name), 0);
	if (!ret || !name) {
		// missing function name specified
		return;
	}

	r_cons_printf ("%s %s (", ret, name);
	for (i = 0; i < args; i++) {
		char *type = sdb_get (TDB, sdb_fmt ("func.%s.arg.%d", name, i), 0);
		char *name = strchr (type, ',');
		if (name) {
			*name++ = 0;
		}
		r_cons_printf ("%s%s %s", i==0? "": ", ", type, name);
	}
	r_cons_printf (");\n");
	free (res);
}