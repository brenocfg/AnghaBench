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
typedef  scalar_t__ Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetNextTempTableSpace () ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ MyDatabaseTableSpace ; 
 int /*<<< orphan*/  PrepareTempTablespaces () ; 
 char RELPERSISTENCE_TEMP ; 
 char* default_tablespace ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ get_tablespace_oid (char*,int) ; 

Oid
GetDefaultTablespace(char relpersistence, bool partitioned)
{
	Oid			result;

	/* The temp-table case is handled elsewhere */
	if (relpersistence == RELPERSISTENCE_TEMP)
	{
		PrepareTempTablespaces();
		return GetNextTempTableSpace();
	}

	/* Fast path for default_tablespace == "" */
	if (default_tablespace == NULL || default_tablespace[0] == '\0')
		return InvalidOid;

	/*
	 * It is tempting to cache this lookup for more speed, but then we would
	 * fail to detect the case where the tablespace was dropped since the GUC
	 * variable was set.  Note also that we don't complain if the value fails
	 * to refer to an existing tablespace; we just silently return InvalidOid,
	 * causing the new object to be created in the database's tablespace.
	 */
	result = get_tablespace_oid(default_tablespace, true);

	/*
	 * Allow explicit specification of database's default tablespace in
	 * default_tablespace without triggering permissions checks.  Don't allow
	 * specifying that when creating a partitioned table, however, since the
	 * result is confusing.
	 */
	if (result == MyDatabaseTableSpace)
	{
		if (partitioned)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("cannot specify default tablespace for partitioned relations")));
		result = InvalidOid;
	}
	return result;
}