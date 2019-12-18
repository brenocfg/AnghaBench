#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  tag; int /*<<< orphan*/  namespace; int /*<<< orphan*/  desc; } ;
typedef  TYPE_1__ TocEntry ;
struct TYPE_11__ {int /*<<< orphan*/  connection; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_3__ ArchiveHandle ;

/* Variables and functions */
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,char const*) ; 
 TYPE_2__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 char* fmtQualifiedId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
lockTableForWorker(ArchiveHandle *AH, TocEntry *te)
{
	const char *qualId;
	PQExpBuffer query;
	PGresult   *res;

	/* Nothing to do for BLOBS */
	if (strcmp(te->desc, "BLOBS") == 0)
		return;

	query = createPQExpBuffer();

	qualId = fmtQualifiedId(te->namespace, te->tag);

	appendPQExpBuffer(query, "LOCK TABLE %s IN ACCESS SHARE MODE NOWAIT",
					  qualId);

	res = PQexec(AH->connection, query->data);

	if (!res || PQresultStatus(res) != PGRES_COMMAND_OK)
		fatal("could not obtain lock on relation \"%s\"\n"
			  "This usually means that someone requested an ACCESS EXCLUSIVE lock "
			  "on the table after the pg_dump parent process had gotten the "
			  "initial ACCESS SHARE lock on the table.", qualId);

	PQclear(res);
	destroyPQExpBuffer(query);
}