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
struct TYPE_4__ {scalar_t__ objectSubId; void* objectId; void* classId; } ;
typedef  void* Oid ;
typedef  TYPE_1__ ObjectAddress ;

/* Variables and functions */
 void* AuthIdRelationId ; 
 int /*<<< orphan*/  SHARED_DEPENDENCY_OWNER ; 
 int /*<<< orphan*/  recordSharedDependencyOn (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

void
recordDependencyOnOwner(Oid classId, Oid objectId, Oid owner)
{
	ObjectAddress myself,
				referenced;

	myself.classId = classId;
	myself.objectId = objectId;
	myself.objectSubId = 0;

	referenced.classId = AuthIdRelationId;
	referenced.objectId = owner;
	referenced.objectSubId = 0;

	recordSharedDependencyOn(&myself, &referenced, SHARED_DEPENDENCY_OWNER);
}