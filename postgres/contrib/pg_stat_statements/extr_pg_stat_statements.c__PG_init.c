#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  DefineCustomBoolVariable (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DefineCustomEnumVariable (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DefineCustomIntVariable (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EmitWarningsOnPlaceholders (char*) ; 
 int /*<<< orphan*/  ExecutorEnd_hook ; 
 int /*<<< orphan*/  ExecutorFinish_hook ; 
 int /*<<< orphan*/  ExecutorRun_hook ; 
 int /*<<< orphan*/  ExecutorStart_hook ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  PGC_POSTMASTER ; 
 int /*<<< orphan*/  PGC_SIGHUP ; 
 int /*<<< orphan*/  PGC_SUSET ; 
 int /*<<< orphan*/  PGSS_TRACK_TOP ; 
 int /*<<< orphan*/  ProcessUtility_hook ; 
 int /*<<< orphan*/  RequestAddinShmemSpace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RequestNamedLWLockTranche (char*,int) ; 
 int /*<<< orphan*/  pgss_ExecutorEnd ; 
 int /*<<< orphan*/  pgss_ExecutorFinish ; 
 int /*<<< orphan*/  pgss_ExecutorRun ; 
 int /*<<< orphan*/  pgss_ExecutorStart ; 
 int /*<<< orphan*/  pgss_ProcessUtility ; 
 int /*<<< orphan*/  pgss_max ; 
 int /*<<< orphan*/  pgss_memsize () ; 
 int /*<<< orphan*/  pgss_post_parse_analyze ; 
 int /*<<< orphan*/  pgss_save ; 
 int /*<<< orphan*/  pgss_shmem_startup ; 
 int /*<<< orphan*/  pgss_track ; 
 int /*<<< orphan*/  pgss_track_utility ; 
 int /*<<< orphan*/  post_parse_analyze_hook ; 
 int /*<<< orphan*/  prev_ExecutorEnd ; 
 int /*<<< orphan*/  prev_ExecutorFinish ; 
 int /*<<< orphan*/  prev_ExecutorRun ; 
 int /*<<< orphan*/  prev_ExecutorStart ; 
 int /*<<< orphan*/  prev_ProcessUtility ; 
 int /*<<< orphan*/  prev_post_parse_analyze_hook ; 
 int /*<<< orphan*/  prev_shmem_startup_hook ; 
 int /*<<< orphan*/  process_shared_preload_libraries_in_progress ; 
 int /*<<< orphan*/  shmem_startup_hook ; 
 int /*<<< orphan*/  track_options ; 

void
_PG_init(void)
{
	/*
	 * In order to create our shared memory area, we have to be loaded via
	 * shared_preload_libraries.  If not, fall out without hooking into any of
	 * the main system.  (We don't throw error here because it seems useful to
	 * allow the pg_stat_statements functions to be created even when the
	 * module isn't active.  The functions must protect themselves against
	 * being called then, however.)
	 */
	if (!process_shared_preload_libraries_in_progress)
		return;

	/*
	 * Define (or redefine) custom GUC variables.
	 */
	DefineCustomIntVariable("pg_stat_statements.max",
							"Sets the maximum number of statements tracked by pg_stat_statements.",
							NULL,
							&pgss_max,
							5000,
							100,
							INT_MAX,
							PGC_POSTMASTER,
							0,
							NULL,
							NULL,
							NULL);

	DefineCustomEnumVariable("pg_stat_statements.track",
							 "Selects which statements are tracked by pg_stat_statements.",
							 NULL,
							 &pgss_track,
							 PGSS_TRACK_TOP,
							 track_options,
							 PGC_SUSET,
							 0,
							 NULL,
							 NULL,
							 NULL);

	DefineCustomBoolVariable("pg_stat_statements.track_utility",
							 "Selects whether utility commands are tracked by pg_stat_statements.",
							 NULL,
							 &pgss_track_utility,
							 true,
							 PGC_SUSET,
							 0,
							 NULL,
							 NULL,
							 NULL);

	DefineCustomBoolVariable("pg_stat_statements.save",
							 "Save pg_stat_statements statistics across server shutdowns.",
							 NULL,
							 &pgss_save,
							 true,
							 PGC_SIGHUP,
							 0,
							 NULL,
							 NULL,
							 NULL);

	EmitWarningsOnPlaceholders("pg_stat_statements");

	/*
	 * Request additional shared resources.  (These are no-ops if we're not in
	 * the postmaster process.)  We'll allocate or attach to the shared
	 * resources in pgss_shmem_startup().
	 */
	RequestAddinShmemSpace(pgss_memsize());
	RequestNamedLWLockTranche("pg_stat_statements", 1);

	/*
	 * Install hooks.
	 */
	prev_shmem_startup_hook = shmem_startup_hook;
	shmem_startup_hook = pgss_shmem_startup;
	prev_post_parse_analyze_hook = post_parse_analyze_hook;
	post_parse_analyze_hook = pgss_post_parse_analyze;
	prev_ExecutorStart = ExecutorStart_hook;
	ExecutorStart_hook = pgss_ExecutorStart;
	prev_ExecutorRun = ExecutorRun_hook;
	ExecutorRun_hook = pgss_ExecutorRun;
	prev_ExecutorFinish = ExecutorFinish_hook;
	ExecutorFinish_hook = pgss_ExecutorFinish;
	prev_ExecutorEnd = ExecutorEnd_hook;
	ExecutorEnd_hook = pgss_ExecutorEnd;
	prev_ProcessUtility = ProcessUtility_hook;
	ProcessUtility_hook = pgss_ProcessUtility;
}