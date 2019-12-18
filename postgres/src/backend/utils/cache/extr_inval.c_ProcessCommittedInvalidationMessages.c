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
typedef  int /*<<< orphan*/  SharedInvalidationMessage ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG4 ; 
 int /*<<< orphan*/ * DatabasePath ; 
 int /*<<< orphan*/ * GetDatabasePath (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationCacheInitFilePostInvalidate () ; 
 int /*<<< orphan*/  RelationCacheInitFilePreInvalidate () ; 
 int /*<<< orphan*/  SendSharedInvalidMessages (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_recovery (int /*<<< orphan*/ ) ; 

void
ProcessCommittedInvalidationMessages(SharedInvalidationMessage *msgs,
									 int nmsgs, bool RelcacheInitFileInval,
									 Oid dbid, Oid tsid)
{
	if (nmsgs <= 0)
		return;

	elog(trace_recovery(DEBUG4), "replaying commit with %d messages%s", nmsgs,
		 (RelcacheInitFileInval ? " and relcache file invalidation" : ""));

	if (RelcacheInitFileInval)
	{
		elog(trace_recovery(DEBUG4), "removing relcache init files for database %u",
			 dbid);

		/*
		 * RelationCacheInitFilePreInvalidate, when the invalidation message
		 * is for a specific database, requires DatabasePath to be set, but we
		 * should not use SetDatabasePath during recovery, since it is
		 * intended to be used only once by normal backends.  Hence, a quick
		 * hack: set DatabasePath directly then unset after use.
		 */
		if (OidIsValid(dbid))
			DatabasePath = GetDatabasePath(dbid, tsid);

		RelationCacheInitFilePreInvalidate();

		if (OidIsValid(dbid))
		{
			pfree(DatabasePath);
			DatabasePath = NULL;
		}
	}

	SendSharedInvalidMessages(msgs, nmsgs);

	if (RelcacheInitFileInval)
		RelationCacheInitFilePostInvalidate();
}