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
struct TYPE_3__ {scalar_t__ objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  DROP_CASCADE ; 
 int /*<<< orphan*/  LargeObjectRelationId ; 
 int /*<<< orphan*/  performDeletion (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
inv_drop(Oid lobjId)
{
	ObjectAddress object;

	/*
	 * Delete any comments and dependencies on the large object
	 */
	object.classId = LargeObjectRelationId;
	object.objectId = lobjId;
	object.objectSubId = 0;
	performDeletion(&object, DROP_CASCADE, 0);

	/*
	 * Advance command counter so that tuple removal will be seen by later
	 * large-object operations in this transaction.
	 */
	CommandCounterIncrement();

	/* For historical reasons, we always return 1 on success. */
	return 1;
}