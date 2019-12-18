#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  locktag_lockmethodid; } ;
struct TYPE_9__ {int /*<<< orphan*/  relId; int /*<<< orphan*/  dbId; } ;
struct TYPE_10__ {TYPE_1__ lockRelId; } ;
struct TYPE_11__ {TYPE_2__ rd_lockInfo; } ;
typedef  TYPE_3__* Relation ;
typedef  TYPE_4__ LOCKTAG ;
typedef  scalar_t__ LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  GetLockmodeName (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LockHeldByMe (TYPE_4__*,scalar_t__) ; 
 scalar_t__ MaxLockMode ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_3__*) ; 
 int /*<<< orphan*/  SET_LOCKTAG_RELATION (TYPE_4__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
CheckRelationLockedByMe(Relation relation, LOCKMODE lockmode, bool orstronger)
{
	LOCKTAG		tag;

	SET_LOCKTAG_RELATION(tag,
						 relation->rd_lockInfo.lockRelId.dbId,
						 relation->rd_lockInfo.lockRelId.relId);

	if (LockHeldByMe(&tag, lockmode))
		return true;

	if (orstronger)
	{
		LOCKMODE	slockmode;

		for (slockmode = lockmode + 1;
			 slockmode <= MaxLockMode;
			 slockmode++)
		{
			if (LockHeldByMe(&tag, slockmode))
			{
#ifdef NOT_USED
				/* Sometimes this might be useful for debugging purposes */
				elog(WARNING, "lock mode %s substituted for %s on relation %s",
					 GetLockmodeName(tag.locktag_lockmethodid, slockmode),
					 GetLockmodeName(tag.locktag_lockmethodid, lockmode),
					 RelationGetRelationName(relation));
#endif
				return true;
			}
		}
	}

	return false;
}