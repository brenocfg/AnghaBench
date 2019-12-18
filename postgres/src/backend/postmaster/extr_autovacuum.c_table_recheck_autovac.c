#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {double vacuum_cost_delay; int vacuum_cost_limit; int log_min_duration; int freeze_min_age; int freeze_table_age; int multixact_freeze_min_age; int multixact_freeze_table_age; } ;
struct TYPE_13__ {TYPE_5__ ar_reloptions; scalar_t__ ar_hasrelopts; } ;
typedef  TYPE_2__ av_relation ;
struct TYPE_12__ {int options; int freeze_min_age; int freeze_table_age; int multixact_freeze_min_age; int multixact_freeze_table_age; int is_wraparound; int log_min_duration; void* truncate; void* index_cleanup; } ;
struct TYPE_14__ {int at_vacuum_cost_limit; double at_vacuum_cost_delay; int at_dobalance; int /*<<< orphan*/ * at_datname; int /*<<< orphan*/ * at_nspname; int /*<<< orphan*/ * at_relname; TYPE_1__ at_params; int /*<<< orphan*/  at_sharedrel; int /*<<< orphan*/  at_relid; } ;
typedef  TYPE_3__ autovac_table ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_15__ {scalar_t__ relkind; int /*<<< orphan*/  relisshared; } ;
typedef  int /*<<< orphan*/  PgStat_StatTabEntry ;
typedef  int /*<<< orphan*/  PgStat_StatDBEntry ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_4__* Form_pg_class ;
typedef  TYPE_5__ AutoVacOpts ;

/* Variables and functions */
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int Log_autovacuum_min_duration ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ RELKIND_TOASTVALUE ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VACOPT_ANALYZE ; 
 int VACOPT_SKIPTOAST ; 
 int VACOPT_SKIP_LOCKED ; 
 void* VACOPT_TERNARY_DEFAULT ; 
 int VACOPT_VACUUM ; 
 double VacuumCostDelay ; 
 int VacuumCostLimit ; 
 int /*<<< orphan*/  autovac_refresh_stats () ; 
 double autovacuum_vac_cost_delay ; 
 int autovacuum_vac_cost_limit ; 
 int default_freeze_min_age ; 
 int default_freeze_table_age ; 
 int default_multixact_freeze_min_age ; 
 int default_multixact_freeze_table_age ; 
 TYPE_5__* extract_autovac_opts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_pgstat_tabentry_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* hash_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 TYPE_3__* palloc (int) ; 
 int /*<<< orphan*/ * pgstat_fetch_stat_dbentry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_needs_vacanalyze (int /*<<< orphan*/ ,TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *,int,int*,int*,int*) ; 

__attribute__((used)) static autovac_table *
table_recheck_autovac(Oid relid, HTAB *table_toast_map,
					  TupleDesc pg_class_desc,
					  int effective_multixact_freeze_max_age)
{
	Form_pg_class classForm;
	HeapTuple	classTup;
	bool		dovacuum;
	bool		doanalyze;
	autovac_table *tab = NULL;
	PgStat_StatTabEntry *tabentry;
	PgStat_StatDBEntry *shared;
	PgStat_StatDBEntry *dbentry;
	bool		wraparound;
	AutoVacOpts *avopts;

	/* use fresh stats */
	autovac_refresh_stats();

	shared = pgstat_fetch_stat_dbentry(InvalidOid);
	dbentry = pgstat_fetch_stat_dbentry(MyDatabaseId);

	/* fetch the relation's relcache entry */
	classTup = SearchSysCacheCopy1(RELOID, ObjectIdGetDatum(relid));
	if (!HeapTupleIsValid(classTup))
		return NULL;
	classForm = (Form_pg_class) GETSTRUCT(classTup);

	/*
	 * Get the applicable reloptions.  If it is a TOAST table, try to get the
	 * main table reloptions if the toast table itself doesn't have.
	 */
	avopts = extract_autovac_opts(classTup, pg_class_desc);
	if (classForm->relkind == RELKIND_TOASTVALUE &&
		avopts == NULL && table_toast_map != NULL)
	{
		av_relation *hentry;
		bool		found;

		hentry = hash_search(table_toast_map, &relid, HASH_FIND, &found);
		if (found && hentry->ar_hasrelopts)
			avopts = &hentry->ar_reloptions;
	}

	/* fetch the pgstat table entry */
	tabentry = get_pgstat_tabentry_relid(relid, classForm->relisshared,
										 shared, dbentry);

	relation_needs_vacanalyze(relid, avopts, classForm, tabentry,
							  effective_multixact_freeze_max_age,
							  &dovacuum, &doanalyze, &wraparound);

	/* ignore ANALYZE for toast tables */
	if (classForm->relkind == RELKIND_TOASTVALUE)
		doanalyze = false;

	/* OK, it needs something done */
	if (doanalyze || dovacuum)
	{
		int			freeze_min_age;
		int			freeze_table_age;
		int			multixact_freeze_min_age;
		int			multixact_freeze_table_age;
		int			vac_cost_limit;
		double		vac_cost_delay;
		int			log_min_duration;

		/*
		 * Calculate the vacuum cost parameters and the freeze ages.  If there
		 * are options set in pg_class.reloptions, use them; in the case of a
		 * toast table, try the main table too.  Otherwise use the GUC
		 * defaults, autovacuum's own first and plain vacuum second.
		 */

		/* -1 in autovac setting means use plain vacuum_cost_delay */
		vac_cost_delay = (avopts && avopts->vacuum_cost_delay >= 0)
			? avopts->vacuum_cost_delay
			: (autovacuum_vac_cost_delay >= 0)
			? autovacuum_vac_cost_delay
			: VacuumCostDelay;

		/* 0 or -1 in autovac setting means use plain vacuum_cost_limit */
		vac_cost_limit = (avopts && avopts->vacuum_cost_limit > 0)
			? avopts->vacuum_cost_limit
			: (autovacuum_vac_cost_limit > 0)
			? autovacuum_vac_cost_limit
			: VacuumCostLimit;

		/* -1 in autovac setting means use log_autovacuum_min_duration */
		log_min_duration = (avopts && avopts->log_min_duration >= 0)
			? avopts->log_min_duration
			: Log_autovacuum_min_duration;

		/* these do not have autovacuum-specific settings */
		freeze_min_age = (avopts && avopts->freeze_min_age >= 0)
			? avopts->freeze_min_age
			: default_freeze_min_age;

		freeze_table_age = (avopts && avopts->freeze_table_age >= 0)
			? avopts->freeze_table_age
			: default_freeze_table_age;

		multixact_freeze_min_age = (avopts &&
									avopts->multixact_freeze_min_age >= 0)
			? avopts->multixact_freeze_min_age
			: default_multixact_freeze_min_age;

		multixact_freeze_table_age = (avopts &&
									  avopts->multixact_freeze_table_age >= 0)
			? avopts->multixact_freeze_table_age
			: default_multixact_freeze_table_age;

		tab = palloc(sizeof(autovac_table));
		tab->at_relid = relid;
		tab->at_sharedrel = classForm->relisshared;
		tab->at_params.options = VACOPT_SKIPTOAST |
			(dovacuum ? VACOPT_VACUUM : 0) |
			(doanalyze ? VACOPT_ANALYZE : 0) |
			(!wraparound ? VACOPT_SKIP_LOCKED : 0);
		tab->at_params.index_cleanup = VACOPT_TERNARY_DEFAULT;
		tab->at_params.truncate = VACOPT_TERNARY_DEFAULT;
		tab->at_params.freeze_min_age = freeze_min_age;
		tab->at_params.freeze_table_age = freeze_table_age;
		tab->at_params.multixact_freeze_min_age = multixact_freeze_min_age;
		tab->at_params.multixact_freeze_table_age = multixact_freeze_table_age;
		tab->at_params.is_wraparound = wraparound;
		tab->at_params.log_min_duration = log_min_duration;
		tab->at_vacuum_cost_limit = vac_cost_limit;
		tab->at_vacuum_cost_delay = vac_cost_delay;
		tab->at_relname = NULL;
		tab->at_nspname = NULL;
		tab->at_datname = NULL;

		/*
		 * If any of the cost delay parameters has been set individually for
		 * this table, disable the balancing algorithm.
		 */
		tab->at_dobalance =
			!(avopts && (avopts->vacuum_cost_limit > 0 ||
						 avopts->vacuum_cost_delay > 0));
	}

	heap_freetuple(classTup);

	return tab;
}