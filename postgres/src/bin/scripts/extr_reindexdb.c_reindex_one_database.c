#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  enum trivalue { ____Placeholder_trivalue } trivalue ;
struct TYPE_19__ {int /*<<< orphan*/ * connection; } ;
struct TYPE_18__ {TYPE_1__* head; } ;
struct TYPE_17__ {char* val; struct TYPE_17__* next; } ;
typedef  TYPE_1__ SimpleStringListCell ;
typedef  TYPE_2__ SimpleStringList ;
typedef  int ReindexType ;
typedef  TYPE_3__ ParallelSlot ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CancelRequested ; 
 int Min (int,int) ; 
 char const* PQdb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 int PQserverVersion (int /*<<< orphan*/ *) ; 
 TYPE_3__* ParallelSlotsGetIdle (TYPE_3__*,int) ; 
 TYPE_3__* ParallelSlotsSetup (char const*,char const*,char const*,char const*,int,char const*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ParallelSlotsTerminate (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ParallelSlotsWaitCompletion (TYPE_3__*,int) ; 
#define  REINDEX_DATABASE 132 
#define  REINDEX_INDEX 131 
#define  REINDEX_SCHEMA 130 
#define  REINDEX_SYSTEM 129 
#define  REINDEX_TABLE 128 
 int /*<<< orphan*/ * connectDatabase (char const*,char const*,char const*,char const*,int,char const*,int,int,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 TYPE_2__* get_parallel_object_list (int /*<<< orphan*/ *,int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  pfree (TYPE_3__*) ; 
 int /*<<< orphan*/  pg_free (TYPE_2__*) ; 
 int /*<<< orphan*/  pg_log_error (char*,char*,char*) ; 
 int /*<<< orphan*/  pg_log_warning (char*) ; 
 TYPE_2__* pg_malloc0 (int) ; 
 int /*<<< orphan*/  run_reindex_command (int /*<<< orphan*/ *,int const,char const*,int,int,int,int) ; 
 int /*<<< orphan*/  simple_string_list_append (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  simple_string_list_destroy (TYPE_2__*) ; 

__attribute__((used)) static void
reindex_one_database(const char *dbname, ReindexType type,
					 SimpleStringList *user_list, const char *host,
					 const char *port, const char *username,
					 enum trivalue prompt_password, const char *progname, bool echo,
					 bool verbose, bool concurrently, int concurrentCons)
{
	PGconn	   *conn;
	SimpleStringListCell *cell;
	bool		parallel = concurrentCons > 1;
	SimpleStringList *process_list = user_list;
	ReindexType process_type = type;
	ParallelSlot *slots;
	bool		failed = false;
	int			items_count = 0;

	conn = connectDatabase(dbname, host, port, username, prompt_password,
						   progname, echo, false, false);

	if (concurrently && PQserverVersion(conn) < 120000)
	{
		PQfinish(conn);
		pg_log_error("cannot use the \"%s\" option on server versions older than PostgreSQL %s",
					 "concurrently", "12");
		exit(1);
	}

	if (!parallel)
	{
		switch (process_type)
		{
			case REINDEX_DATABASE:
			case REINDEX_SYSTEM:

				/*
				 * Database and system reindexes only need to work on the
				 * database itself, so build a list with a single entry.
				 */
				Assert(user_list == NULL);
				process_list = pg_malloc0(sizeof(SimpleStringList));
				simple_string_list_append(process_list, PQdb(conn));
				break;

			case REINDEX_INDEX:
			case REINDEX_SCHEMA:
			case REINDEX_TABLE:
				Assert(user_list != NULL);
				break;
		}
	}
	else
	{
		switch (process_type)
		{
			case REINDEX_DATABASE:

				/*
				 * Database-wide parallel reindex requires special processing.
				 * If multiple jobs were asked, we have to reindex system
				 * catalogs first as they cannot be processed in parallel.
				 */
				if (concurrently)
					pg_log_warning("cannot reindex system catalogs concurrently, skipping all");
				else
					run_reindex_command(conn, REINDEX_SYSTEM, PQdb(conn), echo,
										verbose, concurrently, false);

				/* Build a list of relations from the database */
				process_list = get_parallel_object_list(conn, process_type,
														user_list, echo);
				process_type = REINDEX_TABLE;

				/* Bail out if nothing to process */
				if (process_list == NULL)
					return;
				break;

			case REINDEX_SCHEMA:
				Assert(user_list != NULL);

				/* Build a list of relations from all the schemas */
				process_list = get_parallel_object_list(conn, process_type,
														user_list, echo);
				process_type = REINDEX_TABLE;

				/* Bail out if nothing to process */
				if (process_list == NULL)
					return;
				break;

			case REINDEX_SYSTEM:
			case REINDEX_INDEX:
				/* not supported */
				Assert(false);
				break;

			case REINDEX_TABLE:

				/*
				 * Fall through.  The list of items for tables is already
				 * created.
				 */
				break;
		}
	}

	/*
	 * Adjust the number of concurrent connections depending on the items in
	 * the list.  We choose the minimum between the number of concurrent
	 * connections and the number of items in the list.
	 */
	for (cell = process_list->head; cell; cell = cell->next)
	{
		items_count++;

		/* no need to continue if there are more elements than jobs */
		if (items_count >= concurrentCons)
			break;
	}
	concurrentCons = Min(concurrentCons, items_count);
	Assert(concurrentCons > 0);

	Assert(process_list != NULL);

	slots = ParallelSlotsSetup(dbname, host, port, username, prompt_password,
							   progname, echo, conn, concurrentCons);

	cell = process_list->head;
	do
	{
		const char *objname = cell->val;
		ParallelSlot *free_slot = NULL;

		if (CancelRequested)
		{
			failed = true;
			goto finish;
		}

		free_slot = ParallelSlotsGetIdle(slots, concurrentCons);
		if (!free_slot)
		{
			failed = true;
			goto finish;
		}

		run_reindex_command(free_slot->connection, process_type, objname,
							echo, verbose, concurrently, true);

		cell = cell->next;
	} while (cell != NULL);

	if (!ParallelSlotsWaitCompletion(slots, concurrentCons))
		failed = true;

finish:
	if (process_list != user_list)
	{
		simple_string_list_destroy(process_list);
		pg_free(process_list);
	}

	ParallelSlotsTerminate(slots, concurrentCons);
	pfree(slots);

	if (failed)
		exit(1);
}