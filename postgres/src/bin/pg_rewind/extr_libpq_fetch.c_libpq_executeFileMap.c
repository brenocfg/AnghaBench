#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int narray; TYPE_2__** array; } ;
typedef  TYPE_1__ filemap_t ;
struct TYPE_7__ {int action; int /*<<< orphan*/  newsize; int /*<<< orphan*/  oldsize; int /*<<< orphan*/  path; int /*<<< orphan*/  pagemap; } ;
typedef  TYPE_2__ file_entry_t ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
#define  FILE_ACTION_COPY 133 
#define  FILE_ACTION_COPY_TAIL 132 
#define  FILE_ACTION_CREATE 131 
#define  FILE_ACTION_NONE 130 
#define  FILE_ACTION_REMOVE 129 
#define  FILE_ACTION_TRUNCATE 128 
 scalar_t__ PGRES_COMMAND_OK ; 
 scalar_t__ PGRES_COPY_IN ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * PQgetResult (int /*<<< orphan*/ ) ; 
 int PQputCopyEnd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQresultErrorMessage (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  create_target (TYPE_2__*) ; 
 int /*<<< orphan*/  execute_pagemap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_file_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_target_file (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pg_fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  receiveFileChunks (char const*) ; 
 int /*<<< orphan*/  remove_target (TYPE_2__*) ; 
 int /*<<< orphan*/  run_simple_command (char const*) ; 
 int /*<<< orphan*/  truncate_target_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
libpq_executeFileMap(filemap_t *map)
{
	file_entry_t *entry;
	const char *sql;
	PGresult   *res;
	int			i;

	/*
	 * First create a temporary table, and load it with the blocks that we
	 * need to fetch.
	 */
	sql = "CREATE TEMPORARY TABLE fetchchunks(path text, begin int8, len int4);";
	run_simple_command(sql);

	sql = "COPY fetchchunks FROM STDIN";
	res = PQexec(conn, sql);

	if (PQresultStatus(res) != PGRES_COPY_IN)
		pg_fatal("could not send file list: %s",
				 PQresultErrorMessage(res));
	PQclear(res);

	for (i = 0; i < map->narray; i++)
	{
		entry = map->array[i];

		/* If this is a relation file, copy the modified blocks */
		execute_pagemap(&entry->pagemap, entry->path);

		switch (entry->action)
		{
			case FILE_ACTION_NONE:
				/* nothing else to do */
				break;

			case FILE_ACTION_COPY:
				/* Truncate the old file out of the way, if any */
				open_target_file(entry->path, true);
				fetch_file_range(entry->path, 0, entry->newsize);
				break;

			case FILE_ACTION_TRUNCATE:
				truncate_target_file(entry->path, entry->newsize);
				break;

			case FILE_ACTION_COPY_TAIL:
				fetch_file_range(entry->path, entry->oldsize, entry->newsize);
				break;

			case FILE_ACTION_REMOVE:
				remove_target(entry);
				break;

			case FILE_ACTION_CREATE:
				create_target(entry);
				break;
		}
	}

	if (PQputCopyEnd(conn, NULL) != 1)
		pg_fatal("could not send end-of-COPY: %s",
				 PQerrorMessage(conn));

	while ((res = PQgetResult(conn)) != NULL)
	{
		if (PQresultStatus(res) != PGRES_COMMAND_OK)
			pg_fatal("unexpected result while sending file list: %s",
					 PQresultErrorMessage(res));
		PQclear(res);
	}

	/*
	 * We've now copied the list of file ranges that we need to fetch to the
	 * temporary table. Now, actually fetch all of those ranges.
	 */
	sql =
		"SELECT path, begin,\n"
		"  pg_read_binary_file(path, begin, len, true) AS chunk\n"
		"FROM fetchchunks\n";

	receiveFileChunks(sql);
}