#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct pg_tm {int dummy; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  fsec_t ;
struct TYPE_8__ {int /*<<< orphan*/  dirdesc; int /*<<< orphan*/  location; } ;
typedef  TYPE_1__ directory_fctx ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_9__ {int /*<<< orphan*/  attinmeta; TYPE_1__* user_fctx; int /*<<< orphan*/  multi_call_memory_ctx; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  TYPE_2__ FuncCallContext ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  AllocateDir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BuildTupleFromCStrings (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  CreateTemplateTupleDesc (int) ; 
 scalar_t__ DecodeDateTime (char**,int*,int,int*,struct pg_tm*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Log_directory ; 
 char* Log_filename ; 
 int MAXDATEFIELDS ; 
 int /*<<< orphan*/  MAXDATELEN ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ ParseDateTime (char*,char*,int /*<<< orphan*/ ,char**,int*,int,int*) ; 
 struct dirent* ReadDir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* SRF_FIRSTCALL_INIT () ; 
 scalar_t__ SRF_IS_FIRSTCALL () ; 
 TYPE_2__* SRF_PERCALL_SETUP () ; 
 int /*<<< orphan*/  SRF_RETURN_DONE (TYPE_2__*) ; 
 int /*<<< orphan*/  SRF_RETURN_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEXTOID ; 
 int /*<<< orphan*/  TIMESTAMPOID ; 
 int /*<<< orphan*/  TupleDescGetAttInMetadata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TupleDescInitEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 TYPE_1__* palloc (int) ; 
 char* psprintf (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pstrdup (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static Datum
pg_logdir_ls_internal(FunctionCallInfo fcinfo)
{
	FuncCallContext *funcctx;
	struct dirent *de;
	directory_fctx *fctx;

	if (strcmp(Log_filename, "postgresql-%Y-%m-%d_%H%M%S.log") != 0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 (errmsg("the log_filename parameter must equal 'postgresql-%%Y-%%m-%%d_%%H%%M%%S.log'"))));

	if (SRF_IS_FIRSTCALL())
	{
		MemoryContext oldcontext;
		TupleDesc	tupdesc;

		funcctx = SRF_FIRSTCALL_INIT();
		oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);

		fctx = palloc(sizeof(directory_fctx));

		tupdesc = CreateTemplateTupleDesc(2);
		TupleDescInitEntry(tupdesc, (AttrNumber) 1, "starttime",
						   TIMESTAMPOID, -1, 0);
		TupleDescInitEntry(tupdesc, (AttrNumber) 2, "filename",
						   TEXTOID, -1, 0);

		funcctx->attinmeta = TupleDescGetAttInMetadata(tupdesc);

		fctx->location = pstrdup(Log_directory);
		fctx->dirdesc = AllocateDir(fctx->location);

		if (!fctx->dirdesc)
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not open directory \"%s\": %m",
							fctx->location)));

		funcctx->user_fctx = fctx;
		MemoryContextSwitchTo(oldcontext);
	}

	funcctx = SRF_PERCALL_SETUP();
	fctx = (directory_fctx *) funcctx->user_fctx;

	while ((de = ReadDir(fctx->dirdesc, fctx->location)) != NULL)
	{
		char	   *values[2];
		HeapTuple	tuple;
		char		timestampbuf[32];
		char	   *field[MAXDATEFIELDS];
		char		lowstr[MAXDATELEN + 1];
		int			dtype;
		int			nf,
					ftype[MAXDATEFIELDS];
		fsec_t		fsec;
		int			tz = 0;
		struct pg_tm date;

		/*
		 * Default format: postgresql-YYYY-MM-DD_HHMMSS.log
		 */
		if (strlen(de->d_name) != 32
			|| strncmp(de->d_name, "postgresql-", 11) != 0
			|| de->d_name[21] != '_'
			|| strcmp(de->d_name + 28, ".log") != 0)
			continue;

		/* extract timestamp portion of filename */
		strcpy(timestampbuf, de->d_name + 11);
		timestampbuf[17] = '\0';

		/* parse and decode expected timestamp to verify it's OK format */
		if (ParseDateTime(timestampbuf, lowstr, MAXDATELEN, field, ftype, MAXDATEFIELDS, &nf))
			continue;

		if (DecodeDateTime(field, ftype, nf, &dtype, &date, &fsec, &tz))
			continue;

		/* Seems the timestamp is OK; prepare and return tuple */

		values[0] = timestampbuf;
		values[1] = psprintf("%s/%s", fctx->location, de->d_name);

		tuple = BuildTupleFromCStrings(funcctx->attinmeta, values);

		SRF_RETURN_NEXT(funcctx, HeapTupleGetDatum(tuple));
	}

	FreeDir(fctx->dirdesc);
	SRF_RETURN_DONE(funcctx);
}