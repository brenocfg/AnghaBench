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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int mode_t ;
struct TYPE_11__ {int is_program; int /*<<< orphan*/  filename; int /*<<< orphan*/ * copy_file; int /*<<< orphan*/  copycontext; } ;
struct TYPE_10__ {TYPE_1__* rd_rel; } ;
struct TYPE_9__ {scalar_t__ relkind; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  RawStmt ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_3__* CopyState ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_3__* BeginCopy (int /*<<< orphan*/ *,int,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ DestRemote ; 
 int EACCES ; 
 int ENOENT ; 
 int /*<<< orphan*/  ERRCODE_INVALID_NAME ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenPipeStream (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_BINARY_W ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_FINALLY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 scalar_t__ RELKIND_FOREIGN_TABLE ; 
 scalar_t__ RELKIND_MATVIEW ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RELKIND_RELATION ; 
 scalar_t__ RELKIND_SEQUENCE ; 
 scalar_t__ RELKIND_VIEW ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int errno ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  is_absolute_path (char const*) ; 
 int /*<<< orphan*/  pstrdup (char const*) ; 
 int /*<<< orphan*/ * stdout ; 
 int umask (int) ; 
 scalar_t__ whereToSendOutput ; 

__attribute__((used)) static CopyState
BeginCopyTo(ParseState *pstate,
			Relation rel,
			RawStmt *query,
			Oid queryRelId,
			const char *filename,
			bool is_program,
			List *attnamelist,
			List *options)
{
	CopyState	cstate;
	bool		pipe = (filename == NULL);
	MemoryContext oldcontext;

	if (rel != NULL && rel->rd_rel->relkind != RELKIND_RELATION)
	{
		if (rel->rd_rel->relkind == RELKIND_VIEW)
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("cannot copy from view \"%s\"",
							RelationGetRelationName(rel)),
					 errhint("Try the COPY (SELECT ...) TO variant.")));
		else if (rel->rd_rel->relkind == RELKIND_MATVIEW)
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("cannot copy from materialized view \"%s\"",
							RelationGetRelationName(rel)),
					 errhint("Try the COPY (SELECT ...) TO variant.")));
		else if (rel->rd_rel->relkind == RELKIND_FOREIGN_TABLE)
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("cannot copy from foreign table \"%s\"",
							RelationGetRelationName(rel)),
					 errhint("Try the COPY (SELECT ...) TO variant.")));
		else if (rel->rd_rel->relkind == RELKIND_SEQUENCE)
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("cannot copy from sequence \"%s\"",
							RelationGetRelationName(rel))));
		else if (rel->rd_rel->relkind == RELKIND_PARTITIONED_TABLE)
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("cannot copy from partitioned table \"%s\"",
							RelationGetRelationName(rel)),
					 errhint("Try the COPY (SELECT ...) TO variant.")));
		else
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("cannot copy from non-table relation \"%s\"",
							RelationGetRelationName(rel))));
	}

	cstate = BeginCopy(pstate, false, rel, query, queryRelId, attnamelist,
					   options);
	oldcontext = MemoryContextSwitchTo(cstate->copycontext);

	if (pipe)
	{
		Assert(!is_program);	/* the grammar does not allow this */
		if (whereToSendOutput != DestRemote)
			cstate->copy_file = stdout;
	}
	else
	{
		cstate->filename = pstrdup(filename);
		cstate->is_program = is_program;

		if (is_program)
		{
			cstate->copy_file = OpenPipeStream(cstate->filename, PG_BINARY_W);
			if (cstate->copy_file == NULL)
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not execute command \"%s\": %m",
								cstate->filename)));
		}
		else
		{
			mode_t		oumask; /* Pre-existing umask value */
			struct stat st;

			/*
			 * Prevent write to relative path ... too easy to shoot oneself in
			 * the foot by overwriting a database file ...
			 */
			if (!is_absolute_path(filename))
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_NAME),
						 errmsg("relative path not allowed for COPY to file")));

			oumask = umask(S_IWGRP | S_IWOTH);
			PG_TRY();
			{
				cstate->copy_file = AllocateFile(cstate->filename, PG_BINARY_W);
			}
			PG_FINALLY();
			{
				umask(oumask);
			}
			PG_END_TRY();
			if (cstate->copy_file == NULL)
			{
				/* copy errno because ereport subfunctions might change it */
				int			save_errno = errno;

				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not open file \"%s\" for writing: %m",
								cstate->filename),
						 (save_errno == ENOENT || save_errno == EACCES) ?
						 errhint("COPY TO instructs the PostgreSQL server process to write a file. "
								 "You may want a client-side facility such as psql's \\copy.") : 0));
			}

			if (fstat(fileno(cstate->copy_file), &st))
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not stat file \"%s\": %m",
								cstate->filename)));

			if (S_ISDIR(st.st_mode))
				ereport(ERROR,
						(errcode(ERRCODE_WRONG_OBJECT_TYPE),
						 errmsg("\"%s\" is a directory", cstate->filename)));
		}
	}

	MemoryContextSwitchTo(oldcontext);

	return cstate;
}