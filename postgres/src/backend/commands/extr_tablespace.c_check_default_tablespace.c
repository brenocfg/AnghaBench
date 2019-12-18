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
typedef  scalar_t__ GucSource ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  GUC_check_errdetail (char*,char*) ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ IsTransactionState () ; 
 scalar_t__ MyDatabaseId ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ PGC_S_TEST ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  get_tablespace_oid (char*,int) ; 

bool
check_default_tablespace(char **newval, void **extra, GucSource source)
{
	/*
	 * If we aren't inside a transaction, or connected to a database, we
	 * cannot do the catalog accesses necessary to verify the name.  Must
	 * accept the value on faith.
	 */
	if (IsTransactionState() && MyDatabaseId != InvalidOid)
	{
		if (**newval != '\0' &&
			!OidIsValid(get_tablespace_oid(*newval, true)))
		{
			/*
			 * When source == PGC_S_TEST, don't throw a hard error for a
			 * nonexistent tablespace, only a NOTICE.  See comments in guc.h.
			 */
			if (source == PGC_S_TEST)
			{
				ereport(NOTICE,
						(errcode(ERRCODE_UNDEFINED_OBJECT),
						 errmsg("tablespace \"%s\" does not exist",
								*newval)));
			}
			else
			{
				GUC_check_errdetail("Tablespace \"%s\" does not exist.",
									*newval);
				return false;
			}
		}
	}

	return true;
}