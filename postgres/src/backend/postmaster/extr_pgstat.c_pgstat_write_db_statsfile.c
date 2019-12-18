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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  format_id ;
struct TYPE_3__ {int /*<<< orphan*/  functions; int /*<<< orphan*/  tables; int /*<<< orphan*/  databaseid; } ;
typedef  int /*<<< orphan*/  PgStat_StatTabEntry ;
typedef  int /*<<< orphan*/  PgStat_StatFuncEntry ;
typedef  TYPE_1__ PgStat_StatDBEntry ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateFile (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG2 ; 
 scalar_t__ FreeFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  PGSTAT_FILE_FORMAT_ID ; 
 int /*<<< orphan*/  PG_BINARY_W ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*,...) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_dbstat_filename (int,int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 scalar_t__ rename (char*,char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void
pgstat_write_db_statsfile(PgStat_StatDBEntry *dbentry, bool permanent)
{
	HASH_SEQ_STATUS tstat;
	HASH_SEQ_STATUS fstat;
	PgStat_StatTabEntry *tabentry;
	PgStat_StatFuncEntry *funcentry;
	FILE	   *fpout;
	int32		format_id;
	Oid			dbid = dbentry->databaseid;
	int			rc;
	char		tmpfile[MAXPGPATH];
	char		statfile[MAXPGPATH];

	get_dbstat_filename(permanent, true, dbid, tmpfile, MAXPGPATH);
	get_dbstat_filename(permanent, false, dbid, statfile, MAXPGPATH);

	elog(DEBUG2, "writing stats file \"%s\"", statfile);

	/*
	 * Open the statistics temp file to write out the current values.
	 */
	fpout = AllocateFile(tmpfile, PG_BINARY_W);
	if (fpout == NULL)
	{
		ereport(LOG,
				(errcode_for_file_access(),
				 errmsg("could not open temporary statistics file \"%s\": %m",
						tmpfile)));
		return;
	}

	/*
	 * Write the file header --- currently just a format ID.
	 */
	format_id = PGSTAT_FILE_FORMAT_ID;
	rc = fwrite(&format_id, sizeof(format_id), 1, fpout);
	(void) rc;					/* we'll check for error with ferror */

	/*
	 * Walk through the database's access stats per table.
	 */
	hash_seq_init(&tstat, dbentry->tables);
	while ((tabentry = (PgStat_StatTabEntry *) hash_seq_search(&tstat)) != NULL)
	{
		fputc('T', fpout);
		rc = fwrite(tabentry, sizeof(PgStat_StatTabEntry), 1, fpout);
		(void) rc;				/* we'll check for error with ferror */
	}

	/*
	 * Walk through the database's function stats table.
	 */
	hash_seq_init(&fstat, dbentry->functions);
	while ((funcentry = (PgStat_StatFuncEntry *) hash_seq_search(&fstat)) != NULL)
	{
		fputc('F', fpout);
		rc = fwrite(funcentry, sizeof(PgStat_StatFuncEntry), 1, fpout);
		(void) rc;				/* we'll check for error with ferror */
	}

	/*
	 * No more output to be done. Close the temp file and replace the old
	 * pgstat.stat with it.  The ferror() check replaces testing for error
	 * after each individual fputc or fwrite above.
	 */
	fputc('E', fpout);

	if (ferror(fpout))
	{
		ereport(LOG,
				(errcode_for_file_access(),
				 errmsg("could not write temporary statistics file \"%s\": %m",
						tmpfile)));
		FreeFile(fpout);
		unlink(tmpfile);
	}
	else if (FreeFile(fpout) < 0)
	{
		ereport(LOG,
				(errcode_for_file_access(),
				 errmsg("could not close temporary statistics file \"%s\": %m",
						tmpfile)));
		unlink(tmpfile);
	}
	else if (rename(tmpfile, statfile) < 0)
	{
		ereport(LOG,
				(errcode_for_file_access(),
				 errmsg("could not rename temporary statistics file \"%s\" to \"%s\": %m",
						tmpfile, statfile)));
		unlink(tmpfile);
	}

	if (permanent)
	{
		get_dbstat_filename(false, false, dbid, statfile, MAXPGPATH);

		elog(DEBUG2, "removing temporary stats file \"%s\"", statfile);
		unlink(statfile);
	}
}