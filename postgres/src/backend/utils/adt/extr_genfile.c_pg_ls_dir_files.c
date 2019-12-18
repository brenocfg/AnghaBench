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
struct stat {int /*<<< orphan*/  st_mtime; scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  nulls ;
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_8__ {char const* location; int /*<<< orphan*/  dirdesc; } ;
typedef  TYPE_1__ directory_fctx ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_9__ {int /*<<< orphan*/  tuple_desc; TYPE_1__* user_fctx; int /*<<< orphan*/  multi_call_memory_ctx; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  TYPE_2__ FuncCallContext ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  AllocateDir (char const*) ; 
 int /*<<< orphan*/  BlessTupleDesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CStringGetTextDatum (char*) ; 
 int /*<<< orphan*/  CreateTemplateTupleDesc (int) ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT8OID ; 
 int /*<<< orphan*/  Int64GetDatum (int /*<<< orphan*/ ) ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 struct dirent* ReadDir (int /*<<< orphan*/ ,char const*) ; 
 TYPE_2__* SRF_FIRSTCALL_INIT () ; 
 scalar_t__ SRF_IS_FIRSTCALL () ; 
 TYPE_2__* SRF_PERCALL_SETUP () ; 
 int /*<<< orphan*/  SRF_RETURN_DONE (TYPE_2__*) ; 
 int /*<<< orphan*/  SRF_RETURN_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEXTOID ; 
 int /*<<< orphan*/  TIMESTAMPTZOID ; 
 int /*<<< orphan*/  TimestampTzGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TupleDescInitEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* palloc (int) ; 
 char const* pstrdup (char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  time_t_to_timestamptz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Datum
pg_ls_dir_files(FunctionCallInfo fcinfo, const char *dir, bool missing_ok)
{
	FuncCallContext *funcctx;
	struct dirent *de;
	directory_fctx *fctx;

	if (SRF_IS_FIRSTCALL())
	{
		MemoryContext oldcontext;
		TupleDesc	tupdesc;

		funcctx = SRF_FIRSTCALL_INIT();
		oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);

		fctx = palloc(sizeof(directory_fctx));

		tupdesc = CreateTemplateTupleDesc(3);
		TupleDescInitEntry(tupdesc, (AttrNumber) 1, "name",
						   TEXTOID, -1, 0);
		TupleDescInitEntry(tupdesc, (AttrNumber) 2, "size",
						   INT8OID, -1, 0);
		TupleDescInitEntry(tupdesc, (AttrNumber) 3, "modification",
						   TIMESTAMPTZOID, -1, 0);
		funcctx->tuple_desc = BlessTupleDesc(tupdesc);

		fctx->location = pstrdup(dir);
		fctx->dirdesc = AllocateDir(fctx->location);

		if (!fctx->dirdesc)
		{
			if (missing_ok && errno == ENOENT)
			{
				MemoryContextSwitchTo(oldcontext);
				SRF_RETURN_DONE(funcctx);
			}
			else
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not open directory \"%s\": %m",
								fctx->location)));
		}

		funcctx->user_fctx = fctx;
		MemoryContextSwitchTo(oldcontext);
	}

	funcctx = SRF_PERCALL_SETUP();
	fctx = (directory_fctx *) funcctx->user_fctx;

	while ((de = ReadDir(fctx->dirdesc, fctx->location)) != NULL)
	{
		Datum		values[3];
		bool		nulls[3];
		char		path[MAXPGPATH * 2];
		struct stat attrib;
		HeapTuple	tuple;

		/* Skip hidden files */
		if (de->d_name[0] == '.')
			continue;

		/* Get the file info */
		snprintf(path, sizeof(path), "%s/%s", fctx->location, de->d_name);
		if (stat(path, &attrib) < 0)
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not stat directory \"%s\": %m", dir)));

		/* Ignore anything but regular files */
		if (!S_ISREG(attrib.st_mode))
			continue;

		values[0] = CStringGetTextDatum(de->d_name);
		values[1] = Int64GetDatum((int64) attrib.st_size);
		values[2] = TimestampTzGetDatum(time_t_to_timestamptz(attrib.st_mtime));
		memset(nulls, 0, sizeof(nulls));

		tuple = heap_form_tuple(funcctx->tuple_desc, values, nulls);
		SRF_RETURN_NEXT(funcctx, HeapTupleGetDatum(tuple));
	}

	FreeDir(fctx->dirdesc);
	SRF_RETURN_DONE(funcctx);
}