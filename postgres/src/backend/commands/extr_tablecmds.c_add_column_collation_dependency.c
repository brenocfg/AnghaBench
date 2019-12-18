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
typedef  scalar_t__ int32 ;
struct TYPE_4__ {scalar_t__ objectSubId; scalar_t__ objectId; int /*<<< orphan*/  classId; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__ ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  CollationRelationId ; 
 scalar_t__ DEFAULT_COLLATION_OID ; 
 int /*<<< orphan*/  DEPENDENCY_NORMAL ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_column_collation_dependency(Oid relid, int32 attnum, Oid collid)
{
	ObjectAddress myself,
				referenced;

	/* We know the default collation is pinned, so don't bother recording it */
	if (OidIsValid(collid) && collid != DEFAULT_COLLATION_OID)
	{
		myself.classId = RelationRelationId;
		myself.objectId = relid;
		myself.objectSubId = attnum;
		referenced.classId = CollationRelationId;
		referenced.objectId = collid;
		referenced.objectSubId = 0;
		recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);
	}
}