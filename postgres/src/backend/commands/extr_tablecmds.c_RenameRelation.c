#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  relname; } ;
struct TYPE_4__ {scalar_t__ renameType; int /*<<< orphan*/  newname; TYPE_3__* relation; scalar_t__ missing_ok; } ;
typedef  TYPE_1__ RenameStmt ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  InvalidObjectAddress ; 
 int /*<<< orphan*/  NOTICE ; 
 scalar_t__ OBJECT_INDEX ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RVR_MISSING_OK ; 
 int /*<<< orphan*/  RangeVarCallbackForAlterRelation ; 
 int /*<<< orphan*/  RangeVarGetRelidExtended (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  RenameRelationInternal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ShareUpdateExclusiveLock ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 

ObjectAddress
RenameRelation(RenameStmt *stmt)
{
	bool		is_index = stmt->renameType == OBJECT_INDEX;
	Oid			relid;
	ObjectAddress address;

	/*
	 * Grab an exclusive lock on the target table, index, sequence, view,
	 * materialized view, or foreign table, which we will NOT release until
	 * end of transaction.
	 *
	 * Lock level used here should match RenameRelationInternal, to avoid lock
	 * escalation.
	 */
	relid = RangeVarGetRelidExtended(stmt->relation,
									 is_index ? ShareUpdateExclusiveLock : AccessExclusiveLock,
									 stmt->missing_ok ? RVR_MISSING_OK : 0,
									 RangeVarCallbackForAlterRelation,
									 (void *) stmt);

	if (!OidIsValid(relid))
	{
		ereport(NOTICE,
				(errmsg("relation \"%s\" does not exist, skipping",
						stmt->relation->relname)));
		return InvalidObjectAddress;
	}

	/* Do the work */
	RenameRelationInternal(relid, stmt->newname, false, is_index);

	ObjectAddressSet(address, RelationRelationId, relid);

	return address;
}