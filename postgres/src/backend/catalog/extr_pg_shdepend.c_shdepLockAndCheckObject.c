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
typedef  int Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHOID ; 
 int /*<<< orphan*/  AccessShareLock ; 
#define  AuthIdRelationId 130 
#define  DatabaseRelationId 129 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  LockSharedObject (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int) ; 
 int /*<<< orphan*/  SearchSysCacheExists1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TableSpaceRelationId 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int) ; 
 char* get_database_name (int) ; 
 char* get_tablespace_name (int) ; 
 int /*<<< orphan*/  pfree (char*) ; 

void
shdepLockAndCheckObject(Oid classId, Oid objectId)
{
	/* AccessShareLock should be OK, since we are not modifying the object */
	LockSharedObject(classId, objectId, 0, AccessShareLock);

	switch (classId)
	{
		case AuthIdRelationId:
			if (!SearchSysCacheExists1(AUTHOID, ObjectIdGetDatum(objectId)))
				ereport(ERROR,
						(errcode(ERRCODE_UNDEFINED_OBJECT),
						 errmsg("role %u was concurrently dropped",
								objectId)));
			break;

			/*
			 * Currently, this routine need not support any other shared
			 * object types besides roles.  If we wanted to record explicit
			 * dependencies on databases or tablespaces, we'd need code along
			 * these lines:
			 */
#ifdef NOT_USED
		case TableSpaceRelationId:
			{
				/* For lack of a syscache on pg_tablespace, do this: */
				char	   *tablespace = get_tablespace_name(objectId);

				if (tablespace == NULL)
					ereport(ERROR,
							(errcode(ERRCODE_UNDEFINED_OBJECT),
							 errmsg("tablespace %u was concurrently dropped",
									objectId)));
				pfree(tablespace);
				break;
			}
#endif

		case DatabaseRelationId:
			{
				/* For lack of a syscache on pg_database, do this: */
				char	   *database = get_database_name(objectId);

				if (database == NULL)
					ereport(ERROR,
							(errcode(ERRCODE_UNDEFINED_OBJECT),
							 errmsg("database %u was concurrently dropped",
									objectId)));
				pfree(database);
				break;
			}


		default:
			elog(ERROR, "unrecognized shared classId: %u", classId);
	}
}