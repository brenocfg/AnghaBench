#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ relisshared; int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_class ;

/* Variables and functions */
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  PrepareInvalidationState () ; 
 int /*<<< orphan*/  RegisterRelcacheInvalidation (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
CacheInvalidateRelcacheByTuple(HeapTuple classTuple)
{
	Form_pg_class classtup = (Form_pg_class) GETSTRUCT(classTuple);
	Oid			databaseId;
	Oid			relationId;

	PrepareInvalidationState();

	relationId = classtup->oid;
	if (classtup->relisshared)
		databaseId = InvalidOid;
	else
		databaseId = MyDatabaseId;
	RegisterRelcacheInvalidation(databaseId, relationId);
}