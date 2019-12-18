#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  InvokeObjectPostCreateHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LargeObjectCreate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LargeObjectRelationId ; 
 int /*<<< orphan*/  recordDependencyOnOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Oid
inv_create(Oid lobjId)
{
	Oid			lobjId_new;

	/*
	 * Create a new largeobject with empty data pages
	 */
	lobjId_new = LargeObjectCreate(lobjId);

	/*
	 * dependency on the owner of largeobject
	 *
	 * The reason why we use LargeObjectRelationId instead of
	 * LargeObjectMetadataRelationId here is to provide backward compatibility
	 * to the applications which utilize a knowledge about internal layout of
	 * system catalogs. OID of pg_largeobject_metadata and loid of
	 * pg_largeobject are same value, so there are no actual differences here.
	 */
	recordDependencyOnOwner(LargeObjectRelationId,
							lobjId_new, GetUserId());

	/* Post creation hook for new large object */
	InvokeObjectPostCreateHook(LargeObjectRelationId, lobjId_new, 0);

	/*
	 * Advance command counter to make new tuple visible to later operations.
	 */
	CommandCounterIncrement();

	return lobjId_new;
}