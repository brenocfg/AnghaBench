#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lockRelId; } ;
struct TYPE_6__ {TYPE_1__ rd_lockInfo; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  LockRelId ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  MAX_LOCKMODES ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  RelationClose (TYPE_2__*) ; 
 int /*<<< orphan*/  UnlockRelationId (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
relation_close(Relation relation, LOCKMODE lockmode)
{
	LockRelId	relid = relation->rd_lockInfo.lockRelId;

	Assert(lockmode >= NoLock && lockmode < MAX_LOCKMODES);

	/* The relcache does the real work... */
	RelationClose(relation);

	if (lockmode != NoLock)
		UnlockRelationId(&relid, lockmode);
}