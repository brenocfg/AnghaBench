#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_16__ {scalar_t__ logical; int /*<<< orphan*/  streamConn; } ;
typedef  TYPE_4__ WalReceiverConn ;
struct TYPE_14__ {char* startpointTLI; } ;
struct TYPE_13__ {char* proto_version; int /*<<< orphan*/ * publication_names; } ;
struct TYPE_15__ {TYPE_2__ physical; TYPE_1__ logical; } ;
struct TYPE_17__ {scalar_t__ logical; char* slotname; int startpoint; TYPE_3__ proto; } ;
typedef  TYPE_5__ WalRcvStreamOptions ;
struct TYPE_18__ {char* data; } ;
typedef  TYPE_6__ StringInfoData ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 scalar_t__ PGRES_COPY_BOTH ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 char* PQescapeLiteral (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQfreemem (char*) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_6__*,char*,char*,...) ; 
 int /*<<< orphan*/  appendStringInfoChar (TYPE_6__*,char) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_6__*) ; 
 int /*<<< orphan*/ * libpqrcv_PQexec (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pchomp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* stringlist_to_identifierstr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static bool
libpqrcv_startstreaming(WalReceiverConn *conn,
						const WalRcvStreamOptions *options)
{
	StringInfoData cmd;
	PGresult   *res;

	Assert(options->logical == conn->logical);
	Assert(options->slotname || !options->logical);

	initStringInfo(&cmd);

	/* Build the command. */
	appendStringInfoString(&cmd, "START_REPLICATION");
	if (options->slotname != NULL)
		appendStringInfo(&cmd, " SLOT \"%s\"",
						 options->slotname);

	if (options->logical)
		appendStringInfoString(&cmd, " LOGICAL");

	appendStringInfo(&cmd, " %X/%X",
					 (uint32) (options->startpoint >> 32),
					 (uint32) options->startpoint);

	/*
	 * Additional options are different depending on if we are doing logical
	 * or physical replication.
	 */
	if (options->logical)
	{
		char	   *pubnames_str;
		List	   *pubnames;
		char	   *pubnames_literal;

		appendStringInfoString(&cmd, " (");

		appendStringInfo(&cmd, "proto_version '%u'",
						 options->proto.logical.proto_version);

		pubnames = options->proto.logical.publication_names;
		pubnames_str = stringlist_to_identifierstr(conn->streamConn, pubnames);
		if (!pubnames_str)
			ereport(ERROR,
					(errmsg("could not start WAL streaming: %s",
							pchomp(PQerrorMessage(conn->streamConn)))));
		pubnames_literal = PQescapeLiteral(conn->streamConn, pubnames_str,
										   strlen(pubnames_str));
		if (!pubnames_literal)
			ereport(ERROR,
					(errmsg("could not start WAL streaming: %s",
							pchomp(PQerrorMessage(conn->streamConn)))));
		appendStringInfo(&cmd, ", publication_names %s", pubnames_literal);
		PQfreemem(pubnames_literal);
		pfree(pubnames_str);

		appendStringInfoChar(&cmd, ')');
	}
	else
		appendStringInfo(&cmd, " TIMELINE %u",
						 options->proto.physical.startpointTLI);

	/* Start streaming. */
	res = libpqrcv_PQexec(conn->streamConn, cmd.data);
	pfree(cmd.data);

	if (PQresultStatus(res) == PGRES_COMMAND_OK)
	{
		PQclear(res);
		return false;
	}
	else if (PQresultStatus(res) != PGRES_COPY_BOTH)
	{
		PQclear(res);
		ereport(ERROR,
				(errmsg("could not start WAL streaming: %s",
						pchomp(PQerrorMessage(conn->streamConn)))));
	}
	PQclear(res);
	return true;
}