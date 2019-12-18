#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  appendConnStrVal (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  appendShellString (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connstr ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ filename ; 
 int /*<<< orphan*/  pg_dump_bin ; 
 int /*<<< orphan*/  pg_log_info (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* pgdumpopts ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int system (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
runPgDump(const char *dbname, const char *create_opts)
{
	PQExpBuffer connstrbuf = createPQExpBuffer();
	PQExpBuffer cmd = createPQExpBuffer();
	int			ret;

	appendPQExpBuffer(cmd, "\"%s\" %s %s", pg_dump_bin,
					  pgdumpopts->data, create_opts);

	/*
	 * If we have a filename, use the undocumented plain-append pg_dump
	 * format.
	 */
	if (filename)
		appendPQExpBufferStr(cmd, " -Fa ");
	else
		appendPQExpBufferStr(cmd, " -Fp ");

	/*
	 * Append the database name to the already-constructed stem of connection
	 * string.
	 */
	appendPQExpBuffer(connstrbuf, "%s dbname=", connstr);
	appendConnStrVal(connstrbuf, dbname);

	appendShellString(cmd, connstrbuf->data);

	pg_log_info("running \"%s\"", cmd->data);

	fflush(stdout);
	fflush(stderr);

	ret = system(cmd->data);

	destroyPQExpBuffer(cmd);
	destroyPQExpBuffer(connstrbuf);

	return ret;
}