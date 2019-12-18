#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vbuf ;
struct TYPE_4__ {int /*<<< orphan*/  encoding; } ;
struct TYPE_5__ {TYPE_1__ topt; } ;
struct TYPE_6__ {int sversion; int /*<<< orphan*/  show_context; int /*<<< orphan*/  db; int /*<<< orphan*/  verbosity; int /*<<< orphan*/  vars; int /*<<< orphan*/  encoding; TYPE_2__ popt; } ;

/* Variables and functions */
 int /*<<< orphan*/  PQclientEncoding (int /*<<< orphan*/ ) ; 
 char* PQdb (int /*<<< orphan*/ ) ; 
 char* PQhost (int /*<<< orphan*/ ) ; 
 char* PQparameterStatus (int /*<<< orphan*/ ,char*) ; 
 char* PQport (int /*<<< orphan*/ ) ; 
 int PQserverVersion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQsetErrorContextVisibility (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQsetErrorVerbosity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* PQuser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetVariable (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  formatPGVersionNumber (int,int,char*,int) ; 
 char* pg_encoding_to_char (int /*<<< orphan*/ ) ; 
 TYPE_3__ pset ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

void
SyncVariables(void)
{
	char		vbuf[32];
	const char *server_version;

	/* get stuff from connection */
	pset.encoding = PQclientEncoding(pset.db);
	pset.popt.topt.encoding = pset.encoding;
	pset.sversion = PQserverVersion(pset.db);

	SetVariable(pset.vars, "DBNAME", PQdb(pset.db));
	SetVariable(pset.vars, "USER", PQuser(pset.db));
	SetVariable(pset.vars, "HOST", PQhost(pset.db));
	SetVariable(pset.vars, "PORT", PQport(pset.db));
	SetVariable(pset.vars, "ENCODING", pg_encoding_to_char(pset.encoding));

	/* this bit should match connection_warnings(): */
	/* Try to get full text form of version, might include "devel" etc */
	server_version = PQparameterStatus(pset.db, "server_version");
	/* Otherwise fall back on pset.sversion */
	if (!server_version)
	{
		formatPGVersionNumber(pset.sversion, true, vbuf, sizeof(vbuf));
		server_version = vbuf;
	}
	SetVariable(pset.vars, "SERVER_VERSION_NAME", server_version);

	snprintf(vbuf, sizeof(vbuf), "%d", pset.sversion);
	SetVariable(pset.vars, "SERVER_VERSION_NUM", vbuf);

	/* send stuff to it, too */
	PQsetErrorVerbosity(pset.db, pset.verbosity);
	PQsetErrorContextVisibility(pset.db, pset.show_context);
}