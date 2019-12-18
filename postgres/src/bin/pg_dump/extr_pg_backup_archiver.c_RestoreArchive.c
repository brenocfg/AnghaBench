#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_6__ ;
typedef  struct TYPE_46__   TYPE_5__ ;
typedef  struct TYPE_45__   TYPE_4__ ;
typedef  struct TYPE_44__   TYPE_3__ ;
typedef  struct TYPE_43__   TYPE_38__ ;
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_41__ {int /*<<< orphan*/  oid; } ;
struct TYPE_42__ {int reqs; char* desc; char* dropStmt; struct TYPE_42__* next; TYPE_1__ catalogId; int /*<<< orphan*/  namespace; int /*<<< orphan*/  tag; struct TYPE_42__* prev; scalar_t__ hadDumper; } ;
typedef  TYPE_2__ TocEntry ;
struct TYPE_47__ {int maxRemoteVersion; scalar_t__ minRemoteVersion; } ;
struct TYPE_43__ {int numWorkers; scalar_t__ verbose; TYPE_3__* ropt; } ;
struct TYPE_46__ {scalar_t__ version; scalar_t__ compression; int noTocComments; TYPE_38__ public; int /*<<< orphan*/  stage; int /*<<< orphan*/ * connection; TYPE_2__* toc; int /*<<< orphan*/  (* PrepParallelRestorePtr ) (TYPE_5__*) ;int /*<<< orphan*/ * currSchema; TYPE_2__* currentTE; int /*<<< orphan*/  createDate; scalar_t__ archiveDumpVersion; scalar_t__ archiveRemoteVersion; int /*<<< orphan*/ * tocsByDumpId; int /*<<< orphan*/ * PrintTocDataPtr; int /*<<< orphan*/  (* ReopenPtr ) (TYPE_5__*) ;int /*<<< orphan*/ * ClonePtr; } ;
struct TYPE_45__ {int /*<<< orphan*/  data; } ;
struct TYPE_44__ {int dataOnly; scalar_t__ useDB; scalar_t__ compression; scalar_t__ filename; scalar_t__ single_txn; int /*<<< orphan*/  if_exists; scalar_t__ createDB; scalar_t__ dropSchema; int /*<<< orphan*/  promptPassword; int /*<<< orphan*/  username; int /*<<< orphan*/  pgport; int /*<<< orphan*/  pghost; int /*<<< orphan*/  dbname; } ;
typedef  TYPE_3__ RestoreOptions ;
typedef  int /*<<< orphan*/  ParallelState ;
typedef  TYPE_4__* PQExpBuffer ;
typedef  int /*<<< orphan*/  OutputContext ;
typedef  TYPE_5__ ArchiveHandle ;
typedef  TYPE_6__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CommitTransaction (TYPE_6__*) ; 
 int /*<<< orphan*/  ConnectDatabase (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DisconnectDatabase (TYPE_38__*) ; 
 int /*<<< orphan*/  DropBlobIfExists (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ K_VERS_1_3 ; 
 scalar_t__ K_VERS_1_8 ; 
 int /*<<< orphan*/  ParallelBackupEnd (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ParallelBackupStart (TYPE_5__*) ; 
 int REQ_DATA ; 
 int REQ_SCHEMA ; 
#define  RESTORE_PASS_ACL 130 
#define  RESTORE_PASS_MAIN 129 
#define  RESTORE_PASS_REFRESH 128 
 int /*<<< orphan*/  RestoreOutput (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAGE_FINALIZING ; 
 int /*<<< orphan*/  STAGE_INITIALIZING ; 
 int /*<<< orphan*/  STAGE_PROCESSING ; 
 int /*<<< orphan*/  SaveOutput (TYPE_5__*) ; 
 int /*<<< orphan*/  SetOutput (TYPE_5__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  StartTransaction (TYPE_6__*) ; 
 int /*<<< orphan*/  _becomeOwner (TYPE_5__*,TYPE_2__*) ; 
 int /*<<< orphan*/  _doSetFixedOutputState (TYPE_5__*) ; 
 int /*<<< orphan*/  _selectOutputSchema (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int const _tocEntryRestorePass (TYPE_2__*) ; 
 int /*<<< orphan*/  ahprintf (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_4__*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  buildTocEntryArrays (TYPE_5__*) ; 
 TYPE_4__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_4__*) ; 
 int /*<<< orphan*/  dumpTimestamp (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pending_list_header_init (TYPE_2__*) ; 
 int /*<<< orphan*/  pg_free (char*) ; 
 int /*<<< orphan*/  pg_log_info (char*,...) ; 
 int /*<<< orphan*/  pg_log_warning (char*,char*) ; 
 char* pg_strdup (char*) ; 
 int /*<<< orphan*/  restore_toc_entries_parallel (TYPE_5__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  restore_toc_entries_postfork (TYPE_5__*,TYPE_2__*) ; 
 int /*<<< orphan*/  restore_toc_entries_prefork (TYPE_5__*,TYPE_2__*) ; 
 int /*<<< orphan*/  restore_toc_entry (TYPE_5__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void
RestoreArchive(Archive *AHX)
{
	ArchiveHandle *AH = (ArchiveHandle *) AHX;
	RestoreOptions *ropt = AH->public.ropt;
	bool		parallel_mode;
	TocEntry   *te;
	OutputContext sav;

	AH->stage = STAGE_INITIALIZING;

	/*
	 * If we're going to do parallel restore, there are some restrictions.
	 */
	parallel_mode = (AH->public.numWorkers > 1 && ropt->useDB);
	if (parallel_mode)
	{
		/* We haven't got round to making this work for all archive formats */
		if (AH->ClonePtr == NULL || AH->ReopenPtr == NULL)
			fatal("parallel restore is not supported with this archive file format");

		/* Doesn't work if the archive represents dependencies as OIDs */
		if (AH->version < K_VERS_1_8)
			fatal("parallel restore is not supported with archives made by pre-8.0 pg_dump");

		/*
		 * It's also not gonna work if we can't reopen the input file, so
		 * let's try that immediately.
		 */
		AH->ReopenPtr(AH);
	}

	/*
	 * Make sure we won't need (de)compression we haven't got
	 */
#ifndef HAVE_LIBZ
	if (AH->compression != 0 && AH->PrintTocDataPtr != NULL)
	{
		for (te = AH->toc->next; te != AH->toc; te = te->next)
		{
			if (te->hadDumper && (te->reqs & REQ_DATA) != 0)
				fatal("cannot restore from compressed archive (compression not supported in this installation)");
		}
	}
#endif

	/*
	 * Prepare index arrays, so we can assume we have them throughout restore.
	 * It's possible we already did this, though.
	 */
	if (AH->tocsByDumpId == NULL)
		buildTocEntryArrays(AH);

	/*
	 * If we're using a DB connection, then connect it.
	 */
	if (ropt->useDB)
	{
		pg_log_info("connecting to database for restore");
		if (AH->version < K_VERS_1_3)
			fatal("direct database connections are not supported in pre-1.3 archives");

		/*
		 * We don't want to guess at whether the dump will successfully
		 * restore; allow the attempt regardless of the version of the restore
		 * target.
		 */
		AHX->minRemoteVersion = 0;
		AHX->maxRemoteVersion = 9999999;

		ConnectDatabase(AHX, ropt->dbname,
						ropt->pghost, ropt->pgport, ropt->username,
						ropt->promptPassword);

		/*
		 * If we're talking to the DB directly, don't send comments since they
		 * obscure SQL when displaying errors
		 */
		AH->noTocComments = 1;
	}

	/*
	 * Work out if we have an implied data-only restore. This can happen if
	 * the dump was data only or if the user has used a toc list to exclude
	 * all of the schema data. All we do is look for schema entries - if none
	 * are found then we set the dataOnly flag.
	 *
	 * We could scan for wanted TABLE entries, but that is not the same as
	 * dataOnly. At this stage, it seems unnecessary (6-Mar-2001).
	 */
	if (!ropt->dataOnly)
	{
		int			impliedDataOnly = 1;

		for (te = AH->toc->next; te != AH->toc; te = te->next)
		{
			if ((te->reqs & REQ_SCHEMA) != 0)
			{					/* It's schema, and it's wanted */
				impliedDataOnly = 0;
				break;
			}
		}
		if (impliedDataOnly)
		{
			ropt->dataOnly = impliedDataOnly;
			pg_log_info("implied data-only restore");
		}
	}

	/*
	 * Setup the output file if necessary.
	 */
	sav = SaveOutput(AH);
	if (ropt->filename || ropt->compression)
		SetOutput(AH, ropt->filename, ropt->compression);

	ahprintf(AH, "--\n-- PostgreSQL database dump\n--\n\n");

	if (AH->archiveRemoteVersion)
		ahprintf(AH, "-- Dumped from database version %s\n",
				 AH->archiveRemoteVersion);
	if (AH->archiveDumpVersion)
		ahprintf(AH, "-- Dumped by pg_dump version %s\n",
				 AH->archiveDumpVersion);

	ahprintf(AH, "\n");

	if (AH->public.verbose)
		dumpTimestamp(AH, "Started on", AH->createDate);

	if (ropt->single_txn)
	{
		if (AH->connection)
			StartTransaction(AHX);
		else
			ahprintf(AH, "BEGIN;\n\n");
	}

	/*
	 * Establish important parameter values right away.
	 */
	_doSetFixedOutputState(AH);

	AH->stage = STAGE_PROCESSING;

	/*
	 * Drop the items at the start, in reverse order
	 */
	if (ropt->dropSchema)
	{
		for (te = AH->toc->prev; te != AH->toc; te = te->prev)
		{
			AH->currentTE = te;

			/*
			 * In createDB mode, issue a DROP *only* for the database as a
			 * whole.  Issuing drops against anything else would be wrong,
			 * because at this point we're connected to the wrong database.
			 * (The DATABASE PROPERTIES entry, if any, should be treated like
			 * the DATABASE entry.)
			 */
			if (ropt->createDB)
			{
				if (strcmp(te->desc, "DATABASE") != 0 &&
					strcmp(te->desc, "DATABASE PROPERTIES") != 0)
					continue;
			}

			/* Otherwise, drop anything that's selected and has a dropStmt */
			if (((te->reqs & (REQ_SCHEMA | REQ_DATA)) != 0) && te->dropStmt)
			{
				pg_log_info("dropping %s %s", te->desc, te->tag);
				/* Select owner and schema as necessary */
				_becomeOwner(AH, te);
				_selectOutputSchema(AH, te->namespace);

				/*
				 * Now emit the DROP command, if the object has one.  Note we
				 * don't necessarily emit it verbatim; at this point we add an
				 * appropriate IF EXISTS clause, if the user requested it.
				 */
				if (*te->dropStmt != '\0')
				{
					if (!ropt->if_exists)
					{
						/* No --if-exists?	Then just use the original */
						ahprintf(AH, "%s", te->dropStmt);
					}
					else
					{
						/*
						 * Inject an appropriate spelling of "if exists".  For
						 * large objects, we have a separate routine that
						 * knows how to do it, without depending on
						 * te->dropStmt; use that.  For other objects we need
						 * to parse the command.
						 */
						if (strncmp(te->desc, "BLOB", 4) == 0)
						{
							DropBlobIfExists(AH, te->catalogId.oid);
						}
						else
						{
							char	   *dropStmt = pg_strdup(te->dropStmt);
							char	   *dropStmtOrig = dropStmt;
							PQExpBuffer ftStmt = createPQExpBuffer();

							/*
							 * Need to inject IF EXISTS clause after ALTER
							 * TABLE part in ALTER TABLE .. DROP statement
							 */
							if (strncmp(dropStmt, "ALTER TABLE", 11) == 0)
							{
								appendPQExpBufferStr(ftStmt,
													 "ALTER TABLE IF EXISTS");
								dropStmt = dropStmt + 11;
							}

							/*
							 * ALTER TABLE..ALTER COLUMN..DROP DEFAULT does
							 * not support the IF EXISTS clause, and therefore
							 * we simply emit the original command for DEFAULT
							 * objects (modulo the adjustment made above).
							 *
							 * Likewise, don't mess with DATABASE PROPERTIES.
							 *
							 * If we used CREATE OR REPLACE VIEW as a means of
							 * quasi-dropping an ON SELECT rule, that should
							 * be emitted unchanged as well.
							 *
							 * For other object types, we need to extract the
							 * first part of the DROP which includes the
							 * object type.  Most of the time this matches
							 * te->desc, so search for that; however for the
							 * different kinds of CONSTRAINTs, we know to
							 * search for hardcoded "DROP CONSTRAINT" instead.
							 */
							if (strcmp(te->desc, "DEFAULT") == 0 ||
								strcmp(te->desc, "DATABASE PROPERTIES") == 0 ||
								strncmp(dropStmt, "CREATE OR REPLACE VIEW", 22) == 0)
								appendPQExpBufferStr(ftStmt, dropStmt);
							else
							{
								char		buffer[40];
								char	   *mark;

								if (strcmp(te->desc, "CONSTRAINT") == 0 ||
									strcmp(te->desc, "CHECK CONSTRAINT") == 0 ||
									strcmp(te->desc, "FK CONSTRAINT") == 0)
									strcpy(buffer, "DROP CONSTRAINT");
								else
									snprintf(buffer, sizeof(buffer), "DROP %s",
											 te->desc);

								mark = strstr(dropStmt, buffer);

								if (mark)
								{
									*mark = '\0';
									appendPQExpBuffer(ftStmt, "%s%s IF EXISTS%s",
													  dropStmt, buffer,
													  mark + strlen(buffer));
								}
								else
								{
									/* complain and emit unmodified command */
									pg_log_warning("could not find where to insert IF EXISTS in statement \"%s\"",
												   dropStmtOrig);
									appendPQExpBufferStr(ftStmt, dropStmt);
								}
							}

							ahprintf(AH, "%s", ftStmt->data);

							destroyPQExpBuffer(ftStmt);
							pg_free(dropStmtOrig);
						}
					}
				}
			}
		}

		/*
		 * _selectOutputSchema may have set currSchema to reflect the effect
		 * of a "SET search_path" command it emitted.  However, by now we may
		 * have dropped that schema; or it might not have existed in the first
		 * place.  In either case the effective value of search_path will not
		 * be what we think.  Forcibly reset currSchema so that we will
		 * re-establish the search_path setting when needed (after creating
		 * the schema).
		 *
		 * If we treated users as pg_dump'able objects then we'd need to reset
		 * currUser here too.
		 */
		if (AH->currSchema)
			free(AH->currSchema);
		AH->currSchema = NULL;
	}

	if (parallel_mode)
	{
		/*
		 * In parallel mode, turn control over to the parallel-restore logic.
		 */
		ParallelState *pstate;
		TocEntry	pending_list;

		/* The archive format module may need some setup for this */
		if (AH->PrepParallelRestorePtr)
			AH->PrepParallelRestorePtr(AH);

		pending_list_header_init(&pending_list);

		/* This runs PRE_DATA items and then disconnects from the database */
		restore_toc_entries_prefork(AH, &pending_list);
		Assert(AH->connection == NULL);

		/* ParallelBackupStart() will actually fork the processes */
		pstate = ParallelBackupStart(AH);
		restore_toc_entries_parallel(AH, pstate, &pending_list);
		ParallelBackupEnd(AH, pstate);

		/* reconnect the master and see if we missed something */
		restore_toc_entries_postfork(AH, &pending_list);
		Assert(AH->connection != NULL);
	}
	else
	{
		/*
		 * In serial mode, process everything in three phases: normal items,
		 * then ACLs, then matview refresh items.  We might be able to skip
		 * one or both extra phases in some cases, eg data-only restores.
		 */
		bool		haveACL = false;
		bool		haveRefresh = false;

		for (te = AH->toc->next; te != AH->toc; te = te->next)
		{
			if ((te->reqs & (REQ_SCHEMA | REQ_DATA)) == 0)
				continue;		/* ignore if not to be dumped at all */

			switch (_tocEntryRestorePass(te))
			{
				case RESTORE_PASS_MAIN:
					(void) restore_toc_entry(AH, te, false);
					break;
				case RESTORE_PASS_ACL:
					haveACL = true;
					break;
				case RESTORE_PASS_REFRESH:
					haveRefresh = true;
					break;
			}
		}

		if (haveACL)
		{
			for (te = AH->toc->next; te != AH->toc; te = te->next)
			{
				if ((te->reqs & (REQ_SCHEMA | REQ_DATA)) != 0 &&
					_tocEntryRestorePass(te) == RESTORE_PASS_ACL)
					(void) restore_toc_entry(AH, te, false);
			}
		}

		if (haveRefresh)
		{
			for (te = AH->toc->next; te != AH->toc; te = te->next)
			{
				if ((te->reqs & (REQ_SCHEMA | REQ_DATA)) != 0 &&
					_tocEntryRestorePass(te) == RESTORE_PASS_REFRESH)
					(void) restore_toc_entry(AH, te, false);
			}
		}
	}

	if (ropt->single_txn)
	{
		if (AH->connection)
			CommitTransaction(AHX);
		else
			ahprintf(AH, "COMMIT;\n\n");
	}

	if (AH->public.verbose)
		dumpTimestamp(AH, "Completed on", time(NULL));

	ahprintf(AH, "--\n-- PostgreSQL database dump complete\n--\n\n");

	/*
	 * Clean up & we're done.
	 */
	AH->stage = STAGE_FINALIZING;

	if (ropt->filename || ropt->compression)
		RestoreOutput(AH, sav);

	if (ropt->useDB)
		DisconnectDatabase(&AH->public);
}