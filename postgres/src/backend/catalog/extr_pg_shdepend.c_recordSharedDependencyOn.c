#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  SharedDependencyType ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ IsBootstrapProcessingMode () ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  SharedDependRelationId ; 
 int /*<<< orphan*/  isSharedObjectPinned (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shdepAddDependency (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
recordSharedDependencyOn(ObjectAddress *depender,
						 ObjectAddress *referenced,
						 SharedDependencyType deptype)
{
	Relation	sdepRel;

	/*
	 * Objects in pg_shdepend can't have SubIds.
	 */
	Assert(depender->objectSubId == 0);
	Assert(referenced->objectSubId == 0);

	/*
	 * During bootstrap, do nothing since pg_shdepend may not exist yet.
	 * initdb will fill in appropriate pg_shdepend entries after bootstrap.
	 */
	if (IsBootstrapProcessingMode())
		return;

	sdepRel = table_open(SharedDependRelationId, RowExclusiveLock);

	/* If the referenced object is pinned, do nothing. */
	if (!isSharedObjectPinned(referenced->classId, referenced->objectId,
							  sdepRel))
	{
		shdepAddDependency(sdepRel, depender->classId, depender->objectId,
						   depender->objectSubId,
						   referenced->classId, referenced->objectId,
						   deptype);
	}

	table_close(sdepRel, RowExclusiveLock);
}