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
struct TYPE_3__ {scalar_t__ and_analyze; scalar_t__ verbose; scalar_t__ freeze; scalar_t__ full; scalar_t__ skip_locked; scalar_t__ disable_page_skipping; scalar_t__ analyze_only; } ;
typedef  TYPE_1__ vacuumingOptions ;
typedef  int /*<<< orphan*/  PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  appendPQExpBuffer (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  resetPQExpBuffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
prepare_vacuum_command(PQExpBuffer sql, int serverVersion,
					   vacuumingOptions *vacopts, const char *table)
{
	const char *paren = " (";
	const char *comma = ", ";
	const char *sep = paren;

	resetPQExpBuffer(sql);

	if (vacopts->analyze_only)
	{
		appendPQExpBufferStr(sql, "ANALYZE");

		/* parenthesized grammar of ANALYZE is supported since v11 */
		if (serverVersion >= 110000)
		{
			if (vacopts->skip_locked)
			{
				/* SKIP_LOCKED is supported since v12 */
				Assert(serverVersion >= 120000);
				appendPQExpBuffer(sql, "%sSKIP_LOCKED", sep);
				sep = comma;
			}
			if (vacopts->verbose)
			{
				appendPQExpBuffer(sql, "%sVERBOSE", sep);
				sep = comma;
			}
			if (sep != paren)
				appendPQExpBufferChar(sql, ')');
		}
		else
		{
			if (vacopts->verbose)
				appendPQExpBufferStr(sql, " VERBOSE");
		}
	}
	else
	{
		appendPQExpBufferStr(sql, "VACUUM");

		/* parenthesized grammar of VACUUM is supported since v9.0 */
		if (serverVersion >= 90000)
		{
			if (vacopts->disable_page_skipping)
			{
				/* DISABLE_PAGE_SKIPPING is supported since v9.6 */
				Assert(serverVersion >= 90600);
				appendPQExpBuffer(sql, "%sDISABLE_PAGE_SKIPPING", sep);
				sep = comma;
			}
			if (vacopts->skip_locked)
			{
				/* SKIP_LOCKED is supported since v12 */
				Assert(serverVersion >= 120000);
				appendPQExpBuffer(sql, "%sSKIP_LOCKED", sep);
				sep = comma;
			}
			if (vacopts->full)
			{
				appendPQExpBuffer(sql, "%sFULL", sep);
				sep = comma;
			}
			if (vacopts->freeze)
			{
				appendPQExpBuffer(sql, "%sFREEZE", sep);
				sep = comma;
			}
			if (vacopts->verbose)
			{
				appendPQExpBuffer(sql, "%sVERBOSE", sep);
				sep = comma;
			}
			if (vacopts->and_analyze)
			{
				appendPQExpBuffer(sql, "%sANALYZE", sep);
				sep = comma;
			}
			if (sep != paren)
				appendPQExpBufferChar(sql, ')');
		}
		else
		{
			if (vacopts->full)
				appendPQExpBufferStr(sql, " FULL");
			if (vacopts->freeze)
				appendPQExpBufferStr(sql, " FREEZE");
			if (vacopts->verbose)
				appendPQExpBufferStr(sql, " VERBOSE");
			if (vacopts->and_analyze)
				appendPQExpBufferStr(sql, " ANALYZE");
		}
	}

	appendPQExpBuffer(sql, " %s;", table);
}