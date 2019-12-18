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
typedef  int /*<<< orphan*/  tempfilename ;
typedef  int /*<<< orphan*/  magic ;
typedef  int /*<<< orphan*/  int16 ;
typedef  int /*<<< orphan*/  finalfilename ;
struct TYPE_11__ {TYPE_2__* reldesc; } ;
struct TYPE_10__ {int relisshared; int relnatts; scalar_t__ relkind; int t_len; struct TYPE_10__* rd_indoption; struct TYPE_10__* rd_indcollation; TYPE_1__* rd_indam; struct TYPE_10__* rd_support; struct TYPE_10__* rd_opcintype; struct TYPE_10__* rd_opfamily; struct TYPE_10__* rd_indextuple; struct TYPE_10__* rd_rel; struct TYPE_10__* rd_options; int /*<<< orphan*/  rd_att; int /*<<< orphan*/  rd_isnailed; } ;
struct TYPE_9__ {int amsupport; } ;
typedef  int /*<<< orphan*/  RelationData ;
typedef  TYPE_2__* Relation ;
typedef  TYPE_3__ RelIdCacheEnt ;
typedef  int /*<<< orphan*/  RegProcedure ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;
typedef  TYPE_2__* Form_pg_class ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ATTRIBUTE_FIXED_PART_SIZE ; 
 int /*<<< orphan*/  AcceptInvalidationMessages () ; 
 int /*<<< orphan*/ * AllocateFile (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int CLASS_TUPLE_SIZE ; 
 char* DatabasePath ; 
 int /*<<< orphan*/  FATAL ; 
 scalar_t__ FreeFile (int /*<<< orphan*/ *) ; 
 int HEAPTUPLESIZE ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int MAXPGPATH ; 
 int MyProcPid ; 
 int /*<<< orphan*/  PG_BINARY_W ; 
 int RELCACHE_INIT_FILEMAGIC ; 
 char* RELCACHE_INIT_FILENAME ; 
 scalar_t__ RELKIND_INDEX ; 
 int /*<<< orphan*/  RelCacheInitLock ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationIdCache ; 
 int /*<<< orphan*/  RelationIdIsInInitFile (int /*<<< orphan*/ ) ; 
 TYPE_2__* TupleDescAttr (int /*<<< orphan*/ ,int) ; 
 int VARSIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int fwrite (int*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 long relcacheInvalsReceived ; 
 scalar_t__ rename (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  write_item (TYPE_2__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
write_relcache_init_file(bool shared)
{
	FILE	   *fp;
	char		tempfilename[MAXPGPATH];
	char		finalfilename[MAXPGPATH];
	int			magic;
	HASH_SEQ_STATUS status;
	RelIdCacheEnt *idhentry;
	int			i;

	/*
	 * If we have already received any relcache inval events, there's no
	 * chance of succeeding so we may as well skip the whole thing.
	 */
	if (relcacheInvalsReceived != 0L)
		return;

	/*
	 * We must write a temporary file and rename it into place. Otherwise,
	 * another backend starting at about the same time might crash trying to
	 * read the partially-complete file.
	 */
	if (shared)
	{
		snprintf(tempfilename, sizeof(tempfilename), "global/%s.%d",
				 RELCACHE_INIT_FILENAME, MyProcPid);
		snprintf(finalfilename, sizeof(finalfilename), "global/%s",
				 RELCACHE_INIT_FILENAME);
	}
	else
	{
		snprintf(tempfilename, sizeof(tempfilename), "%s/%s.%d",
				 DatabasePath, RELCACHE_INIT_FILENAME, MyProcPid);
		snprintf(finalfilename, sizeof(finalfilename), "%s/%s",
				 DatabasePath, RELCACHE_INIT_FILENAME);
	}

	unlink(tempfilename);		/* in case it exists w/wrong permissions */

	fp = AllocateFile(tempfilename, PG_BINARY_W);
	if (fp == NULL)
	{
		/*
		 * We used to consider this a fatal error, but we might as well
		 * continue with backend startup ...
		 */
		ereport(WARNING,
				(errcode_for_file_access(),
				 errmsg("could not create relation-cache initialization file \"%s\": %m",
						tempfilename),
				 errdetail("Continuing anyway, but there's something wrong.")));
		return;
	}

	/*
	 * Write a magic number to serve as a file version identifier.  We can
	 * change the magic number whenever the relcache layout changes.
	 */
	magic = RELCACHE_INIT_FILEMAGIC;
	if (fwrite(&magic, 1, sizeof(magic), fp) != sizeof(magic))
		elog(FATAL, "could not write init file");

	/*
	 * Write all the appropriate reldescs (in no particular order).
	 */
	hash_seq_init(&status, RelationIdCache);

	while ((idhentry = (RelIdCacheEnt *) hash_seq_search(&status)) != NULL)
	{
		Relation	rel = idhentry->reldesc;
		Form_pg_class relform = rel->rd_rel;

		/* ignore if not correct group */
		if (relform->relisshared != shared)
			continue;

		/*
		 * Ignore if not supposed to be in init file.  We can allow any shared
		 * relation that's been loaded so far to be in the shared init file,
		 * but unshared relations must be ones that should be in the local
		 * file per RelationIdIsInInitFile.  (Note: if you want to change the
		 * criterion for rels to be kept in the init file, see also inval.c.
		 * The reason for filtering here is to be sure that we don't put
		 * anything into the local init file for which a relcache inval would
		 * not cause invalidation of that init file.)
		 */
		if (!shared && !RelationIdIsInInitFile(RelationGetRelid(rel)))
		{
			/* Nailed rels had better get stored. */
			Assert(!rel->rd_isnailed);
			continue;
		}

		/* first write the relcache entry proper */
		write_item(rel, sizeof(RelationData), fp);

		/* next write the relation tuple form */
		write_item(relform, CLASS_TUPLE_SIZE, fp);

		/* next, do all the attribute tuple form data entries */
		for (i = 0; i < relform->relnatts; i++)
		{
			write_item(TupleDescAttr(rel->rd_att, i),
					   ATTRIBUTE_FIXED_PART_SIZE, fp);
		}

		/* next, do the access method specific field */
		write_item(rel->rd_options,
				   (rel->rd_options ? VARSIZE(rel->rd_options) : 0),
				   fp);

		/*
		 * If it's an index, there's more to do. Note we explicitly ignore
		 * partitioned indexes here.
		 */
		if (rel->rd_rel->relkind == RELKIND_INDEX)
		{
			/* write the pg_index tuple */
			/* we assume this was created by heap_copytuple! */
			write_item(rel->rd_indextuple,
					   HEAPTUPLESIZE + rel->rd_indextuple->t_len,
					   fp);

			/* next, write the vector of opfamily OIDs */
			write_item(rel->rd_opfamily,
					   relform->relnatts * sizeof(Oid),
					   fp);

			/* next, write the vector of opcintype OIDs */
			write_item(rel->rd_opcintype,
					   relform->relnatts * sizeof(Oid),
					   fp);

			/* next, write the vector of support procedure OIDs */
			write_item(rel->rd_support,
					   relform->relnatts * (rel->rd_indam->amsupport * sizeof(RegProcedure)),
					   fp);

			/* next, write the vector of collation OIDs */
			write_item(rel->rd_indcollation,
					   relform->relnatts * sizeof(Oid),
					   fp);

			/* finally, write the vector of indoption values */
			write_item(rel->rd_indoption,
					   relform->relnatts * sizeof(int16),
					   fp);
		}
	}

	if (FreeFile(fp))
		elog(FATAL, "could not write init file");

	/*
	 * Now we have to check whether the data we've so painstakingly
	 * accumulated is already obsolete due to someone else's just-committed
	 * catalog changes.  If so, we just delete the temp file and leave it to
	 * the next backend to try again.  (Our own relcache entries will be
	 * updated by SI message processing, but we can't be sure whether what we
	 * wrote out was up-to-date.)
	 *
	 * This mustn't run concurrently with the code that unlinks an init file
	 * and sends SI messages, so grab a serialization lock for the duration.
	 */
	LWLockAcquire(RelCacheInitLock, LW_EXCLUSIVE);

	/* Make sure we have seen all incoming SI messages */
	AcceptInvalidationMessages();

	/*
	 * If we have received any SI relcache invals since backend start, assume
	 * we may have written out-of-date data.
	 */
	if (relcacheInvalsReceived == 0L)
	{
		/*
		 * OK, rename the temp file to its final name, deleting any
		 * previously-existing init file.
		 *
		 * Note: a failure here is possible under Cygwin, if some other
		 * backend is holding open an unlinked-but-not-yet-gone init file. So
		 * treat this as a noncritical failure; just remove the useless temp
		 * file on failure.
		 */
		if (rename(tempfilename, finalfilename) < 0)
			unlink(tempfilename);
	}
	else
	{
		/* Delete the already-obsolete temp file */
		unlink(tempfilename);
	}

	LWLockRelease(RelCacheInitLock);
}