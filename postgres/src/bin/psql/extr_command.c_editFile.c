#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 char* DEFAULT_EDITOR ; 
 char* DEFAULT_EDITOR_LINENUMBER_ARG ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 char* psprintf (char*,char const*,char const*,...) ; 
 int system (char*) ; 

__attribute__((used)) static bool
editFile(const char *fname, int lineno)
{
	const char *editorName;
	const char *editor_lineno_arg = NULL;
	char	   *sys;
	int			result;

	Assert(fname != NULL);

	/* Find an editor to use */
	editorName = getenv("PSQL_EDITOR");
	if (!editorName)
		editorName = getenv("EDITOR");
	if (!editorName)
		editorName = getenv("VISUAL");
	if (!editorName)
		editorName = DEFAULT_EDITOR;

	/* Get line number argument, if we need it. */
	if (lineno > 0)
	{
		editor_lineno_arg = getenv("PSQL_EDITOR_LINENUMBER_ARG");
#ifdef DEFAULT_EDITOR_LINENUMBER_ARG
		if (!editor_lineno_arg)
			editor_lineno_arg = DEFAULT_EDITOR_LINENUMBER_ARG;
#endif
		if (!editor_lineno_arg)
		{
			pg_log_error("environment variable PSQL_EDITOR_LINENUMBER_ARG must be set to specify a line number");
			return false;
		}
	}

	/*
	 * On Unix the EDITOR value should *not* be quoted, since it might include
	 * switches, eg, EDITOR="pico -t"; it's up to the user to put quotes in it
	 * if necessary.  But this policy is not very workable on Windows, due to
	 * severe brain damage in their command shell plus the fact that standard
	 * program paths include spaces.
	 */
#ifndef WIN32
	if (lineno > 0)
		sys = psprintf("exec %s %s%d '%s'",
					   editorName, editor_lineno_arg, lineno, fname);
	else
		sys = psprintf("exec %s '%s'",
					   editorName, fname);
#else
	if (lineno > 0)
		sys = psprintf("\"%s\" %s%d \"%s\"",
					   editorName, editor_lineno_arg, lineno, fname);
	else
		sys = psprintf("\"%s\" \"%s\"",
					   editorName, fname);
#endif
	result = system(sys);
	if (result == -1)
		pg_log_error("could not start editor \"%s\"", editorName);
	else if (result == 127)
		pg_log_error("could not start /bin/sh");
	free(sys);

	return result == 0;
}