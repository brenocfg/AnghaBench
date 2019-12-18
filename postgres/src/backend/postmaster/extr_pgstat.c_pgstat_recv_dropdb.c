#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  m_databaseid; } ;
struct TYPE_5__ {int /*<<< orphan*/ * functions; int /*<<< orphan*/ * tables; } ;
typedef  TYPE_1__ PgStat_StatDBEntry ;
typedef  TYPE_2__ PgStat_MsgDropdb ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  get_dbstat_filename (int,int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hash_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgStatDBHash ; 
 TYPE_1__* pgstat_get_db_entry (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void
pgstat_recv_dropdb(PgStat_MsgDropdb *msg, int len)
{
	Oid			dbid = msg->m_databaseid;
	PgStat_StatDBEntry *dbentry;

	/*
	 * Lookup the database in the hashtable.
	 */
	dbentry = pgstat_get_db_entry(dbid, false);

	/*
	 * If found, remove it (along with the db statfile).
	 */
	if (dbentry)
	{
		char		statfile[MAXPGPATH];

		get_dbstat_filename(false, false, dbid, statfile, MAXPGPATH);

		elog(DEBUG2, "removing stats file \"%s\"", statfile);
		unlink(statfile);

		if (dbentry->tables != NULL)
			hash_destroy(dbentry->tables);
		if (dbentry->functions != NULL)
			hash_destroy(dbentry->functions);

		if (hash_search(pgStatDBHash,
						(void *) &dbid,
						HASH_REMOVE, NULL) == NULL)
			ereport(ERROR,
					(errmsg("database hash table corrupted during cleanup --- abort")));
	}
}