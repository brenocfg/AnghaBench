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
struct TYPE_6__ {TYPE_1__* rd_rel; } ;
struct TYPE_5__ {scalar_t__ relisshared; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  PrepareInvalidationState () ; 
 int /*<<< orphan*/  RegisterRelcacheInvalidation (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 

void
CacheInvalidateRelcache(Relation relation)
{
	Oid			databaseId;
	Oid			relationId;

	PrepareInvalidationState();

	relationId = RelationGetRelid(relation);
	if (relation->rd_rel->relisshared)
		databaseId = InvalidOid;
	else
		databaseId = MyDatabaseId;

	RegisterRelcacheInvalidation(databaseId, relationId);
}