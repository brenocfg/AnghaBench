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
struct TYPE_3__ {scalar_t__ relnamespace; scalar_t__ relisshared; int /*<<< orphan*/  relname; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* Form_pg_class ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ PG_CATALOG_NAMESPACE ; 
 int VACOPT_ANALYZE ; 
 int VACOPT_VACUUM ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ pg_class_ownercheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_database_ownercheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
vacuum_is_relation_owner(Oid relid, Form_pg_class reltuple, int options)
{
	char	   *relname;

	Assert((options & (VACOPT_VACUUM | VACOPT_ANALYZE)) != 0);

	/*
	 * Check permissions.
	 *
	 * We allow the user to vacuum or analyze a table if he is superuser, the
	 * table owner, or the database owner (but in the latter case, only if
	 * it's not a shared relation).  pg_class_ownercheck includes the
	 * superuser case.
	 *
	 * Note we choose to treat permissions failure as a WARNING and keep
	 * trying to vacuum or analyze the rest of the DB --- is this appropriate?
	 */
	if (pg_class_ownercheck(relid, GetUserId()) ||
		(pg_database_ownercheck(MyDatabaseId, GetUserId()) && !reltuple->relisshared))
		return true;

	relname = NameStr(reltuple->relname);

	if ((options & VACOPT_VACUUM) != 0)
	{
		if (reltuple->relisshared)
			ereport(WARNING,
					(errmsg("skipping \"%s\" --- only superuser can vacuum it",
							relname)));
		else if (reltuple->relnamespace == PG_CATALOG_NAMESPACE)
			ereport(WARNING,
					(errmsg("skipping \"%s\" --- only superuser or database owner can vacuum it",
							relname)));
		else
			ereport(WARNING,
					(errmsg("skipping \"%s\" --- only table or database owner can vacuum it",
							relname)));

		/*
		 * For VACUUM ANALYZE, both logs could show up, but just generate
		 * information for VACUUM as that would be the first one to be
		 * processed.
		 */
		return false;
	}

	if ((options & VACOPT_ANALYZE) != 0)
	{
		if (reltuple->relisshared)
			ereport(WARNING,
					(errmsg("skipping \"%s\" --- only superuser can analyze it",
							relname)));
		else if (reltuple->relnamespace == PG_CATALOG_NAMESPACE)
			ereport(WARNING,
					(errmsg("skipping \"%s\" --- only superuser or database owner can analyze it",
							relname)));
		else
			ereport(WARNING,
					(errmsg("skipping \"%s\" --- only table or database owner can analyze it",
							relname)));
	}

	return false;
}