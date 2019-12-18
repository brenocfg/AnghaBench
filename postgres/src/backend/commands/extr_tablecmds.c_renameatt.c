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
struct TYPE_5__ {int /*<<< orphan*/  inh; int /*<<< orphan*/  relname; } ;
struct TYPE_4__ {int /*<<< orphan*/  behavior; TYPE_3__* relation; int /*<<< orphan*/  newname; int /*<<< orphan*/  subname; scalar_t__ missing_ok; } ;
typedef  TYPE_1__ RenameStmt ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  InvalidObjectAddress ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  ObjectAddressSubSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RVR_MISSING_OK ; 
 int /*<<< orphan*/  RangeVarCallbackForRenameAttribute ; 
 int /*<<< orphan*/  RangeVarGetRelidExtended (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  renameatt_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ObjectAddress
renameatt(RenameStmt *stmt)
{
	Oid			relid;
	AttrNumber	attnum;
	ObjectAddress address;

	/* lock level taken here should match renameatt_internal */
	relid = RangeVarGetRelidExtended(stmt->relation, AccessExclusiveLock,
									 stmt->missing_ok ? RVR_MISSING_OK : 0,
									 RangeVarCallbackForRenameAttribute,
									 NULL);

	if (!OidIsValid(relid))
	{
		ereport(NOTICE,
				(errmsg("relation \"%s\" does not exist, skipping",
						stmt->relation->relname)));
		return InvalidObjectAddress;
	}

	attnum =
		renameatt_internal(relid,
						   stmt->subname,	/* old att name */
						   stmt->newname,	/* new att name */
						   stmt->relation->inh, /* recursive? */
						   false,	/* recursing? */
						   0,	/* expected inhcount */
						   stmt->behavior);

	ObjectAddressSubSet(address, RelationRelationId, relid, attnum);

	return address;
}