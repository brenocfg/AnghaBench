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
struct TYPE_3__ {scalar_t__ extname; scalar_t__ object; int /*<<< orphan*/  relation; int /*<<< orphan*/  objectType; } ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ AlterObjectDependsStmt ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEPENDENCY_AUTO_EXTENSION ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  OBJECT_EXTENSION ; 
 int /*<<< orphan*/  get_object_address (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_object_address_rv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  recordDependencyOn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ObjectAddress
ExecAlterObjectDependsStmt(AlterObjectDependsStmt *stmt, ObjectAddress *refAddress)
{
	ObjectAddress address;
	ObjectAddress refAddr;
	Relation	rel;

	address =
		get_object_address_rv(stmt->objectType, stmt->relation, (List *) stmt->object,
							  &rel, AccessExclusiveLock, false);

	/*
	 * If a relation was involved, it would have been opened and locked. We
	 * don't need the relation here, but we'll retain the lock until commit.
	 */
	if (rel)
		table_close(rel, NoLock);

	refAddr = get_object_address(OBJECT_EXTENSION, (Node *) stmt->extname,
								 &rel, AccessExclusiveLock, false);
	Assert(rel == NULL);
	if (refAddress)
		*refAddress = refAddr;

	recordDependencyOn(&address, &refAddr, DEPENDENCY_AUTO_EXTENSION);

	return address;
}