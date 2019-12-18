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
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_4__ {scalar_t__ objectSubId; void* objectId; void* classId; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  void* Oid ;
typedef  TYPE_1__ ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  InheritsRelationId ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHookArg (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int) ; 
 void* RelationRelationId ; 
 int /*<<< orphan*/  SetRelationHasSubclass (void*,int) ; 
 int /*<<< orphan*/  StoreSingleInheritance (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  child_dependency_type (int) ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
StoreCatalogInheritance1(Oid relationId, Oid parentOid,
						 int32 seqNumber, Relation inhRelation,
						 bool child_is_partition)
{
	ObjectAddress childobject,
				parentobject;

	/* store the pg_inherits row */
	StoreSingleInheritance(relationId, parentOid, seqNumber);

	/*
	 * Store a dependency too
	 */
	parentobject.classId = RelationRelationId;
	parentobject.objectId = parentOid;
	parentobject.objectSubId = 0;
	childobject.classId = RelationRelationId;
	childobject.objectId = relationId;
	childobject.objectSubId = 0;

	recordDependencyOn(&childobject, &parentobject,
					   child_dependency_type(child_is_partition));

	/*
	 * Post creation hook of this inheritance. Since object_access_hook
	 * doesn't take multiple object identifiers, we relay oid of parent
	 * relation using auxiliary_id argument.
	 */
	InvokeObjectPostAlterHookArg(InheritsRelationId,
								 relationId, 0,
								 parentOid, false);

	/*
	 * Mark the parent as having subclasses.
	 */
	SetRelationHasSubclass(parentOid, true);
}