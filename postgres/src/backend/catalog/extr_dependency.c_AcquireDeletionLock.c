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
struct TYPE_3__ {scalar_t__ classId; int /*<<< orphan*/  objectId; } ;
typedef  TYPE_1__ ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  LockDatabaseObject (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockRelationOid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PERFORM_DELETION_CONCURRENTLY ; 
 scalar_t__ RelationRelationId ; 
 int /*<<< orphan*/  ShareUpdateExclusiveLock ; 

__attribute__((used)) static void
AcquireDeletionLock(const ObjectAddress *object, int flags)
{
	if (object->classId == RelationRelationId)
	{
		/*
		 * In DROP INDEX CONCURRENTLY, take only ShareUpdateExclusiveLock on
		 * the index for the moment.  index_drop() will promote the lock once
		 * it's safe to do so.  In all other cases we need full exclusive
		 * lock.
		 */
		if (flags & PERFORM_DELETION_CONCURRENTLY)
			LockRelationOid(object->objectId, ShareUpdateExclusiveLock);
		else
			LockRelationOid(object->objectId, AccessExclusiveLock);
	}
	else
	{
		/* assume we should lock the whole object not a sub-object */
		LockDatabaseObject(object->classId, object->objectId, 0,
						   AccessExclusiveLock);
	}
}