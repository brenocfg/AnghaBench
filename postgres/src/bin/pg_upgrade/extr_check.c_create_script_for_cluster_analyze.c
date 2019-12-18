#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {char* bindir; } ;
struct TYPE_12__ {int /*<<< orphan*/  major_version; } ;
struct TYPE_11__ {int /*<<< orphan*/  user; scalar_t__ user_specified; } ;
struct TYPE_10__ {char* data; } ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* ECHO_BLANK ; 
 char* ECHO_QUOTE ; 
 int GET_MAJOR_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCRIPT_EXT ; 
 int /*<<< orphan*/  SCRIPT_PREFIX ; 
 int /*<<< orphan*/  S_IRWXU ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  appendShellString (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_ok () ; 
 scalar_t__ chmod (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_priv (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 TYPE_5__ new_cluster ; 
 TYPE_4__ old_cluster ; 
 TYPE_3__ os_info ; 
 int /*<<< orphan*/  pg_fatal (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prep_status (char*) ; 
 char* psprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

void
create_script_for_cluster_analyze(char **analyze_script_file_name)
{
	FILE	   *script = NULL;
	PQExpBufferData user_specification;

	prep_status("Creating script to analyze new cluster");

	initPQExpBuffer(&user_specification);
	if (os_info.user_specified)
	{
		appendPQExpBufferStr(&user_specification, "-U ");
		appendShellString(&user_specification, os_info.user);
		appendPQExpBufferChar(&user_specification, ' ');
	}

	*analyze_script_file_name = psprintf("%sanalyze_new_cluster.%s",
										 SCRIPT_PREFIX, SCRIPT_EXT);

	if ((script = fopen_priv(*analyze_script_file_name, "w")) == NULL)
		pg_fatal("could not open file \"%s\": %s\n",
				 *analyze_script_file_name, strerror(errno));

#ifndef WIN32
	/* add shebang header */
	fprintf(script, "#!/bin/sh\n\n");
#else
	/* suppress command echoing */
	fprintf(script, "@echo off\n");
#endif

	fprintf(script, "echo %sThis script will generate minimal optimizer statistics rapidly%s\n",
			ECHO_QUOTE, ECHO_QUOTE);
	fprintf(script, "echo %sso your system is usable, and then gather statistics twice more%s\n",
			ECHO_QUOTE, ECHO_QUOTE);
	fprintf(script, "echo %swith increasing accuracy.  When it is done, your system will%s\n",
			ECHO_QUOTE, ECHO_QUOTE);
	fprintf(script, "echo %shave the default level of optimizer statistics.%s\n",
			ECHO_QUOTE, ECHO_QUOTE);
	fprintf(script, "echo%s\n\n", ECHO_BLANK);

	fprintf(script, "echo %sIf you have used ALTER TABLE to modify the statistics target for%s\n",
			ECHO_QUOTE, ECHO_QUOTE);
	fprintf(script, "echo %sany tables, you might want to remove them and restore them after%s\n",
			ECHO_QUOTE, ECHO_QUOTE);
	fprintf(script, "echo %srunning this script because they will delay fast statistics generation.%s\n",
			ECHO_QUOTE, ECHO_QUOTE);
	fprintf(script, "echo%s\n\n", ECHO_BLANK);

	fprintf(script, "echo %sIf you would like default statistics as quickly as possible, cancel%s\n",
			ECHO_QUOTE, ECHO_QUOTE);
	fprintf(script, "echo %sthis script and run:%s\n",
			ECHO_QUOTE, ECHO_QUOTE);
	fprintf(script, "echo %s    \"%s/vacuumdb\" %s--all %s%s\n", ECHO_QUOTE,
			new_cluster.bindir, user_specification.data,
	/* Did we copy the free space files? */
			(GET_MAJOR_VERSION(old_cluster.major_version) >= 804) ?
			"--analyze-only" : "--analyze", ECHO_QUOTE);
	fprintf(script, "echo%s\n\n", ECHO_BLANK);

	fprintf(script, "\"%s/vacuumdb\" %s--all --analyze-in-stages\n",
			new_cluster.bindir, user_specification.data);
	/* Did we copy the free space files? */
	if (GET_MAJOR_VERSION(old_cluster.major_version) < 804)
		fprintf(script, "\"%s/vacuumdb\" %s--all\n", new_cluster.bindir,
				user_specification.data);

	fprintf(script, "echo%s\n\n", ECHO_BLANK);
	fprintf(script, "echo %sDone%s\n",
			ECHO_QUOTE, ECHO_QUOTE);

	fclose(script);

#ifndef WIN32
	if (chmod(*analyze_script_file_name, S_IRWXU) != 0)
		pg_fatal("could not add execute permission to file \"%s\": %s\n",
				 *analyze_script_file_name, strerror(errno));
#endif

	termPQExpBuffer(&user_specification);

	check_ok();
}