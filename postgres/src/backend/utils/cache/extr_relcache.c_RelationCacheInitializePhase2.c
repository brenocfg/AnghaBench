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
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  AuthIdRelation_Rowtype_Id ; 
 int /*<<< orphan*/  AuthMemRelation_Rowtype_Id ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/  DatabaseRelation_Rowtype_Id ; 
 int /*<<< orphan*/  Desc_pg_auth_members ; 
 int /*<<< orphan*/  Desc_pg_authid ; 
 int /*<<< orphan*/  Desc_pg_database ; 
 int /*<<< orphan*/  Desc_pg_shseclabel ; 
 int /*<<< orphan*/  Desc_pg_subscription ; 
 scalar_t__ IsBootstrapProcessingMode () ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Natts_pg_auth_members ; 
 int /*<<< orphan*/  Natts_pg_authid ; 
 int /*<<< orphan*/  Natts_pg_database ; 
 int /*<<< orphan*/  Natts_pg_shseclabel ; 
 int /*<<< orphan*/  Natts_pg_subscription ; 
 int /*<<< orphan*/  RelationMapInitializePhase2 () ; 
 int /*<<< orphan*/  SharedSecLabelRelation_Rowtype_Id ; 
 int /*<<< orphan*/  SubscriptionRelation_Rowtype_Id ; 
 int /*<<< orphan*/  formrdesc (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_relcache_init_file (int) ; 

void
RelationCacheInitializePhase2(void)
{
	MemoryContext oldcxt;

	/*
	 * relation mapper needs initialized too
	 */
	RelationMapInitializePhase2();

	/*
	 * In bootstrap mode, the shared catalogs aren't there yet anyway, so do
	 * nothing.
	 */
	if (IsBootstrapProcessingMode())
		return;

	/*
	 * switch to cache memory context
	 */
	oldcxt = MemoryContextSwitchTo(CacheMemoryContext);

	/*
	 * Try to load the shared relcache cache file.  If unsuccessful, bootstrap
	 * the cache with pre-made descriptors for the critical shared catalogs.
	 */
	if (!load_relcache_init_file(true))
	{
		formrdesc("pg_database", DatabaseRelation_Rowtype_Id, true,
				  Natts_pg_database, Desc_pg_database);
		formrdesc("pg_authid", AuthIdRelation_Rowtype_Id, true,
				  Natts_pg_authid, Desc_pg_authid);
		formrdesc("pg_auth_members", AuthMemRelation_Rowtype_Id, true,
				  Natts_pg_auth_members, Desc_pg_auth_members);
		formrdesc("pg_shseclabel", SharedSecLabelRelation_Rowtype_Id, true,
				  Natts_pg_shseclabel, Desc_pg_shseclabel);
		formrdesc("pg_subscription", SubscriptionRelation_Rowtype_Id, true,
				  Natts_pg_subscription, Desc_pg_subscription);

#define NUM_CRITICAL_SHARED_RELS	5	/* fix if you change list above */
	}

	MemoryContextSwitchTo(oldcxt);
}