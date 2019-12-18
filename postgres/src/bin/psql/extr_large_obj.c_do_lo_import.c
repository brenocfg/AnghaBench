#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  vars; int /*<<< orphan*/  db; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  MCXT_ALLOC_NO_OOM ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQescapeStringConn (int /*<<< orphan*/ ,char*,char const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PSQLexec (char*) ; 
 int /*<<< orphan*/  ResetCancelConn () ; 
 int /*<<< orphan*/  SetCancelConn () ; 
 int /*<<< orphan*/  SetVariable (int /*<<< orphan*/ ,char*,char*) ; 
 int fail_lo_xact (char*,int) ; 
 int /*<<< orphan*/  finish_lo_xact (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ lo_import (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pg_log_info (char*,int /*<<< orphan*/ ) ; 
 char* pg_malloc_extended (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_lo_result (char*,scalar_t__) ; 
 TYPE_1__ pset ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  start_lo_xact (char*,int*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char const*) ; 

bool
do_lo_import(const char *filename_arg, const char *comment_arg)
{
	PGresult   *res;
	Oid			loid;
	char		oidbuf[32];
	bool		own_transaction;

	if (!start_lo_xact("\\lo_import", &own_transaction))
		return false;

	SetCancelConn();
	loid = lo_import(pset.db, filename_arg);
	ResetCancelConn();

	if (loid == InvalidOid)
	{
		pg_log_info("%s", PQerrorMessage(pset.db));
		return fail_lo_xact("\\lo_import", own_transaction);
	}

	/* insert description if given */
	if (comment_arg)
	{
		char	   *cmdbuf;
		char	   *bufptr;
		size_t		slen = strlen(comment_arg);

		cmdbuf = pg_malloc_extended(slen * 2 + 256, MCXT_ALLOC_NO_OOM);
		if (!cmdbuf)
			return fail_lo_xact("\\lo_import", own_transaction);
		sprintf(cmdbuf, "COMMENT ON LARGE OBJECT %u IS '", loid);
		bufptr = cmdbuf + strlen(cmdbuf);
		bufptr += PQescapeStringConn(pset.db, bufptr, comment_arg, slen, NULL);
		strcpy(bufptr, "'");

		if (!(res = PSQLexec(cmdbuf)))
		{
			free(cmdbuf);
			return fail_lo_xact("\\lo_import", own_transaction);
		}

		PQclear(res);
		free(cmdbuf);
	}

	if (!finish_lo_xact("\\lo_import", own_transaction))
		return false;

	print_lo_result("lo_import %u", loid);

	sprintf(oidbuf, "%u", loid);
	SetVariable(pset.vars, "LASTOID", oidbuf);

	return true;
}