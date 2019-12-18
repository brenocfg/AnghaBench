#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cfgname; int /*<<< orphan*/  cfgnamespace; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  scalar_t__ GucSource ;
typedef  TYPE_1__* Form_pg_ts_config ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ IsTransactionState () ; 
 scalar_t__ MyDatabaseId ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ PGC_S_TEST ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSCONFIGOID ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ts_config_oid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* quote_qualified_identifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  stringToQualifiedNameList (char*) ; 

bool
check_TSCurrentConfig(char **newval, void **extra, GucSource source)
{
	/*
	 * If we aren't inside a transaction, or connected to a database, we
	 * cannot do the catalog accesses necessary to verify the config name.
	 * Must accept it on faith.
	 */
	if (IsTransactionState() && MyDatabaseId != InvalidOid)
	{
		Oid			cfgId;
		HeapTuple	tuple;
		Form_pg_ts_config cfg;
		char	   *buf;

		cfgId = get_ts_config_oid(stringToQualifiedNameList(*newval), true);

		/*
		 * When source == PGC_S_TEST, don't throw a hard error for a
		 * nonexistent configuration, only a NOTICE.  See comments in guc.h.
		 */
		if (!OidIsValid(cfgId))
		{
			if (source == PGC_S_TEST)
			{
				ereport(NOTICE,
						(errcode(ERRCODE_UNDEFINED_OBJECT),
						 errmsg("text search configuration \"%s\" does not exist", *newval)));
				return true;
			}
			else
				return false;
		}

		/*
		 * Modify the actually stored value to be fully qualified, to ensure
		 * later changes of search_path don't affect it.
		 */
		tuple = SearchSysCache1(TSCONFIGOID, ObjectIdGetDatum(cfgId));
		if (!HeapTupleIsValid(tuple))
			elog(ERROR, "cache lookup failed for text search configuration %u",
				 cfgId);
		cfg = (Form_pg_ts_config) GETSTRUCT(tuple);

		buf = quote_qualified_identifier(get_namespace_name(cfg->cfgnamespace),
										 NameStr(cfg->cfgname));

		ReleaseSysCache(tuple);

		/* GUC wants it malloc'd not palloc'd */
		free(*newval);
		*newval = strdup(buf);
		pfree(buf);
		if (!*newval)
			return false;
	}

	return true;
}