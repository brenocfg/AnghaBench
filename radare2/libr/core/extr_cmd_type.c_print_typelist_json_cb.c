#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* anal; } ;
struct TYPE_3__ {int /*<<< orphan*/ * sdb_types; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  TYPE_2__ RCore ;
typedef  int /*<<< orphan*/  PJ ;

/* Variables and functions */
 int atoi (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pj_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_ki (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pj_ks (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * pj_new () ; 
 int /*<<< orphan*/  pj_o (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_printf (char*,int /*<<< orphan*/ ) ; 
 char* r_str_newf (char*,char const*) ; 
 int /*<<< orphan*/  r_str_trim (char*) ; 
 char* sdb_querys (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static int print_typelist_json_cb(void *p, const char *k, const char *v) {
	RCore *core = (RCore *)p;
	PJ *pj = pj_new ();
	pj_o (pj);
	Sdb *sdb = core->anal->sdb_types;
	char *sizecmd = r_str_newf ("type.%s.size", k);
	char *size_s = sdb_querys (sdb, NULL, -1, sizecmd);
	char *formatcmd = r_str_newf ("type.%s", k);
	char *format_s = sdb_querys (sdb, NULL, -1, formatcmd);
	r_str_trim (format_s);
	pj_ks (pj, "type", k);
	pj_ki (pj, "size", size_s ? atoi (size_s) : -1);
	pj_ks (pj, "format", format_s);
	pj_end (pj);
	r_cons_printf ("%s", pj_string (pj));
	pj_free (pj);
	free (size_s);
	free (format_s);
	free (sizecmd);
	free (formatcmd);
	return 1;
}